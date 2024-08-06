//
//  Card.hpp
//  poker
//
//  Created by Krishna Kumanan on 7/14/24.
//

#ifndef Card_hpp
#define Card_hpp

#include <string>
using namespace std;

struct Card{
    string suit;
    int suitNum;
    int value;
    string title;
    bool dealt;
};

#endif /* Card_hpp */
