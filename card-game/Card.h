//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#ifndef CARD_GAME_CARD_H
#define CARD_GAME_CARD_H

#include "Suit.h"

class Card {

private:
    Suit suit;
    int value;

public:
    Card(Suit _suit, int _value): suit(_suit), value(_value) {

    }
};


#endif //CARD_GAME_CARD_H
