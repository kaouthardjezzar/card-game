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
    /*
     * Contient le deck à créer
     */
    std::unique_ptr<Deck> deck;

    /*
     * Contient la suite des cartes
     */
    std::vector<std::string> suits;

public:
    DeckBuilder() = default;
    virtual ~DeckBuilder() = default;

    /*
     * Crée une instance de deck
     */
    DeckBuilder& create();

    /*
     * Configure la suite des cartes
     */
    DeckBuilder& with_suits(std::vector<std::string>& suits);

    /*
     * Configure le numéro des cartes
     */
    DeckBuilder& with_range(const std::vector<int>& range);
    DeckBuilder& with_range(int left, int right);

    /*
     * Renvoie une instance de deck
     */
    std::unique_ptr<Deck> build();
};

#endif //CARD_GAME_DECKBUILDER_H
