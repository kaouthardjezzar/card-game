//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#include "GameTemplate.h"

void GameTemplate::lets_play() {
        // Get called by main function
        // How to arrange function call
        initialization();
        while(!is_the_end()) {
            next_turn();
            who_wins_this_turn();
        }
}
