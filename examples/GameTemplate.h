//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#ifndef CARD_GAME_GAMETEMPLATE_H
#define CARD_GAME_GAMETEMPLATE_H


class GameTemplate { // Singleton

    // Players []
    // Scores []
    // Cards on Table []

    void let_the_battle_begin() { // Get called by main function
        // How to arrange function call
        initialization();
        while(!is_the_end()) {
            next_turn();
            who_wins_this_turn();
        }
    }

    void initialization() {
        // Create cards
        // Create deck
        // Create players
    }

    void next_turn() { // Choices for Player(s)

    }

    void who_wins_this_turn() {
        // Check current game status turn winner
    }

    bool is_the_end() {
        return false; // return false till game ends
    }

};


#endif //CARD_GAME_GAMETEMPLATE_H
