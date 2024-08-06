#ifndef Player_hpp
#define Player_hpp

#include "Deck.hpp"
using namespace std;

class Player{
  public:
    Player(string n);
    void dealHand(Deck* mainDeck);
    string viewHand();
    
    Card getCard1();
    Card getCard2();
    int getHandRating();
    int getBalance();
    inline bool getFold(){return folded;}
    inline string getName(){return name;}
    Card* getCurrentHand(){return currentHand;}
    
    void setHandRating(int x);
    void changeBalance(int x);
    void setFold();
    void setHand(Card h[]);
    
  private:
    string name;
    Card hand[2];
    int handRating;
    Card currentHand[5];
    int balance=100;
    
    bool folded = false;
};
#endif /* Player_hpp */
