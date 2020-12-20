//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#ifndef CARD_GAME_PLAYER_H
#define CARD_GAME_PLAYER_H

#include <string>

class Deck;

class Player {
private:
    std::string name;
    Deck *deck;

public:
    Player() {}
};


#endif //CARD_GAME_PLAYER_H
