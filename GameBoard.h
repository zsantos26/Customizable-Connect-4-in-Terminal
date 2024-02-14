#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <chrono> 
#include <thread>
using namespace std;

class GameBoard{
private:
    int rows;
    int columns;
    vector<vector<char> > grid; // outer vector: rows - inner vector: columns (of that row) - grid[row][columns]

public:
    // Constructor
    // Initializes board with specified number of rows and columns - for playing custom games
    GameBoard(int r, int c);

    int getColumns() const;

    int getRows() const;

    char getPiece(int row, int column) const;

    int getTopPieceRow(int column) const;

    // dropPiece - attempts to frop piece in specified columns
    // Returns true if piece is sucesfully dropped, false otherwise              
    bool dropPiece(int column, char piece);

    // isBoardFull - checks if board is completely filled with pieces
    // Return true if full, false otherwise
    bool isBoardFull() const; // const in c++ apparently indicates method is 'const member function' - promises not to modify the state of the object it belongs to. For compiler and programmers to know method won't alter state of GameBoard

    // isColumnFull - checks if column is completely filled with pieces
    // Return true if full, false otherwise
    bool isColumnFull(int column) const;

    // checkWinner - checks board for win-conditions
    // Returns true if a winner is found, false otherwise
    bool checkWinner(int column) const;

    // display - shows current state of game to console
    void display() const;


};

#endif // GAMEBOARD_H
