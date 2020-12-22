//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#include "Deck.h"

void Deck::shuffle() {

}

Card *Deck::pick_random(int) {
    return NULL;
}

void Deck::set_suits(std::vector <Suit> _suits) {
    suits = std::move(_suits);
}

std::vector<Suit> Deck::get_suits() {
    return suits;
}

void Deck::add_card(Suit suit, int value) {
    cards.push_back(std::unique_ptr<Card>(new Card(suit, value)));
}
