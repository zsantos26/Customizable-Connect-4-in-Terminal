#ifndef GAME_H
#define GAME_H
#include "GameBoard.h"
#include "Player.h"

using namespace std;

class Game {
private:
    GameBoard board;
    vector<Player>& players;
    int currentPlayerIdx;
    bool isGameOver;
    bool invalidMove;
    vector<string> colours;
    bool useCharacters;
    bool snakeOrder;
    bool snakeReverse;
    int winningIdx;

    void switchPlayer();
    void switchPlayerSnake();
    bool takeTurn(const Player& player);


public:
    Game(int r, int c, vector<Player>& players, bool useChar, bool sOrder); // The 'const' qualifier applies to the 'Player' object that is being referenced.
    void start();
    void display();
    void displayDrop(int column);
    void displayDropH(int column, double current_row);
};

#endif // GAME_H


