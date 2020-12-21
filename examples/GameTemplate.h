//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#ifndef CARD_GAME_GAMETEMPLATE_H
#define CARD_GAME_GAMETEMPLATE_H


class GameTemplate { // Abstract
protected:
    // Players []
    // Scores []
    // Cards on Table []

    virtual void initialization() = 0;
    // Create cards
        // Create deck
        // Create players

    virtual void next_turn() = 0; // Choices for Player(s)

    virtual void who_wins_this_turn() = 0;
        // Check current game status turn winner

    virtual bool is_the_end() = 0;
        // return false till game end

public:
    void lets_play();
};


#endif //CARD_GAME_GAMETEMPLATE_H
