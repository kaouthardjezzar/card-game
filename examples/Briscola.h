//
// Created by Kaou Thaar on 09/01/2021.
//

#ifndef BOARD_H_BRISCOLA_H
#define BOARD_H_BRISCOLA_H

#include "GameTemplate.h"
#include "../card-game/Board.h"

class Briscola : public GameTemplate {
private:
    Board board;

    unique_ptr<Card> atout;

    std::vector<int> points ;

    void first_turn();

    void display_game_status(std::vector<bool> winner);

    void who_wins_this_turn(std::vector<bool>& winner);

    void compute_winner(std::vector<bool> winner);

    Card& chooseCard ();

    bool validCard (Card &card);

    void end_of_manche();


protected:
    void initialization() override;

    void next_turn() override;

    bool is_the_end() override;

    void end_of_game() override;


public:
    Briscola() = default;
    virtual ~Briscola() = default;
    void lets_play();

};


#endif //BOARD_H_BRISCOLA_H
