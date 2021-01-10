//
// Created by Ny Andrianina Mamy on 29/12/2020.
//

#ifndef CARD_GAME_UNO_H
#define CARD_GAME_UNO_H

#include "GameTemplate.h"
#include "../card-game/Board.h"
#include "UnoCards.h"
#include <iostream>

#define SKIPLINE std::cout<<std::endl;

class Uno: public GameTemplate  {
private:
    Board board;

    static bool is_special_card(const Card& card);

    static void compute_special_card(const Card& card, Board& board);

    static void compute_normal_card(const Card& card, Board& board);

    static void display_valid_move(Player& current_player, const Card& card_on_board);

    int make_a_choice();

    void compute_choice(int choice);

    void initialization() ;

    void next_turn() ;

    void first_turn() ;

    void display_game_status();

    bool is_the_end();

    void end_of_game();

    void compute_winner();

public:
    Uno() = default;
    virtual ~Uno() = default;

    void lets_play() override {
        initialization();
        first_turn();
        while(!is_the_end()) {
            next_turn();
        }
        end_of_game();
    }

};


#endif //CARD_GAME_UNO_H
