#include "GameBoard.h"
#include <iostream>
#include <cassert>

using namespace std;
/*
// ANSI Escape Codes for coloring
const string RED = "\033[31m";
const string YELLOW = "\033[33m";
const string RESET_COLOR = "\033[0m";
const char* FILLED_CIRCLE = "\u25CF";
*/
// Constructor
// Initializes board with specified number of rows and columns - for playing custom games
GameBoard::GameBoard(int r, int c) : rows(r), columns(c), grid(r, vector<char>(c, '.')) { // grid(r, vector<char>(c, '.') - initializes a vector with r elements, each of the r element is a vector with c elements, each element of the c elements is a char with value '.'
    assert(rows > 0 && columns > 0); // Asserting invariants. rows and columns must be positives
}


int GameBoard::getColumns() const{
    return columns;
}

int GameBoard::getRows() const{
    return rows;
}

char GameBoard::getPiece(int row, int column) const {
    return grid[row][column];
}

int GameBoard::getTopPieceRow(int column) const {
    int r = 0;
    while (grid[r][column] == '.' && r < rows-1 ) {
        r++;
    }
    return r;
}

// dropPiece - attempts to frop piece in specified columns
// Precondition: column is within range [0, columns). The column is not full
// Returns true if piece is sucesfully dropped, false otherwise              
bool GameBoard::dropPiece(int column, char piece) {
    bool result = false;
    int r = rows-1;

    // Ensure column is valid
    assert(column >= 0 && column < columns);

    if ( isColumnFull(column) ) {
        return result;
    }

    while ( grid[r][column] != '.' ) {
        r--;
    }
    if ( grid[r][column] == '.' ) {
        grid[r][column] = piece;
        result = true;
        return result;
    }
    
    // Safety net - should not be reached if previous checks are correct
    return result;
    
}

// isBoardFull - checks if board is completely filled with pieces
// Return true if full, false otherwise
bool GameBoard::isBoardFull() const {
    bool result = true;
    for (unsigned int i = 0 ; i < columns ; i++) {
        // if there isn't a full column
        if ( !isColumnFull(i) ) {
            result = false;  // return false - board is not gull
        }
    }
    return result;
}

// isColumnFull - checks if column is completely filled with pieces
// Return true if full, false otherwise
bool GameBoard::isColumnFull(int column) const {
    bool result = false;
    // if top row of specified column isn't vacant
    if ( grid[0][column] != '.' ) {
        result = true; // return true - column is full
    }

    return result;
}

// checkWinner - checks board for win-conditions
// Input: The column of the most recent piece dropper
// To be called after each succesfull dropPiece
// Returns true if a winner is found, false otherwise
bool GameBoard::checkWinner(int column) const {
    bool result = false;
    char piece = '.';
    int r = 0;
    int count = 0;
    const int win_count = 4;
    // condition checker variables - to help with counting and checking horizontal an diagonal win conditions. Not needed for vertical since it is much more simple - just check and count three pieces below. While horizontal and diagonal need to count multiple directions, so more complicated
    bool continue_count = true; 

    // Ensure input is valid. Safety net - since called after 'drop piece' with same column input, should already be checked.
    assert(column >= 0 && column < columns);
    
    // Look for piece last dropped in column. Find first empty row of specified column.
    while (grid[r][column] == '.') {
        r++;
    }
    piece = grid[r][column];

    // Ensure piece doesn't have value '.' anymore. Safety net - should not be reached if previous checks are correct
    assert(piece != '.');

    // check vertical win-condition
    count = 1;
    // check if 3 pieces below all match
    for ( unsigned int v = 1 ; v < win_count ; v++ ) {
        // Ensure row being checked is valid - above or on bottom (rows)-1 row.
        if ( r+v < rows ) {
            if ( grid[r+v][column] == piece ) {
                count++;
            }
        }

    }
    if ( count == win_count ) {
        result = true;
        return true;
    }

    // check horizontal win-condition
    count = 1;
    // Horizontal win-condition section, variable declaration - maybe put above with other variable declarations. However, might just to make it clear, putting here for now
    int column_displacer = 1;


    // count consecutive pieces to the left of placed piece
    while ( continue_count ) {
        // check if column is valid - to the right or on very left (0) column
        if ( column-column_displacer >= 0 ) {
            // check if piece to the left (by column_displacer) is same piece
            if ( grid[r][column-column_displacer] == piece ) {
                count++;
                column_displacer++;
            }
            else {
                continue_count = false;
            }
        }
        else {
            continue_count = false;
        }
    }

    // reset condition variables
    continue_count = true;
    column_displacer = 1;
    // count consecutive pieces to the right of placed piece
    while ( continue_count ) {
        // check if column is valid - to the left or on very right (column-1) column
        if ( column+column_displacer < columns ) {
            if ( grid[r][column+column_displacer] == piece ) {
                count++;
                column_displacer++;
            }
            else {
                continue_count = false;
            }
        }
        else {
            continue_count = false;
        }
    }

    if ( count >= win_count ) {
        result = true;
        return result;
    }


    // check diagonal win_conditions

    // check top left to bottom right '\' diagonal
    // reset condition variables
    count = 1;
    continue_count = true;
    // here, column displacer will act as column AND row displacer. To keep it simple, will just keep column displacer, since it is intuitive that column displacer also means row displacer for diagonals
    column_displacer = 1;

    // count consecutive pieces to the left and above 
    while ( continue_count ) {
        // check if column is valid (column-coumn_displace on or on right of very left (0) column) and row is valid (r on or below top (0) row
        if ( column-column_displacer >= 0 && r-column_displacer >= 0 ) {
            if ( grid[r-column_displacer][column-column_displacer] == piece ) {
                count++;
                column_displacer++;
            }
            else {
                continue_count = false;
            }
        }
        else {
            continue_count = false;
        }
    }

    // reset condition variable, but continue count for pieces to right right and down of specified placed pliece
    continue_count = true;
    column_displacer = 1;

    while ( continue_count ) {
        // check if column is valid (column+column_displacer < )
        if ( column+column_displacer < columns && r+column_displacer < rows ) {
            if ( grid[r+column_displacer][column+column_displacer] == piece) {
                count++;
                column_displacer++;
            }
            else {
                continue_count = false;
            }
        }
        else {
            continue_count = false;
        }
    }

    if ( count >= win_count ) {
        result = true;
        return result;
    }


    // check bottom left to top right '/' diagonal
    count = 1;
    continue_count = true;
    column_displacer = 1;

    // count consecutive pieces to the left and down
    while ( continue_count ) {
        // check if column is on or to the right of very left (0) column and row is above or on bottom (rows-1) row
        if ( column-column_displacer >= 0 && r+column_displacer < rows ) {
            if ( grid[r+column_displacer][column-column_displacer] == piece ) {
                count++;
                column_displacer++;
            }
            else {
                continue_count = false;
            }
        }
        else {
            continue_count = false;
        }
    }
    // reset condition variable, but continue count for pieces to right and above specified placed piece
    continue_count = true;
    column_displacer = 1;

    while ( continue_count ) {
        // check if column is on or to the left of most right (columns-1) column, and row is on or below top (0) row
        if ( column+column_displacer && r-column_displacer >= 0 ) {
            if ( grid[r-column_displacer][column+column_displacer] == piece ) {
                count++;
                column_displacer++;
            }
            else {
                continue_count = false;
            }
        }
        else {
            continue_count = false;
        }
    }
    
    if ( count >= win_count ) {
        result = true;
        return result;
    }

    return result;
}


/*
void GameBoard::display() const{
    // Clear the terminal screen
    std::cout << "\033[2J\033[1;1H";

    // Print the column labels
    std::cout << " ";
    for (int col = 0; col < columns; col++) {
        std::cout << "  " << col << " ";
    }
    std::cout << std::endl;

    // Print the grid
    for (int row = 0; row < rows; row++) {
        std::cout << " |"; // Left border of the board
        for (int col = 0; col < columns; col++) {
            // Choose color based on player piece
            string color = (grid[row][col] == 'A') ? RED : (grid[row][col] == 'B') ? YELLOW : RESET_COLOR;
            char displayChar = (grid[row][col] != '.') ? grid[row][col] : ' '; // Replace '.' with space for empty slots
            cout << color << " " << FILLED_CIRCLE << " " << RESET_COLOR << "|"; // Player piece and right border
        }
        std::cout << std::endl;

        // Print a row separator
        std::cout << " +";
        for (int col = 0; col < columns; ++col) {
            std::cout << "---+";
        }
        std::cout << std::endl;
    }
}
*/