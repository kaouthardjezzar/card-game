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
    std::vector<int> special_cards = {8 , 0, 1, 11,2};

    void first_turn();
    bool isSpecialCard(const Card card);

    void excute_round();

    bool chooseCard();

    bool validCard (Card &card);

    void displayPlayerStat(int pos);

    void specialProcess();

protected:
    void initialization() ;

    void next_turn() ;

    bool is_the_end() ;

    void end_of_game() ;

public:
    HuitAmericain() = default;
    virtual ~HuitAmericain() = default;
    void lets_play() override;
};


#endif //CARD_GAME_HUITAMERICAIN_H
