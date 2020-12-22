//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#include "Deck.h"

void Deck::shuffle() {

}

Card *Deck::pick_random(int) {
    return NULL;
}

void Deck::add_card(Suit suit, int value) {
    cards.push_back(std::unique_ptr<Card>(new Card(suit, value)));
}
