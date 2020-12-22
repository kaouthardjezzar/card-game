//
// Created by Ny Andrianina Mamy on 21/12/2020.
//

#include "Board.h"

#include <utility>

void Board::set_deck(std::unique_ptr<Deck> _deck) {
    deck = std::move(_deck);
}
