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
    std::unique_ptr<Deck> temp_deck; // Used to hold temporary cards for score computation
    int round;

public:
    explicit Board(): deck{new Deck()}, players{}, temp_deck{new Deck()}, round{0} {
    }

    virtual ~Board() = default;

    void set_deck(std::unique_ptr<Deck> _deck);

    Deck& get_deck() {
        return *deck;
    }

    Deck& get_temp_deck() {
        return *temp_deck;
    }

    void increase_round() {
        round++;
    }

    int get_round() const {
        return round;
    }

    void shuffle_deck();

    void add_player(std::unique_ptr<Player>& player); // unique_ptr to transfer player ownership to board

    void affect_decks_toplayers(std::vector<std::unique_ptr<Deck>>& decks);

    std::vector<std::unique_ptr<Player>>& get_players();

};

#endif //CARD_GAME_BOARD_H
