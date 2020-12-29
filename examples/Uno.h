//
// Created by Ny Andrianina Mamy on 29/12/2020.
//

#ifndef CARD_GAME_UNO_H
#define CARD_GAME_UNO_H

#include "GameTemplate.h"
#include "../card-game/Board.h"

class Uno : public GameTemplate {
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
    Uno() {}
    virtual ~Uno() {}

};


#endif //CARD_GAME_UNO_H
