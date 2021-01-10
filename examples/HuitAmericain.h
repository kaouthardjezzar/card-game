//
// Created by Kaou Thaar on 02/01/2021.
//

#ifndef CARD_GAME_HUITAMERICAIN_H
#define CARD_GAME_HUITAMERICAIN_H

#include "GameTemplate.h"
#include "../card-game/Board.h"

class HuitAmericain : public GameTemplate {
private:
    std::vector<int> special_cards = {8 , 0, 1, 11,2};

    void initialization() override;

    void first_turn();

    void excute_round();

    bool chooseCard();

    bool isSpecialCard(const Card card);

    bool validCard (Card &card);

    void specialProcess();

    void displayPlayerStat(int pos);

    int count_card(Card & card);

    void next_turn() override;

    bool is_the_end() override;

    void end_of_game() override;

public:
    HuitAmericain() = default;
    virtual ~HuitAmericain() = default;
    void lets_play(std::vector<std::string> players);
};


#endif //CARD_GAME_HUITAMERICAIN_H
