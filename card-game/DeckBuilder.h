//
// Created by Ny Andrianina Mamy on 21/12/2020.
//

#ifndef CARD_GAME_DECKBUILDER_H
#define CARD_GAME_DECKBUILDER_H

#include <memory>
#include <vector>
#include "Deck.h"
#include "Card.h"

class DeckBuilder {
private:
    std::unique_ptr<Deck> deck;

public:
    DeckBuilder() = default;
    virtual ~DeckBuilder() = default;

    DeckBuilder* create();
    std::unique_ptr<Deck> build();
    DeckBuilder* with_suits(std::vector<Suit> suits);
    DeckBuilder* with_range(const std::vector<int>& range);
};

#endif //CARD_GAME_DECKBUILDER_H
