//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#ifndef CARD_GAME_DECK_H
#define CARD_GAME_DECK_H

#include <vector>
#include <memory>
#include "Card.h"

#define VECTOR_IT __wrap_iter<vector<unique_ptr<Card, default_delete<Card>>, allocator<unique_ptr<Card, default_delete<Card>>>>::pointer>

using namespace std;

class Deck {
private:
    vector<unique_ptr<Card>> cards;
public:
   Deck(): cards{} {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Creating Deck \n";
    }

    virtual ~Deck() {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Deleting Deck containing" << " , Cards : " << cards.size() << "\n";
    }

    // Iterable Class

    typedef Card * iterator;
    typedef const Card * const_iterator;

    VECTOR_IT begin() {
        return cards.begin();
    }

    VECTOR_IT end() {
        return cards.end();
    }

    void sort();
    void add_card(std::string suit, int value);
    void add_card(std::unique_ptr<Card>& card) {
        cards.push_back(std::move(card)); // transfer card ownership to board deck
    }
    void shuffle();
    unique_ptr<Card>& take_front_card() {
       return cards.back();
    }

    void remove_front_card() {
        cards.pop_back();
    }

    void pop_front() {
        assert(!cards.empty());
        cards.erase(cards.begin());
    }

    void split(std::vector<std::unique_ptr<Deck>>& decks) {
        if(decks.size() != 2) {
            std::cerr << "Only split to two parts" << std::endl;
            return;
        }
        int parts = cards.size()/2;
        for(int i = 0 ; i < parts; ++i) {
            decks[0]->add_card(this->take_front_card());
            this->remove_front_card();
        }
        for(int i = 0; i < parts; ++i) {
            decks[1]->add_card(this->take_front_card());
            this->remove_front_card();
        }
    }

    unique_ptr<Card> pick_random();
    unique_ptr<Card>& pick_card(int pos);

    Card& draw();
    int get_nbcards();
    bool isEmpty();
};


#endif //CARD_GAME_DECK_H
