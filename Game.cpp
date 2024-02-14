#include "Game.h"
#include <chrono>
#include <thread>
const char* FILLED_CIRCLE = "\u25CF";
const string RESET_COLOR = "\033[0m";

Game::Game(int r, int c, vector<Player>& players, bool useChar, bool sOrder) : board(r, c), players(players), currentPlayerIdx(0), isGameOver(false), invalidMove(false), useCharacters(useChar), snakeOrder(sOrder), snakeReverse(false), winningIdx(-1) {
    colours.push_back("\033[31m");
    colours.push_back("\033[33m");
    colours.push_back("\033[32m");
    colours.push_back("\033[34m");
    colours.push_back("\033[35m");
}

void Game::start() {
    
    while (!isGameOver) {
        display();
        const Player& currentPlayer = players[currentPlayerIdx];  // The 'const' qualifier applies to the 'Player' object that is being referenced. So currentPlayer can refer to different Player objects, and those Player objects are not modified in the function.
        if (!takeTurn(currentPlayer)) {
            invalidMove = true;
            continue;
        }
        if (!isGameOver) {
            switchPlayer();
        }
        
        
    }
    display();

    cout << endl;

    if ( winningIdx == -1 ) {
        cout << "We have ourselves a DRAW";
    }
    else {
        players[winningIdx].incrementWins();
        cout << "And the winner is... " << "\033[1m" << players[winningIdx].getName() << "\033[0m" << endl;
    }
    cout << endl;

    
}

bool Game::takeTurn(const Player& player) {
    bool result = false;
    int column;
    
    if (invalidMove) {
        cout << "Invalid Move! Try again." << endl;
        invalidMove = false;
    }
    cout << endl;
    
    cout << player.getName() << ", enter a column to drop piece: ";
    cin >> column;

    if ( column < 0 || column >= board.getColumns() ) {
        result = false;
        return result;
    }

    result = board.dropPiece(column, player.getPiece());

    if (result) {
        if (board.checkWinner(column)) {
            winningIdx = currentPlayerIdx;
            isGameOver = true;
        }
        else if (board.isBoardFull()) {
            winningIdx = -1;
            isGameOver = true;
        }
        displayDrop(column);
    }

    return result;

}

void Game::switchPlayer() {
    if (snakeOrder) {
        switchPlayerSnake();
    }
    else {
        currentPlayerIdx = (currentPlayerIdx+1) % players.size();
    }
}

void Game::switchPlayerSnake() {

    if (currentPlayerIdx == players.size()-1 && !snakeReverse) {
        snakeReverse = true;
    }
    else if (snakeReverse && currentPlayerIdx != 0) {
        currentPlayerIdx--;
    }
    else if (snakeReverse && currentPlayerIdx == 0) {
        snakeReverse = false;
    }
    else if (!snakeReverse) {
        currentPlayerIdx++;
    }

}

void Game::display() {
    // Clear the terminal screen
    cout << "\033[2J\033[1;1H";

    // Print the column labels
    cout << "\t" << " ";
    for (int col = 0; col < board.getColumns(); col++) {
        cout << "  " << col;
        if (col < 10) {
            cout << " ";
        }
    }
    cout << endl << endl;;

    // Print the grid
    for ( unsigned int r = 0 ; r < board.getRows() ; r++ ) {
        cout << "\t" <<" |"; // Left border of board
        for ( unsigned int c = 0 ; c < board.getColumns() ; c++ ) {
            char piece = board.getPiece(r, c);

            string displayChar = " ";
            if ( piece != '.' ) {
                if (useCharacters) {
                    displayChar = piece;
                }
                else {
                    displayChar = FILLED_CIRCLE;
                }
            }

            string colour = RESET_COLOR;
            for ( unsigned int i = 0 ; i < players.size() ; i++ ) {
                if ( piece == players[i].getPiece() ) {
                    colour = colours[i];
                }
            }

            cout << colour << " " << displayChar << " " << RESET_COLOR << "|";

        }
        cout << endl;

        // Print a row separator
        cout << "\t" << " +";
        for (int col = 0; col < board.getColumns(); col++) {
            cout << "---+";
        }
        cout << endl;

    }
}

void Game::displayDrop(int column) {
    // Clear the terminal screen
    cout << "\033[2J\033[1;1H";

    // Print the column labels
    cout << "\t" << " ";
    for (int col = 0; col < board.getColumns(); col++) {
        cout << "  " << col;
        if (col < 10) {
            cout << " ";
        }
    }
    cout << endl;

    cout << "\t" << " ";

    for (int col = 0; col < board.getColumns(); col++) {
        if (col != column) {
            cout << "  " << " " << " ";
        }
        else {
            if (useCharacters) {
                cout << "  " << colours[currentPlayerIdx] << board.getPiece(board.getTopPieceRow(column), column) << RESET_COLOR << " ";
            }
            else {
                cout << "  " << colours[currentPlayerIdx] << FILLED_CIRCLE << RESET_COLOR << " ";
            }
            
        }
    }

    cout << endl;
    // Print the grid
    for ( unsigned int r = 0 ; r < board.getRows() ; r++ ) {
        cout << "\t" <<" |"; // Left border of board
        for ( unsigned int c = 0 ; c < board.getColumns() ; c++ ) {
            char piece = board.getPiece(r, c);

            string displayChar = " ";
            if ( piece != '.' && !(c == column && r == board.getTopPieceRow(column)) ) {
                if (useCharacters) {
                    displayChar = piece;
                }
                else {
                    displayChar = FILLED_CIRCLE;
                }
            }

            string colour = RESET_COLOR;
            for ( unsigned int i = 0 ; i < players.size() ; i++ ) {
                if ( piece == players[i].getPiece() ) {
                    colour = colours[i];
                }
            }

            cout << colour << " " << displayChar << " " << RESET_COLOR << "|";

        }
        cout << endl;

        // Print a row separator
        cout << "\t" << " +";
        for (int col = 0; col < board.getColumns(); col++) {
            cout << "---+";
        }
        cout << endl;

    }
    this_thread::sleep_for(chrono::milliseconds(200));
    for ( double r = 0 ; r < board.getTopPieceRow(column) ; r = r + 0.5 ) {
        displayDropH(column, r);
        this_thread::sleep_for(chrono::milliseconds(50));
    }
}

void Game::displayDropH(int column, double current_row) {
    // Clear the terminal screen
    cout << "\033[2J\033[1;1H";

    // Print the column labels
    cout << "\t" << " ";
    for (int col = 0; col < board.getColumns(); col++) {
        cout << "  " << col;
        if (col < 10) {
            cout << " ";
        }
    }
    cout << endl << endl;


    // Print the grid
    for ( unsigned int r = 0 ; r < board.getRows() ; r++ ) {
        cout << "\t" <<" |"; // Left border of board
        for ( unsigned int c = 0 ; c < board.getColumns() ; c++ ) {
            char piece = board.getPiece(r, c);

            string displayChar = " ";
            if ( (piece != '.' && !(c == column && r == board.getTopPieceRow(column))) || (c == column && r == current_row) ) {
                if ( useCharacters && c == column && r == current_row )   {
                    displayChar = board.getPiece(board.getTopPieceRow(c), c);
                }
                else if (useCharacters && piece != '.') {
                    displayChar = piece;
                }
                else {
                    displayChar = FILLED_CIRCLE;
                }
            }

            string colour = RESET_COLOR;
            if ( c == column && r == current_row ) {
                piece = board.getPiece(board.getTopPieceRow(column), c);
            }
            for ( unsigned int i = 0 ; i < players.size() ; i++ ) {
                if ( piece == players[i].getPiece() ) {
                    colour = colours[i];
                }
            }

            cout << colour << " " << displayChar << " " << RESET_COLOR << "|";

        }
        cout << endl;

        // Print a row separator
        cout << "\t" << " +";

        for (int col = 0; col < board.getColumns(); col++) {
            if ( col == column && r+0.5 == current_row ) {
                string displayCharHalf = FILLED_CIRCLE;
                if (useCharacters) {
                    displayCharHalf = board.getPiece(board.getTopPieceRow(col), col);
                }
                char pieceHalf = board.getPiece(board.getTopPieceRow(column), col);
                string colourHalf = RESET_COLOR;
                for ( unsigned int i = 0 ; i < players.size() ; i++ ) {
                    if ( pieceHalf == players[i].getPiece() ) {
                        colourHalf = colours[i];
                    }
                }
                cout << "-" << colourHalf << displayCharHalf << RESET_COLOR << "-+";
            }
            else {
                cout << "---+";
            }
            
        }
        cout << endl;

    }
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
}*/