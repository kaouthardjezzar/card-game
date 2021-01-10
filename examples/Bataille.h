//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#ifndef CARD_GAME_BATAILLE_H
#define CARD_GAME_BATAILLE_H

#include "GameTemplate.h"
#include "../card-game/Board.h"

class Bataille : public GameTemplate {
private:
    void display_game_status(std::vector<bool> winner);

    void who_wins_this_turn(std::vector<bool>& winner);

    void compute_winner(std::vector<bool> winner);

    void a_player_wins(Player &player);

protected:
    void initialization() override;

    void first_turn() override;

    void next_turn() override;

    bool is_the_end() override;

    void end_of_game() override;

public:
    Bataille() = default;
    virtual ~Bataille() = default;
};


#endif //CARD_GAME_BATAILLE_H
