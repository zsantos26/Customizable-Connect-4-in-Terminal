#include "Player.h"
#include <iostream>
#include <cassert>

using namespace std;

Player::Player(string name, char piece) : player_name(name), player_piece(piece), wins(0) {}

string Player::getName() const {
    return player_name;
}

char Player::getPiece() const {
    return player_piece;
}

void Player::incrementWins() {
    wins++;
}

unsigned int Player::getWins() const {
    return wins;
}