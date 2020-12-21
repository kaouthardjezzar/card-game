//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#include <iostream>
#include "Bataille.h"
#include "../card-game/Board.h"

bool play_bataille() {

    /*
    // Shuffle deck
    // while (!end_game)
     // Turn begins here
a:   Display game status
     Wait for draw
     Draw
     Check current turn winner // Should be on game start section
         If A wins over B:
            Add A.card and B.card to TEMP
            Add TEMP to A.deck
         Else if : same for B
         Else if no winner :
            // Add cards to TEMP
            goto a:

     Display final score

    */


    return true; // When game is finished
}

void Bataille::who_wins_this_turn() {

}

void Bataille::next_turn() {

}

void Bataille::initialization() {
    std::cout << "Launching Bataille " << std::endl;
    board.build_deck();
}

bool Bataille::is_the_end() {
    return true;
}
