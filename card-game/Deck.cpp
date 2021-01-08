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
        this->remove_front_card();
    }
    for(int i = 0; i < half; ++i) {
        decks[1]->add_card(this->take_front_card());
        this->remove_front_card();
    }
}

void Deck::add_card(std::string suit, int value) {
    cards.push_back(std::unique_ptr<Card>(new Card(suit, value)));
}

void Deck::add_card(std::unique_ptr<Card>& card) {
    cards.push_back(std::move(card)); // transfer card ownership to board deck
}

std::vector<std::unique_ptr<Card>>::iterator Deck::begin() {
    return cards.begin();
}

std::vector<std::unique_ptr<Card>>::iterator Deck::end() {
    return cards.end();
}


void Deck::shuffle(){ //mélanger un paquet
    std::shuffle(
            std::begin(cards),
            std::end(cards),
            std::default_random_engine{
                    std::random_device{}()
            }
            );
}

unique_ptr<Card>& Deck::take_front_card() {
    return cards.back();
}

Card& Deck::watch_front_card() const {
    return *cards.back();
}

Card& Deck::watch_card_at(int pos) const {
    assert(pos >=0 && pos < cards.size());
    return *cards.at(pos);
}

void Deck::remove_front_card() {
    cards.pop_back();
}

void Deck::pop_front() {
    assert(!cards.empty());
    cards.erase(cards.begin());
}

unique_ptr<Card> Deck::pick_random() { // prendre une carte du paquet au hasard
    int indice = rand()%(cards.size());
    return move(cards[indice]);
}

unique_ptr<Card>& Deck::pick_card(int pos) { // prendre une carte d'une position précise
    return cards.at(pos);
}

Card& Deck::draw() //pour tirer une carte de la main
{
    Card *cd = new Card(*this->pick_card(cards.size()-1));//en memoirise la carte a tirer
    delete(&cards[cards.size()-1]);
    cards.erase(cards.begin()+cards.size()-1);
    return *cd;//retourner la carte choisie
}

int Deck::get_nbcards() { //nombre de cartes restant dans le paquet
    return cards.size();
}

bool Deck::isEmpty() {
    return this->get_nbcards()==0;
}

void Deck::split_half(vector<std::unique_ptr<Deck>> &decks) {
    decks.push_back(std::unique_ptr<Deck>(new Deck()));
    decks.push_back(std::unique_ptr<Deck>(new Deck()));
    split(decks, 2);
}

void Deck::add_card(std::string label, std::string suit, int value) {
    cards.push_back(std::unique_ptr<Card>(new Card(label, suit, value)));
}

void Deck::distribute(int nb_players, int nb_cards_per_player, vector<std::unique_ptr<Deck>> &decks) {
    assert(cards.size() >= (nb_players * nb_cards_per_player));

    for (int i = 0; i < nb_players; ++i) {
        std::unique_ptr<Deck> deck = std::unique_ptr<Deck>(new Deck());
        for (int j = 0; j < nb_cards_per_player; ++j) {
            deck->add_card(this->take_front_card());
            this->remove_front_card();
        }
        decks.push_back(std::move(deck));
    }
}
