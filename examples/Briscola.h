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
    void first_turn();

protected:
    void initialization() override;

    void next_turn() override;

    bool is_the_end() override;

    void end_of_game() override;

public:
    Briscola() = default;
    virtual ~Briscola() = default;
};


#endif //BOARD_H_BRISCOLA_H
