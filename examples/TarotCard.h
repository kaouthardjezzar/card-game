//
// Created by Ny Andrianina Mamy on 09/01/2021.
//

#ifndef CARD_GAME_TAROTCARD_H
#define CARD_GAME_TAROTCARD_H

#include "../card-game/Card.h"
#include <iostream>

#define ATOUT "Atouts"
#define EXCUSE "Excuse"


class TarotCard: public Card {
public:
    bool operator>(const Card& c) const override;
    bool operator<(const Card& c) const override;
    bool operator==(const Card& c) const override;
    friend ostream & operator << (ostream & out, Card & aCard);
};


#endif //CARD_GAME_TAROTCARD_H
