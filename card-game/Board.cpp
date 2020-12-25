//
// Created by Ny Andrianina Mamy on 21/12/2020.
//

#include "Board.h"

#include <utility>

void Board::set_deck(std::unique_ptr<Deck> _deck) {
    deck = std::move(_deck);
}

void Board::shuffle_deck() {
    deck->shuffle();
}

void Board::add_player(std::unique_ptr<Player>& player) {
    players.push_back(std::move(player));
}

void Board::affect_cards_toplayer() {
        int a = deck->get_nbcards();
        for (int j = 0; j < (deck->get_nbcards()/ players.size()); j++) {
            for (int k = 0; k < players.size(); k++) {
                players[k]->get_deck().add_card(deck->pick_card(a)->get_suit(),deck->pick_card(a)->get_value());
                a--;
        }
    }
}

std::vector<std::unique_ptr<Player>> Board::get_players() {
    return players;
}

