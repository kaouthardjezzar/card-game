//
// Created by Ny Andrianina Mamy on 29/12/2020.
//

#ifndef CARD_GAME_UNO_H
#define CARD_GAME_UNO_H

#include "GameTemplate.h"
#include "../card-game/Board.h"
#include <iostream>

class Uno : public GameTemplate {
private:
    Board board;

    void display_game_status(std::vector<bool> winner);

    void who_wins_this_turn(std::vector<bool>& winner, int choice);

    void compute_winner(std::vector<bool>& winner);

    void a_player_wins(Player &player);

protected:
    void initialization() override;

    void next_turn() override;

    bool is_the_end() override;

    void end_of_game() override;

public:
    Uno() = default;
    virtual ~Uno() = default;

};


#endif //CARD_GAME_UNO_H
