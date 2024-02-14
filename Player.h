#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
using namespace std;

class Player{
private:
    string player_name;
    char player_piece;
    unsigned int wins;

public:
    Player(string name, char piece);
    string getName() const;
    char getPiece() const;
    void incrementWins();
    unsigned int getWins() const;

};

#endif // PLAYER_H
