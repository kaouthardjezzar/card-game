//
// Created by Ny Andrianina Mamy on 21/12/2020.
//

#include "DeckBuilder.h"

#include <utility>

DeckBuilder& DeckBuilder::create() {
    deck = std::unique_ptr<Deck>(new Deck());
    return *this;
}

std::unique_ptr<Deck> DeckBuilder::build() {
    return std::move(deck);
}

DeckBuilder& DeckBuilder::with_suits(std::vector<std::string>& _suits) {
    suits = _suits;
    return *this;
}

DeckBuilder& DeckBuilder::with_range(const std::vector<int>& range) {
    for(const std::string suit: suits) {
        for(int num: range) {
            deck->add_card(suit, num);
        }
    }

    return *this;
}

DeckBuilder& DeckBuilder::with_range(int left, int right) {
    std::vector<int> range;
    for(int i = left; i < right + 1; ++i){
        range.push_back(i);
    }
    return with_range(range);
}
