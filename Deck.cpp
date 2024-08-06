//
//  Deck.cpp
//  poker
//
//  Created by Krishna Kumanan on 7/26/24.
//

#include "Deck.hpp"

Deck::Deck()
    : m_cards(52) {
    for(int i=0; i<13; i++){
        m_cards[i].suit = "Spades"; // 0
        m_cards[i+13].suit = "Hearts"; // 1
        m_cards[i+26].suit = "Clubs"; // 2
        m_cards[i+39].suit = "Diamonds"; // 3
        
        m_cards[i].suitNum = 0;
        m_cards[i+13].suitNum = 1;
        m_cards[i+26].suitNum = 2;
        m_cards[i+39].suitNum = 3;
        
        
        m_cards[i].value = i;
        m_cards[i+13].value = i;
        m_cards[i+26].value = i;
        m_cards[i+39].value = i;
        
        if(i == 0){
            m_cards[i].title = "Ace";
            m_cards[i+13].title = "Ace";
            m_cards[i+26].title = "Ace";
            m_cards[i+39].title = "Ace";
        }
        else if(i == 1){
            m_cards[i].title = "Two";
            m_cards[i+13].title = "Two";
            m_cards[i+26].title = "Two";
            m_cards[i+39].title = "Two";
        }
        else if(i == 2){
            m_cards[i].title = "Three";
            m_cards[i+13].title = "Three";
            m_cards[i+26].title = "Three";
            m_cards[i+39].title = "Three";
        }
        else if(i == 3){
            m_cards[i].title = "Four";
            m_cards[i+13].title = "Four";
            m_cards[i+26].title = "Four";
            m_cards[i+39].title = "Four";
        }
        else if(i == 4){
            m_cards[i].title = "Five";
            m_cards[i+13].title = "Five";
            m_cards[i+26].title = "Five";
            m_cards[i+39].title = "Five";
        }
        else if(i == 5){
            m_cards[i].title = "Six";
            m_cards[i+13].title = "Six";
            m_cards[i+26].title = "Six";
            m_cards[i+39].title = "Six";
        }
        else if(i == 6){
            m_cards[i].title = "Seven";
            m_cards[i+13].title = "Seven";
            m_cards[i+26].title = "Seven";
            m_cards[i+39].title = "Seven";
        }
        else if(i == 7){
            m_cards[i].title = "Eight";
            m_cards[i+13].title = "Eight";
            m_cards[i+26].title = "Eight";
            m_cards[i+39].title = "Eight";
        }
        else if(i == 8){
            m_cards[i].title = "Nine";
            m_cards[i+13].title = "Nine";
            m_cards[i+26].title = "Nine";
            m_cards[i+39].title = "Nine";
        }
        else if(i == 9){
            m_cards[i].title = "Ten";
            m_cards[i+13].title = "Ten";
            m_cards[i+26].title = "Ten";
            m_cards[i+39].title = "Ten";
        }
        
        else if(i==10){
            m_cards[i].title = "Jack";
            m_cards[i+13].title = "Jack";
            m_cards[i+26].title = "Jack";
            m_cards[i+39].title = "Jack";
        }
        else if(i==11){
            m_cards[i].title = "Queen";
            m_cards[i+13].title = "Queen";
            m_cards[i+26].title = "Queen";
            m_cards[i+39].title = "Queen";

        }
        else if(i==12){
            m_cards[i].title = "King";
            m_cards[i+13].title = "King";
            m_cards[i+26].title = "King";
            m_cards[i+39].title = "King";
        }

        m_cards[i].dealt = false;
    }
}
//
//
//void Deck::shuffle(){
//    m_cards.shuffle(m_cards.begin(), m_cards.end());
//}
bool Deck::burn(){
    for(int i=0; i<52; i++){
        int x = rand() % 52;
        if(m_cards[x].dealt == false){
            m_cards[x].dealt = true;
            return true;
        }
    }
    return false;
}

Card Deck::deal(){
    for(int i=0; i<52; i++){
        int x = rand() % 52;
        if(m_cards[x].dealt == false){
            m_cards[x].dealt = true;
            return m_cards[x];
        }
    }
    
    Card error;
    error.title = "Zero";
    return error;
}

