//
//  Player.cpp
//  poker
//
//  Created by Krishna Kumanan on 7/26/24.
//

#include "Player.hpp"

Player::Player(string n){
    name = n;
}

void Player::dealHand(Deck* mainDeck){
    hand[0] = mainDeck->deal();
    hand[1] = mainDeck->deal();
}

string Player::viewHand(){
    return hand[0].title + " of " + hand[0].suit + ",  " + hand[1].title + " of " + hand[1].suit;
}

Card Player::getCard1(){
    return hand[0];
}

Card Player::getCard2(){
    return hand[1];
}

int Player::getHandRating(){
    return handRating;
}

int Player::getBalance(){
    return balance;
}

void Player::setHandRating(int x){
    handRating = x;
}

void Player::changeBalance(int x){
    balance += x;
}

void Player::setFold(){
    folded = true;
}

void Player::setHand(Card h[]){
    for(int i=0; i<5; i++){
        currentHand[i] = h[i];
    }
}
