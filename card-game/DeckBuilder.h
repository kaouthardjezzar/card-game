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
    std::vector<std::string> suits;

public:
    DeckBuilder() = default;
    virtual ~DeckBuilder() = default;

    // Using references
    DeckBuilder& create();
    std::unique_ptr<Deck> build();
    DeckBuilder& with_suits(std::vector<std::string>& suits);
    DeckBuilder& with_range(const std::vector<int>& range);
    DeckBuilder& with_range(int left, int right);
};

#endif //CARD_GAME_DECKBUILDER_H
