//
//  Deck.hpp
//  poker
//
//  Created by Krishna Kumanan on 7/14/24.
//

#ifndef Deck_hpp
#define Deck_hpp

#include <vector>
#include <random>

#include "Card.hpp"
using namespace std;


class Deck{
  public:
    Deck();
//    void shuffle();
    bool burn();
    Card deal();
  private:
    vector<Card> m_cards;
};
#endif /* Deck_hpp */
