//
//  Game.hpp
//  poker
//
//  Created by Krishna Kumanan on 7/22/24.
//

#ifndef Game_hpp
#define Game_hpp

#include <algorithm>
#include <iostream>
#include "Player.hpp"
using namespace std;

class Table;

//int BIGBLIND = 2;
//int SMALLBLIND = 2;

class Game{
  public:
    Game(Table* mainTable);
    
    string showHand();
    
    string flop();
    string turn();
    string river();
    
    void handGenerator(Player* currentPlayer, int round);
    string whatHand(Card p[5], int& score);
    bool compareHands(int score, Card hand1[5], Card hand2[5]);
    
    bool addPot(string action, int amount, Player* currentPlayer);
    inline void changeCurrentBet(int x){ currentBet = x;}
    void collectBets(bool preflop);
    
//    Player* getPlayer(int x);
//    int getPlayerCount(){return playerCount;}
    inline int getCurrentBet(){ return currentBet;}
    inline int getPot(){ return pot;}
    inline int getFoldCount(){return foldCount;}
    inline Deck* getDeck(){return m_deck;}
    
  private:
    Deck* m_deck;
    Card m_board[5];
    int pot;
    int currentBet;
    int prevRaise;
    int foldCount;
    
    Table* table;

};

#endif /* Game_hpp */
