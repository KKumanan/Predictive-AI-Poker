//
//  Table.hpp
//  poker
//
//  Created by Krishna Kumanan on 7/26/24.
//

#ifndef Table_hpp
#define Table_hpp

#include <iostream>
#include <fstream>
using namespace std;

class Game;
class Player;

class Table{
public:
    Table(int p);
    ~Table();
    void runGame();
    string dataGen();
    void changeDealer();
    
    Player* getPlayer(int x);
    
    inline int getPlayerCount(){return playerCount;}
    inline int getDealer(){return dealer;}
    inline int getBb(){return bb;}
    inline int getSb(){return sb;}

    
private:
    vector<Player*> players;
    int playerCount;
    int dealer;
    int bb;
    int sb;
    Game* game;
};
#endif /* Table_hpp */
