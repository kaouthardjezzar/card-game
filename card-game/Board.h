//
// Created by Ny Andrianina Mamy on 21/12/2020.
//

#ifndef CARD_GAME_BOARD_H
#define CARD_GAME_BOARD_H

#include <vector>
#include <memory>
#include "DeckBuilder.h"

class Player;

class Board {
private:
    std::unique_ptr<Deck> deck;
    std::vector<Player*> players;

public:
    explicit Board() {
    }
    virtual ~Board() = default;

    void build_deck();

//    void addDeck(Deck* deck);

//    void addPlayer(Player* player);

};

#endif //CARD_GAME_BOARD_H
