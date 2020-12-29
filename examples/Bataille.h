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

    void display_game_status(std::vector<bool> winner);

    void who_wins_this_turn(std::vector<bool>& winner);

    void compute_winner(std::vector<bool> winner);

    void a_player_wins(Player &player);

protected:
    virtual void initialization();

    virtual void next_turn();

    virtual bool is_the_end();

    virtual void end_of_game();

public:
    Bataille() {}
    virtual ~Bataille() {}

};


#endif //CARD_GAME_BATAILLE_H
