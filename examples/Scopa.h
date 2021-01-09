//
// Created by Ny Andrianina Mamy on 09/01/2021.
//

#ifndef CARD_GAME_SCOPA_H
#define CARD_GAME_SCOPA_H

#include "../card-game/Board.h"
#include <iostream>

class Scopa {
private:
    Board board;

    void initialization() ;

    void next_turn() ;

    void first_turn() ;

    bool is_the_end();

    void end_of_game();

    void display_game_status();

public:
    Scopa() = default;
    virtual ~Scopa() = default;

    void lets_play() {
        initialization();
        first_turn();
        while(!is_the_end()) {
            next_turn();
        }
        end_of_game();
    }


};


#endif //CARD_GAME_SCOPA_H
