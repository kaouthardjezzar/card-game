//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#ifndef CARD_GAME_DECK_H
#define CARD_GAME_DECK_H

#include <vector>
#include <memory>
#include "Card.h"


class Deck {
private:
    std::vector<std::unique_ptr<Card>> cards;
public:
    Deck() {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Creating Deck \n";
    }
    virtual ~Deck() {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Deleting Deck containing" << " , Cards : " << cards.size() << "\n";
    }

    void add_card(std::string suit, int value);
    void shuffle();
    Card* pick_random(int);

};


#endif //CARD_GAME_DECK_H
