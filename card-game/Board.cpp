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

void Board::affect_decks_toplayers(std::vector<std::unique_ptr<Deck>>& decks) {
    for(int i=0; i < get_players().size(); ++i) {
        get_players()[i]->set_deck(decks[i]);
    }
}

std::vector<std::unique_ptr<Player>>& Board::get_players() {
    return players;
}

