//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#ifndef CARD_GAME_CARD_H
#define CARD_GAME_CARD_H

#include <iostream>
#include "../lib/logger.h"
#include "Suit.h"


class Card {

private:
    Suit suit;
    int value;

public:
    Card(Suit _suit, int _value): suit(_suit), value(_value) {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Creating card : " << " suit " << " , " << value << "\n";
    }

    virtual ~Card() {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Deleting card \n";
    }

    int get_value() const;
};


#endif //CARD_GAME_CARD_H
