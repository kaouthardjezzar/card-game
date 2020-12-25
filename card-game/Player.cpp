//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#include "Player.h"

std::string Player::get_name() const {
    return name;
}
Deck Player::get_deck() {
    return *deck;
}

void Player::increment()// incrementer le score du joueur
{
    score=+2;
}

int Player::get_score() {
    return score;
}