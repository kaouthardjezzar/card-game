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
    explicit Player(std::string  _name): name(std::move(_name)), deck{}, score(0) {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Creating player : " << name << "\n";
    }

    virtual ~Player() {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Deleting player \n";
    }

    std::string get_name() const;
    std::unique_ptr<Deck>& get_deck();

    void set_deck(std::unique_ptr<Deck>& _deck);

    int get_score();

    void set_score(int n);

    friend ostream & operator << (ostream & out,const Player &player);
};


#endif //CARD_GAME_PLAYER_H
