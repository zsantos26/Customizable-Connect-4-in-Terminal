#include "Game.h"
#include "Player.h"
#include "GameBoard.h"
#include <iostream>

using namespace std;

void snakeOrderPreview(vector<Player> playerList) {
    cout << "\033[2J\033[1;1H";
    cout << "\033[4m" << "Linear/Regular Order" << "\033[0m" << "\t\t\t" << "\033[4m" << "Snake Order" "\033[0m" << endl; 
    cout << "\n\t\t\t" << "\033[1m" << "Round 1" << "\033[0m" << endl;
    for ( unsigned int i = 0 ; i < playerList.size() ; i++ ) {
        cout << "Turn " << i+1 << ": " << playerList[i].getPiece();
        cout << "\t\t\t\t";
        cout << "Turn " << i+1 << ": " << playerList[i].getPiece();
        cout << endl;
    }

    cout << "\n\t\t\t" << "\033[1m" << "Round 2" << "\033[0m" << endl;
    for ( unsigned int i = 0 ; i < playerList.size() ; i++ ) {
        cout << "Turn " << i+1 << ": " << playerList[i].getPiece();
        cout << "\t\t\t\t";
        cout << "Turn " << i+1 << ": " << playerList[playerList.size()-1-i].getPiece();
        cout << endl;
    }
    cout << "\n\t\t    " << "\033[1m" << "{REPEAT CYCLE}" << "\033[0m" << endl;
    cout << endl << endl;
}

void modifySettings(int& rows, int& columns, vector<Player>& playerList, bool& useChar, bool& snakeOrder) {
    bool leaveSettings = false;
    char modifySettingsAns;
    int modifyQuestionAnsInt;
    char modifyQuestionAnsChar;
    int numPlayers;
    string playerName;
    char playerChar;
    

    do {
        modifySettingsAns = 'e';
        cout << "\033[2J\033[1;1H";
        cout << "What would you like to change? " << endl;
        cout << 
        "\tNumber or rows (r)" << endl <<
        "\tNumber of columns (c)" << endl <<
        "\tUse of tokens or characters for pieces (p) " << endl <<
        "\tType of ordering used (o) " << endl <<
        "\tPlayer List (l)" << endl <<
        "\tNothing else. Leave settings (e)" << endl <<
        "Please, input answer: ";

        cin >> modifySettingsAns;
        if ( modifySettingsAns == 'r' || modifySettingsAns == 'R' ) {
            cout << "How many rows would you like now? ";
            cin >> modifyQuestionAnsInt;
            rows = modifyQuestionAnsInt;
        }
        else if ( modifySettingsAns == 'c' || modifySettingsAns == 'C' ) {
            cout << "How many columns would you like now? ";
            cin >> modifyQuestionAnsInt;
            columns = modifyQuestionAnsInt;
        }
        else if ( modifySettingsAns == 'p' || modifySettingsAns == 'P' ) {
            cout << "Would you like to use characters as pieces instead of tokens? (y/n) ";
            cin >> modifyQuestionAnsChar;
            if ( modifyQuestionAnsChar == 'y' || modifyQuestionAnsChar == 'Y' ) {
                useChar = true;
            }
            else {
                useChar = false;
            }
        }
        else if ( modifySettingsAns == 'o' || modifySettingsAns == 'O' ) {
            cout << "Would you like to use a Snake Order rather than Linear/Regular Order? (y/n) ";
            cin >> modifyQuestionAnsChar;
            if ( modifyQuestionAnsChar == 'y' || modifyQuestionAnsChar == 'Y' ) {
                snakeOrder = true;
            }
            else {
                snakeOrder = false;
            }
        }
        else if ( modifySettingsAns == 'l' || modifySettingsAns == 'L' ) {
            cout << "\033[2J\033[1;1H";
            playerList.clear();
            do {
                cout << endl << "How many players would like to play (2-5)? ";
                cin >> numPlayers;
                cout << "\033[2J\033[1;1H";
                if ( !(numPlayers >= 2 && numPlayers <= 5) ) {
                    cout << "Invalid Input!!! ";
                }
            } while ( !(numPlayers >= 2 && numPlayers <= 5) );
                bool flag = false;
                for ( int i = 1 ; i <= numPlayers ; i++ ) {
                    cout << "Player " << i << ", please enter your name: ";
                    cin >> playerName;

                    cout << endl << endl;

                    cout << playerName << ", please input a unique character to represent yourself: ";
                    cin >> playerChar;

                    for ( unsigned int j = 0 ; j < playerList.size() ; j++ ) {
                        if ( playerChar == playerList[j].getPiece() )  {
                            cout << "\033[2J\033[1;1H";
                            cout << "Invalid Player!!! ";
                            i--;
                            flag = true;
                        }
                    }
                    if (flag) {
                        flag = false;
                        continue;
                    }

                    cout << endl;

                    Player newPlayer = Player(playerName, playerChar);
                    playerList.push_back(newPlayer);
                    cout << "\033[2J\033[1;1H";
                }
        }
        else if ( modifySettingsAns == 'e' || modifySettingsAns == 'E' ) {
            leaveSettings = true;
        }
    } while (!leaveSettings);

    return;

}

void displayScore(vector<Player> playerList) {
    // sort
    int currentMax;
    int currentMaxIdx;

    cout << "\033[2J\033[1;1H";
    cout << "\033[1m" << "\033[4m" << "Current Scores" << "\033[0m" << endl << endl;
    
    for ( unsigned int i = 0 ; i < playerList.size() ; i++ ) {
        currentMax = playerList[i].getWins();
        currentMaxIdx = i;
        for ( unsigned int j = i ; j < playerList.size() ; j++ ) {
            if (playerList[j].getWins() > currentMax) {
                currentMax = playerList[j].getWins();
                currentMaxIdx = j;
            }
            swap(playerList[i], playerList[currentMaxIdx]);
        }
    }

    for ( int i = 0 ; i < playerList.size() ; i++ ) {
        cout << i+1 << ". " << playerList[i].getName() << " (" << playerList[i].getPiece() << ") - " << playerList[i].getWins() << " Wins" << endl;
    }
    cout << endl;
    return;
}


int main() {

    int numPlayers;
    vector<Player> playerList;
    string playerName;
    char playerChar;
    int rows = 6;
    int columns = 7;
    bool useChar = false;
    char useCharAns;
    bool snakeOrder = false;
    char snakeOrderAns;
    bool leaveGame = false;
    char nextAns;
    

    cout << "\033[2J\033[1;1H";
    do {
        cout << "How many players would like to play (2-5)? ";
        cin >> numPlayers;
        cout << "\033[2J\033[1;1H";
        if ( !(numPlayers >= 2 && numPlayers <= 5) ) {
            cout << "Invalid Input!!! ";
        }
    } while ( !(numPlayers >= 2 && numPlayers <= 5) );

    bool flag = false;
    for ( int i = 1 ; i <= numPlayers ; i++ ) {
        cout << "Player " << i << ", please enter your name (no spaces): ";
        cin >> playerName;

        cout << endl << endl;

        cout << playerName << ", please input a unique character to represent yourself: ";
        cin >> playerChar;

        for ( unsigned int j = 0 ; j < playerList.size() ; j++ ) {
            if ( playerChar == playerList[j].getPiece() )  {
                cout << "\033[2J\033[1;1H";
                cout << "Invalid Player!!! ";
                i--;
                flag = true;
            }
        }
        if (flag) {
            flag = false;
            continue;
        }

        cout << endl;

        Player newPlayer = Player(playerName, playerChar);
        playerList.push_back(newPlayer);
        cout << "\033[2J\033[1;1H";
    }

    cout << "How many rows would you like the board to have? \nDefault is 6. Due to space constraints, recommend <15: ";
    cin >> rows;
    cout << "\033[2J\033[1;1H";


    cout << "How many columns would you like the board to have? \nDefault is 7. Due to space constraints recommend <20: ";
    cin >> columns;
    cout << "\033[2J\033[1;1H";


    cout << "Would you like to use character representations instead of tokens for pieces? (y/n): ";
    cin >> useCharAns;
    cout << "\033[2J\033[1;1H";
    if ( useCharAns == 'y' || useCharAns == 'Y') {
        useChar = true;
    }


    do {
        cout << "Would you like to use a Snake Order, rather than linear order? (y/n), or enter 's' to show difference between snake and linear order: ";
        cin >> snakeOrderAns;
        if (snakeOrderAns == 's' || snakeOrderAns == 's' ) {
            snakeOrderPreview(playerList);
        }
    } while (snakeOrderAns == 's' || snakeOrderAns == 'S');
    cout << "\033[2J\033[1;1H";

    bool leaveMenu = false;
    do {
        Game * test = new Game(rows, columns, playerList, useChar, snakeOrder);
        test->start(); 

        do {
            cout << "Would you like to modify any settings (m), display the current score (d), continue playing (p) or leave (e/l)? ";
            cin >> nextAns;
            
            leaveMenu = false;
            if (nextAns == 'e' || nextAns == 'E' || nextAns == 'l' || nextAns == 'L') {
                leaveGame = true;
                leaveMenu = true;
            }
            else if ( nextAns == 'm' || nextAns == 'M' ) {
                modifySettings(rows, columns, playerList, useChar, snakeOrder);
            }
            else if (nextAns == 'd' || nextAns == 'D') {
                displayScore(playerList);
            }
            else {
                leaveMenu = true;
            }
        } while (!leaveMenu);

    } while (!leaveGame);

    cout << "\033[2J\033[1;1H";
    
    cout << "\033[1m" << "Thank you for playing!!! Please let me know any suggestions or comments :D ";

    return 0;
}

