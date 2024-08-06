#include "Game.hpp"
#include "Table.hpp"


Game::Game(Table* mainTable){
    table = mainTable;

    m_deck = new Deck;
    pot = 0;
    currentBet = 2; // BIG BLIND
    prevRaise = currentBet;
    foldCount = 0;

//    for(int i=0; i<table->getPlayerCount(); i++){
//        m_players.push_back(new Player);
//        m_players[i]->dealHand(m_deck);
//    }

    m_deck->burn();
    m_board[0] = m_deck->deal();
    m_board[1] = m_deck->deal();
    m_board[2] = m_deck->deal();
    m_deck->burn();
    m_board[3] = m_deck->deal();
    m_deck->burn();
    m_board[4] = m_deck->deal();
}

string Game::showHand(){
    string result;
    for(int i=0; i<table->getPlayerCount(); i++){
        result += table->getPlayer(i)->viewHand() + "\n";
    }

    return result;
}


string Game::flop(){
    return "FLOP: " + m_board[0].title + " of " + m_board[0].suit + ",  " + m_board[1].title + " of " + m_board[1].suit + ",  " + m_board[2].title + " of " + m_board[2].suit;
}

string Game::turn(){
    return flop() + "  TURN: " + m_board[3].title + " of " + m_board[3].suit;
}

string Game::river(){
    return turn() + "  RIVER: " + m_board[4].title + " of " + m_board[4].suit;
}



string Game::whatHand(Card *p, int& score){

    int counts[] = {0, 0, 0, 0, 0};
    Card lowCard; lowCard.value = 13;
    Card highCard; highCard.value = -1;

    for(int i=0; i<5; i++){
        if(p[i].value < lowCard.value) lowCard = p[i];
        if(p[i].value > highCard.value) highCard = p[i];

        for(int j=0; j<5; j++){
            if(i == j) continue;
            if(p[i].value == p[j].value)
                counts[i]++;
        }
    }

    if(lowCard.value == 0) highCard = lowCard;

    // {pairs, trips, quads}
    int countOfPairs[] = {0, 0, 0};
    for(int i=0; i<5; i++){
        if(counts[i] == 1) countOfPairs[0]++;
        else if(counts[i] == 2) countOfPairs[1]++;
        else if(counts[i] == 3) countOfPairs[2]++;
    }

    bool flush = false;
    bool straight = false;
    bool royal = false;

    if(countOfPairs[0] + countOfPairs[1] + countOfPairs[2] == 0){

        // Check that suits are equal
        if(p[0].suit == p[1].suit && p[0].suit == p[2].suit && p[0].suit == p[3].suit && p[0].suit == p[4].suit)
            flush = true;

        int values[5];
        for(int i=0; i<5; i++){values[i] = p[i].value;}
        sort(values, values+5);

        // Check that numbers are in a row
        if(values[0]+1 == values[1] && values[1]+1 == values[2] && values[2]+1 == values[3] && values[3]+1 == values[4])
            straight = true;

        // Special case of straight becuase 10, J, Q, K, A
        if(values[0] == 0 && values[1] == 9 && values[2] == 10 && values[3] == 11 && values[4] == 12){
            straight = true;
            royal = true;
        }
    }

    if(flush == true && royal == true){
        score = 10;
        return "ROYAL FLUSH";
    }

    if(flush == true && straight == true){
        score = 9;
        return highCard.title + " HIGH STRAIGHT FLUSH";
    }

    if(countOfPairs[2] != 0){
        score = 8;
        return "QUADS";
    }

    if(countOfPairs[0] != 0 && countOfPairs[1] != 0){
        score = 7;
        return "FULL HOUSE";
    }

    if(flush == true){
        score = 6;
        return highCard.title + " HIGH FLUSH";
    }

    if(straight == true){
        score = 5;
        return highCard.title + " HIGH STRAIGHT";
    }

    if(countOfPairs[1] != 0){
        score = 4;
        return "TRIPS";
    }

    if(countOfPairs[0] == 4){
        score = 3;
        return "TWO PAIR";
    }

    if(countOfPairs[0] != 0){
        score = 2;
        return "ONE PAIR";
    }

    score = 1;
    return "HIGH CARD";
}


void Game::handGenerator(Player* currentPlayer, int round){

    // round 0 = flop, 1 = turn, 2 = river
    int roundCount;

    if(round == 0)
        roundCount = 1;
    else if(round == 1)
        roundCount = 6;
    else
        roundCount = 21;

    Card options[] = {currentPlayer->getCard1(), currentPlayer->getCard2(), m_board[0], m_board[1], m_board[2], m_board[3], m_board[4]};

    int permutations[21][5] = {
        {0, 1, 2, 3, 4},
        {0, 1, 2, 3, 5},
        {0, 1, 2, 4, 5},
        {0, 1, 3, 4, 5},
        {0, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {0, 1, 2, 3, 6},
        {0, 1, 2, 4, 6},
        {0, 1, 2, 5, 6},
        {0, 1, 3, 4, 6},
        {0, 1, 3, 5, 6},
        {0, 1, 4, 5, 6},
        {0, 2, 3, 4, 6},
        {0, 2, 3, 5, 6},
        {0, 2, 4, 5, 6},
        {0, 3, 4, 5, 6},
        {1, 2, 3, 4, 6},
        {1, 2, 3, 5, 6},
        {1, 2, 4, 5, 6},
        {1, 3, 4, 5, 6},
        {2, 3, 4, 5, 6}
    };

    int highScore = 0;
    int highHand = -1;
    string highTitle = "";

    for(int i=0; i < roundCount; i++){
        Card currentHand[] = {options[permutations[i][0]], options[permutations[i][1]], options[permutations[i][2]], options[permutations[i][3]], options[permutations[i][4]]};
        int tempScore = 0;

        string tempString = whatHand(currentHand, tempScore);

        if(tempScore > highScore){
            highScore = tempScore;
            highHand = i;
            highTitle = tempString;
        }
        else if(tempScore == highScore){

            Card tempCard[] = {options[permutations[highHand][0]], options[permutations[highHand][1]], options[permutations[highHand][2]], options[permutations[highHand][3]], options[permutations[highHand][4]]};

            if(compareHands(tempScore, currentHand, tempCard)){
                highHand = i;
                highTitle = tempString;
            }

        }
    }
    currentPlayer->setHandRating(highScore);
    Card finalHand[] = {options[permutations[highHand][0]], options[permutations[highHand][1]], options[permutations[highHand][2]], options[permutations[highHand][3]], options[permutations[highHand][4]]};
    currentPlayer->setHand(finalHand);

//    cout << highScore << " " << highHand << " " << highTitle << endl;
}


bool Game::compareHands(int score, Card hand1[5], Card hand2[5]){

    // TRUE = hand1 beats hand2
    // FALSE = hand2 beats hand1

    // Straight Flush
    if(score == 9){
        int hand1Max = -1;
        int hand2Max = -1;
        for(int i=0; i<5; i++){
            if(hand1[i].value > hand1Max) hand1Max = hand1[i].value;
            if(hand2[i].value > hand2Max) hand2Max = hand2[i].value;
        }

        if(hand1Max > hand2Max)
            return true;
        return false;
    }

    // Quads
    if(score == 8){
        int counts1[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int counts2[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        for(int i=0; i<5; i++){
            counts1[hand1[i].value]++;
            counts2[hand2[i].value]++;
        }

        int q1=-1, kick1=-1,
            q2=-1, kick2=-1;

        for(int i=0; i<13; i++){
            if(counts1[i] == 1) kick1 = i;
            if(counts1[i] == 4) q1 = i;
            if(counts2[i] == 1) kick2 = i;
            if(counts2[i] == 4) q2 = i;
        }

        if(q1 == 0) q1 = 13;
        if(kick1 == 0) kick1 = 13;
        if(q2 == 0) q2 = 13;
        if(kick2 == 0) kick2 = 13;



        // hand1 has higher quads
        if(q1 > q2)
            return true;
        // hand2 has higher quads
        if(q2 > q1)
            return false;
        // hand1 has higher kicker
        if(kick1 > kick2)
            return true;
        //hand2 has higher kicker
        if(kick2 > kick1)
            return false;

        // CHOP
        return false;
    }

    // Full House
    if(score == 7){
        int counts1[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int counts2[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        for(int i=0; i<5; i++){
            counts1[hand1[i].value]++;
            counts2[hand2[i].value]++;
        }

        int t1=-1, p1=-1,
            t2=-1, p2=-1;

        for(int i=0; i<13; i++){
            if(counts1[i] == 3) t1 = i;
            if(counts1[i] == 2) p1 = i;
            if(counts2[i] == 3) t2 = i;
            if(counts2[i] == 2) p2 = i;
        }

        if(t1 == 0) p1 = 13;
        if(p1 == 0) p1 = 13;
        if(t2 == 0) t2 = 13;
        if(p2 == 0) p2 = 13;

        // hand1 has higher trips
        if(t1 > t2)
            return true;
        // hand2 has higher trips
        if(t2 > t1)
            return false;
        // hand1 has higher pair
        if(p1 > p2)
            return true;
        // hand2 has higher pair
        if(p2 > p1)
            return false;

        // CHOP
        return false;
    }

    // Flush
    if(score == 6){
        int highCard1 = -1, highCard2 = -1;
        for(int i=0; i<5; i++){
            if(hand1[i].value == 0) highCard1 = 13;
            if(hand2[i].value == 0) highCard2 = 13;

            if(hand1[i].value > highCard1) highCard1 = hand1[i].value;
            if(hand2[i].value > highCard2) highCard2 = hand2[i].value;
        }

        if(highCard1 > highCard2)
            return true;
        if(highCard2 > highCard1)
            return false;

        // CHOP
        return false;
    }

    // Straight
    if(score == 5){


        //
        //
        // FIX PROBLEM TO GET CORRECT STRAIGHT WHEN IT STARTS WITH ACE
        //
        //


        int highCard1 = -1, highCard2 = -1;
        for(int i=0; i<5; i++){
            if(hand1[i].value == 0) highCard1 = 13;
            if(hand2[i].value == 0) highCard2 = 13;

            if(hand1[i].value > highCard1) highCard1 = hand1[i].value;
            if(hand2[i].value > highCard2) highCard2 = hand2[i].value;
        }

        if(highCard1 > highCard2)
            return true;
        if(highCard2 > highCard1)
            return false;

        // CHOP
        return false;
    }

    // Trips
    if(score == 4){
        int counts1[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int counts2[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        for(int i=0; i<5; i++){
            if(hand1[i].value == 0)
                counts1[13]++;
            else
                counts1[hand1[i].value]++;

            if(hand2[i].value == 0)
                counts2[13]++;
            else
                counts2[hand2[i].value]++;
        }

        int trip1=-1, f1=-1, s1=-1,
            trip2=-1, f2=-1, s2=-1;

        for(int i=0; i<14; i++){
            if(counts1[i] == 3) trip1 = i;
            if(counts2[i] == 3) trip2 = i;

            if(counts1[i] == 1 && f1 == -1)
                f1 = i;
            else if(counts1[i] == 1 && f1 != -1)
                s1 = i;

            if(counts2[i] == 1 && f2 == -1)
                f2 = i;
            else if(counts2[i] == 1 && f2 != -1)
                s2 = i;
        }

        // hand1 has higher trips
        if(trip1 > trip2)
            return true;
        // hand2 has higher trips
        if(trip2 > trip1)
            return false;
        // hand1 has higher first kicker
        if(s1 > s2)
            return true;
        // hand2 has higher first kicker
        if(s2 > s1)
            return false;
        // hand1 has higher second kicker
        if(f1 > f2)
            return true;
        // hand2 has higher kicker
        if(f2 > f1)
            return false;

        // CHOP
        return false;
    }

    // Two Pair
    if(score == 3){
        int counts1[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int counts2[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        for(int i=0; i<5; i++){
            if(hand1[i].value == 0)
                counts1[13]++;
            else
                counts1[hand1[i].value]++;

            if(hand2[i].value == 0)
                counts2[13]++;
            else
                counts2[hand2[i].value]++;
        }

        int f1=-1, s1=-1, k1=-1,
            f2=-1, s2=-1, k2=-1;

        for(int i=0; i<14; i++){

            if(counts1[i] == 2 && f1 == -1)
                f1 = i;
            else if(counts1[i] == 2 && f1 != -1)
                s1 = i;

            if(counts2[i] == 2 && f2 == -1)
                f2 = i;
            else if(counts2[i] == 2 && f2 != -1)
                s2 = i;

            if(counts1[i] == 1) k1 = i;
            if(counts2[i] == 1) k2 = i;
        }

        // hand1 has higher first pair
        if(s1 > s2)
            return true;
        // hand2 has higher first pair
        if(s2 > s1)
            return false;
        // hand1 has higher second pair
        if(f1 > f2)
            return true;
        // hand2 has higher second pair
        if(f2 > f1)
            return false;
        // hand1 has higher kicker
        if(k1 > k2)
            return true;
        // hand2 has higher kicker
        if(k2 > k1)
            return false;

        // CHOP
        return false;
    }

    // One Pair
    if(score == 2){
        int counts1[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int counts2[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        for(int i=0; i<5; i++){
            if(hand1[i].value == 0)
                counts1[13]++;
            else
                counts1[hand1[i].value]++;

            if(hand2[i].value == 0)
                counts2[13]++;
            else
                counts2[hand2[i].value]++;
        }


        int pair1=-1, a1=-1, b1=-1, c1=-1,
            pair2=-1, a2=-1, b2=-1, c2=-1;

        for(int i=0; i<14; i++){
            if(counts1[i] == 2) pair1 = i;
            if(counts2[i] == 2) pair2 = i;

            if(counts1[i] == 1 && a1 == -1) a1 = i;
            else if(counts1[i] == 1 && a1 != -1 && b1 == -1) b1 = i;
            else if(counts1[i] == 1 && a1 != -1 && b1 != -1) c1 = i;

            if(counts2[i] == 1 && a2 == -1) a2 = i;
            else if(counts2[i] == 1 && a2 != -1 && b2 == -1) b2 = i;
            else if(counts2[i] == 1 && a2 != -1 && b2 != -1) c2 = i;
        }

        if(pair1 > pair2)
            return true;
        if(pair2 > pair1)
            return false;

        if(c1 > c2)
            return true;
        if(c2 > c1)
            return false;

        if(b1 > b2)
            return true;
        if(b2 > b1)
            return false;

        if(a1 > a2)
            return true;
        if(a2 > a1)
            return false;

        // CHOP
        return false;
    }

    // High Card
    if(score == 1){
        int values1[5], values2[5];
        for(int i=0; i<5; i++){
            if(hand1[i].value == 0)
                values1[i] = 13;
            else
                values1[i] = hand1[i].value;

            if(hand2[i].value == 0)
                values2[i] = 13;
            else
                values2[i] = hand2[i].value;

        }
        sort(values1, values1+5);
        sort(values2, values2+5);

        for(int i=4; i>=0; i--){
            if(values1[i] > values2[i])
                return true;
            else if(values2[i] > values1[i])
                return false;
        }
        // CHOP
        return false;
    }

    return false;
}

//Player* Game::getPlayer(int x){
//    return m_players[x];
//}

bool Game::addPot(string action, int amount, Player* currentPlayer){
    if(action == "fold"){
        currentPlayer->setFold();
        foldCount++;
        return true;
    }

    if(action == "check")
        return true;

    if(action == "call"){
        pot += currentBet;
        currentPlayer->changeBalance(currentBet*-1);
        return true;
    }

    if(action == "raise"){

        if(amount - currentBet < prevRaise)
            return false;

        prevRaise = amount - currentBet;
        pot += amount;
        currentPlayer->changeBalance(amount * -1);
        currentBet = amount;
        return true;
    }

    return true;

}


void Game::collectBets(bool preflop){
    
    currentBet = 2; // BIG BLIND AMOUNT
    int dealer = table->getDealer();
    int sb = table->getSb();
    int bb = table->getBb();
    
        
    // Determine which players are still in
    bool stillPlaying[20];
    for(int i=0; i<table->getPlayerCount(); i++){
        if(table->getPlayer(i)->getFold() == true)
            stillPlaying[i] = false;
        else{
            stillPlaying[i] = true;
        }
    }
    
    int i = sb;
    
    while(true){
        
        
        
    }
}


// OLD COLLECTBETS
//for(int i=0; i<table->getPlayerCount(); i++){
//
//    if(i == sb){
//
//    }
//
//
//    if(getFoldCount() == table->getPlayerCount()-1){
//        cout << table->getPlayer(i)->getName() << " WINS" << endl;
//    }
//
//    if(table->getPlayer(i)->getFold())
//        continue;
//
//    cout << "CURRENT BET: " << getCurrentBet() << "   BALANCE: " << table->getPlayer(i)->getBalance() << "   POT: " << getPot() << endl;
//
//    cout << table->getPlayer(i)->getName() << ", What is your action? ";
//    string action; cin >> action;
//    int amount = 0;
//    if(action == "raise"){
//        cout << "To what amount? ";
//        cin >> amount;
//    }
//
//
//    while(!addPot(action, amount, table->getPlayer(i))){
//        cout << "Cannot raise by that amount" << endl;
//        cout << "New amount? ";
//        cin >> amount;
//    }
//    cout << endl << endl;
//}


// val1, suit1, val2, suit2, val3, suit3, val4, suit4, val5, suit5, win?
