//
// Created by Ny Andrianina Mamy on 09/01/2021.
//

#ifndef CARD_GAME_SCOPA_H
#define CARD_GAME_SCOPA_H

#include "../card-game/Board.h"
#include "GameTemplate.h"
#include <iostream>

class Scopa: public GameTemplate {
private:
    void display_game_status();

    int make_a_choice();

    void compute_choice(int choice);

    void display_valid_move(Player& current_player);

    void initialization() override;

    void next_turn() override;

    void first_turn() override;

    bool is_the_end() override;

    void end_of_game() override;

public:
    Scopa() = default;
    virtual ~Scopa() = default;

};

bool is_correct_move(Deck& deck, const Card& player_move);
int is_same_value(Deck& deck, const Card& player_move);

#endif //CARD_GAME_SCOPA_H
