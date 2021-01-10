//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#include "GameTemplate.h"

void GameTemplate::lets_play() {
        initialization();
        first_turn();
        while(!is_the_end()) {
            next_turn();
        }
        end_of_game();
}

void GameTemplate::initialization() {

}

void GameTemplate::first_turn() {

}

bool GameTemplate::is_the_end() {
    return board.get_deck().isEmpty();
}

void GameTemplate::next_turn() {

}

void GameTemplate::end_of_game() {

}
