//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#include "Deck.h"
#include <algorithm>
#include <random>



void Deck::split(std::vector<std::unique_ptr<Deck>>& decks, int parts) {
    if(parts != 2) {
        std::cerr << "Only split to two parts" << std::endl;
        return;
    }
    int half = (int) cards.size() / parts;
    for(int i = 0 ; i < half; ++i) {
        decks[0]->add_card(this->take_front_card());
    }
    for(int i = 0; i < half; ++i) {
        decks[1]->add_card(this->take_front_card());
    }
}

void Deck::add_card(std::string suit, int value) {
    cards.push_back(std::unique_ptr<Card>(new Card(suit, value)));
}

void Deck::add_card(std::unique_ptr<Card> card) {
    if(card == nullptr) {
        return;
    }
    cards.push_back(std::move(card)); // transfer card ownership to board deck
}

std::vector<std::unique_ptr<Card>>::iterator Deck::begin() {
    return cards.begin();
}

std::vector<std::unique_ptr<Card>>::iterator Deck::end() {
    return cards.end();
}


void Deck::shuffle() { //mélanger un paquet
    int nbr = rand() % 50;
    for (int i = 0; i < nbr; i++) {
        std::shuffle(
                std::begin(cards),
                std::end(cards),
                std::default_random_engine{
                        std::random_device{}()
                }
        );
    }
}

std::unique_ptr<Card> Deck::take_front_card() {
    if(cards.empty()) {
        return nullptr;
    }
    assert(!cards.empty());
    return take_card_at((int) cards.size() -1);
}

std::unique_ptr<Card> Deck::take_card_at(int pos) {
    assert(pos >= 0 && pos < (int)cards.size());
    if(cards.at(pos)) {
        std::unique_ptr<Card> card = std::move(cards.at(pos));
        cards.erase(cards.begin() + pos);
        return std::move(card);
    }
    return nullptr;
}


Card& Deck::watch_front_card() const {
    assert(!cards.empty());
    return *cards.back();
}

Card& Deck::watch_card_at(int pos) const {
    assert(pos >=0 && pos < (int)cards.size());
    return *cards.at(pos);
}


int Deck::get_nbcards() const { //nombre de cartes restant dans le paquet
    return (int)cards.size();
}

bool Deck::isEmpty() const {
    return cards.empty();
}

void Deck::split_half(std::vector<std::unique_ptr<Deck>> &decks) {
    decks.push_back(std::unique_ptr<Deck>(new Deck()));
    decks.push_back(std::unique_ptr<Deck>(new Deck()));
    split(decks, 2);
}

void Deck::add_card(std::string label, std::string suit, int value) {
    cards.push_back(std::unique_ptr<Card>(new Card(label, suit, value)));
}

void Deck::distribute(int nb_players, int nb_cards_per_player, std::vector<std::unique_ptr<Deck>> &decks) {
    assert((int)cards.size() >= (nb_players * nb_cards_per_player));

    for (int i = 0; i < nb_players; ++i) {
        std::unique_ptr<Deck> deck = std::unique_ptr<Deck>(new Deck());
        for (int j = 0; j < nb_cards_per_player; ++j) {
            deck->add_card(this->take_front_card());
        }
        decks.push_back(std::move(deck));
    }
}

void Deck::clean_deck() {
    cards.erase (cards.begin(),cards.begin()+cards.size());

}

std::ostream & operator << (std::ostream & out, const Deck & aDeck) {
    std::cout << "[" ;
    for (int i=0;i<aDeck.get_nbcards();i++){
        std::cout << aDeck.watch_card_at(i) << "," ;
    }
    std::cout << "]" << std::endl;
    return out;
}