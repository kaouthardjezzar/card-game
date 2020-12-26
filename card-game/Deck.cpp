//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#include "Deck.h"
#include <algorithm>
#include <random>

void Deck::add_card(std::string suit, int value) {
    cards.push_back(std::unique_ptr<Card>(new Card(suit, value)));
}

void Deck::sort() { //trier un paquet
    for(int i=0;i<cards.size();i++)
    {
        for(int j=i+1;j<cards.size()+1;j++)
        {
            if(cards[i]->compare(reinterpret_cast<Card &>(cards[j]))==1)
            {
                cards[i]->exchange(reinterpret_cast<Card &>(cards[j]));
            }
        }
    }
}

void Deck::shuffle(){ //mélanger un paquet
    std::shuffle(
            std::begin(cards),
            std::end(cards),
            std::default_random_engine{}
            );
}

unique_ptr<Card> Deck::pick_random() { // prendre une carte du paquet au hasard
    int indice = rand()%(cards.size());
    return move(cards[indice]);
}

unique_ptr<Card> Deck::pick_card(int pos) { // prendre une carte d'une position précise
    return move(cards[pos]);
}

vector<unique_ptr<Deck>> Deck::split(int parts) // déviser le paquet en (parts) paquets
{
    vector<unique_ptr<Deck>> decks;
    LOG_INIT_COUT();
    if (cards.size() % parts != 0) logd(LOG_DEBUG) << "Erreur, on peut pas déviser toutes les cartes !" << "\n";
    for (int i= 0; i< parts; i++) {
        decks.push_back(unique_ptr<Deck>(new Deck()));
    }
    int a = 0;
    for(int j=0; j<(cards.size()/parts);j++)
    {
        for (int k= 0; k< parts; k++) {
            decks[k]->add_card(cards[a]->get_suit(),cards[a]->get_value());
            a++;
        }
    }
    return decks;
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