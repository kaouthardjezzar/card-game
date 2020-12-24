//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#ifndef CARD_GAME_DECK_H
#define CARD_GAME_DECK_H

#include <vector>
#include <memory>
#include "Card.h"

using namespace std;

class Deck {
private:
    vector<unique_ptr<Card>> cards;
public:
   Deck() {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Creating Deck \n";
    }

    virtual ~Deck() {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Deleting Deck containing" << " , Cards : " << cards.size() << "\n";
    }

    void sort(); // pour trier les cartes par ordres
    void add_card(std::string suit, int value);
    void shuffle();
    unique_ptr<Card> pick_random();
    unique_ptr<Card> pick_card(int pos);
    vector<unique_ptr<Deck>> split(int parts);
    Card& tirer();
};


#endif //CARD_GAME_DECK_H
