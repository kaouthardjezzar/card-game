//
// Created by Ny Andrianina Mamy on 29/12/2020.
//

#ifndef CARD_GAME_UNO_H
#define CARD_GAME_UNO_H

#include "GameTemplate.h"
#include "../card-game/Board.h"
#include "UnoCards.h"
#include <iostream>

class Uno: public GameTemplate  {
private:
    static bool is_special_card(const Card& card);

    static void compute_special_card(const Card& card, Board& board);

    static void compute_normal_card(const Card& card, Board& board);

    static void display_valid_move(Player& current_player, const Card& card_on_board);

    int make_a_choice();

    void compute_choice(int choice);

    void display_game_status();

    void compute_winner();

    void initialization() override ;

    void next_turn() override ;

    void first_turn() override ;

    bool is_the_end() override;

    void end_of_game() override;

public:
    Uno() = default;
    virtual ~Uno() = default;
};


#endif //CARD_GAME_UNO_H
