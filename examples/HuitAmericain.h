//
// Created by Kaou Thaar on 02/01/2021.
//

#ifndef CARD_GAME_HUITAMERICAIN_H
#define CARD_GAME_HUITAMERICAIN_H

#include "GameTemplate.h"
#include "../card-game/Board.h"

class HuitAmericain : public GameTemplate {
private:
    Board board;
    std::vector<string> special_cards = {"8", "joker", "11", "1", "2"};

    void first_turn();
    bool isSpecialCard(const Card card);

    void display_game_status(std::vector<bool> winner);

    void who_wins_this_turn();

    void compute_winner(std::vector<bool> winner);
protected:
    void initialization() override;

    void next_turn() override;

    bool is_the_end() override;

    void end_of_game() override;

public:
    HuitAmericain() = default;
    virtual ~HuitAmericain() = default;
};


#endif //CARD_GAME_HUITAMERICAIN_H
