//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#ifndef CARD_GAME_BATAILLE_H
#define CARD_GAME_BATAILLE_H

#include "GameTemplate.h"
#include "../card-game/Board.h"

class Bataille : public GameTemplate {
private:
    Board board;

protected:

    virtual void initialization();
    // Create cards
    // Create deck
    // Create players

    virtual void next_turn();
    // Choices for Player(s)

    virtual void who_wins_this_turn();
    // Check current game status turn winner

    virtual bool is_the_end();
    // return false till game end

    virtual void end_of_game();

    void compute_winner(Player &player);

public:
    Bataille() {}
    virtual ~Bataille() {}

};


#endif //CARD_GAME_BATAILLE_H
