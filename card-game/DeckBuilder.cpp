//
// Created by Ny Andrianina Mamy on 21/12/2020.
//

#include "DeckBuilder.h"

#include <utility>

DeckBuilder* DeckBuilder::create() {
    deck = std::unique_ptr<Deck>(new Deck());
    return this;
}

std::unique_ptr<Deck> DeckBuilder::build() {
    return std::move(deck);
}

DeckBuilder* DeckBuilder::with_suits(std::vector<Suit> suits) {
    deck->set_suits(std::move(suits));
    return this;
}

DeckBuilder* DeckBuilder::with_range(const std::vector<int>& range) {
    for(Suit suit: deck->get_suits()) {
        for(int num: range) {
            deck->add_card(suit, num);
        }
    }

    return this;
}