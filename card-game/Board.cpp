//
// Created by Ny Andrianina Mamy on 21/12/2020.
//

#include "Board.h"

void Board::build_deck() {
    DeckBuilder deck_builder;

    std::vector<Suit> suits{Suit::spade};
    std::vector<int> range{1,2,3,4,5};

    std::unique_ptr<Deck> test = deck_builder.create()->with_suits(suits)->with_range(range)->build();
}
