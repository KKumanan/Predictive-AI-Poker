//
//  Table.cpp
//  poker
//
//  Created by Krishna Kumanan on 7/26/24.
//

#include "Table.hpp"
#include "Game.hpp"

Table::~Table(){
    delete game;
    for(int i=0; i<playerCount; i++){
        delete players[i];
    }
}

Table::Table(int p){
    playerCount = p;
    game = new Game(this);
    
    if(playerCount == 2){
        dealer = 0;
        sb = 0;
        bb = 1;
    }
    else{
        dealer = 0;
        sb = 1;
        bb = 2;
    }
    
    for(int i=0; i<playerCount; i++){
        string pName = "Player " + to_string(i+1);
        players.push_back(new Player(pName));
        players[i]->dealHand(game->getDeck());
    }
    
}

void Table::changeDealer(){
    
    if(playerCount == 2){
        dealer = !dealer;
        sb = dealer;
        bb = !bb;
        return;
    }
    
    dealer++;
    sb++;
    bb++;
    if(dealer == playerCount)
        dealer=0;
    else if(sb == playerCount)
        sb = 0;
    else if(bb == playerCount)
        bb = 0;
}

Player* Table::getPlayer(int x){
    return players[x];
}

void Table::runGame(){
    
    cout << game->showHand() << endl;
    
//    game->collectBets(true);
    
    cout << game->flop() << endl;
    
    game->handGenerator(getPlayer(0), 0);
    
//    game->collectBets(false);
    
    cout << game->turn() << endl;
    
    game->handGenerator(getPlayer(0), 1);
    
//    game->collectBets(false);
    
    
    cout << game->river() << endl;
    
    game->handGenerator(getPlayer(0), 2);
    
//    game->collectBets(false);
    
    changeDealer();
    
}

string Table::dataGen(){
    
//    cout << game->showHand() << endl;
//    cout << game->river() << endl;
    string result = "";


    
    for(int i=0; i<playerCount; i++){
        game->handGenerator(players[i], 2);
    }
    
    int winner = 0;
    
    for(int i=0; i<playerCount; i++){
        if(players[i]->getHandRating() > players[winner]->getHandRating()){
            winner = i;
            continue;
        }
        if(players[i]->getHandRating() == players[winner]->getHandRating() && game->compareHands(players[i]->getHandRating(), players[i]->getCurrentHand(), players[winner]->getCurrentHand())){
            winner = i;
        }
    }
    
//    fstream fout("/Users/krishnakumanan/Documents/poker/poker/poker_hands.txt");

    for(int i=0; i<playerCount; i++){
        int win = 0;
        if(i == winner)
            win = 1;
                
        result += to_string(players[i]->getCard1().value) + "," + to_string(players[i]->getCard1().suitNum) + ","
        + to_string(players[i]->getCard2().value) + "," + to_string(players[i]->getCard2().suitNum) + ","
        + to_string(win) + "\n";
        
//            fout << players[i]->getCard1().value << "," << players[i]->getCard1().suitNum << ","
//            << players[i]->getCard2().value << "," << players[i]->getCard2().suitNum << ","
//            << win << "\n";
                
//        cout << players[i]->getCurrentHand()[0].value << " " << players[i]->getCurrentHand()[0].suitNum << "   "
//        << players[i]->getCurrentHand()[1].value << " " << players[i]->getCurrentHand()[1].suitNum << "   "
//        << players[i]->getCurrentHand()[2].value << " " << players[i]->getCurrentHand()[2].suitNum << "   "
//        << players[i]->getCurrentHand()[3].value << " " << players[i]->getCurrentHand()[3].suitNum << "   "
//        << players[i]->getCurrentHand()[4].value << " " << players[i]->getCurrentHand()[4].suitNum << "      "
//        << win << endl;
    }
    
//    fout.close();
    return result;

}
