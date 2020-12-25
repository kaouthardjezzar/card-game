//
// Created by Ny Andrianina Mamy on 21/12/2020.
//

#ifndef CARD_GAME_BOARD_H
#define CARD_GAME_BOARD_H

#include <vector>
#include <memory>
#include "DeckBuilder.h"
#include "Player.h"

class Board {
private:
    std::unique_ptr<Deck> deck; //52
    std::vector<std::unique_ptr<Player>> players; // 2
    std::unique_ptr<Deck> temporary; // T

public:
    explicit Board() {
    }

    virtual ~Board() = default;

    void set_deck(std::unique_ptr<Deck> _deck);

    void shuffle_deck();
//    void addDeck(Deck* deck);

    void add_player(std::unique_ptr<Player>& player); // unique_ptr to transfer player ownership to board

    void affect_cards_toplayer();
};

#endif //CARD_GAME_BOARD_H
