//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#ifndef CARD_GAME_PLAYER_H
#define CARD_GAME_PLAYER_H

#include <string>
#include <utility>
#include "DeckBuilder.h"
#include "../lib/logger.h"

class Player {
private:
    std::string name;
    std::unique_ptr<Deck> deck;
    int score;
public:
    explicit Player(std::string  _name): name(std::move(_name)), score(0) {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Creating player : " << name << "\n";
        DeckBuilder deck_builder;
        deck = deck_builder.create()->build();
    }

    virtual ~Player() {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Deleting player \n";
    }

    std::string get_name() const;
};


#endif //CARD_GAME_PLAYER_H
