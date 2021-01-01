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

    void split(std::vector<std::unique_ptr<Deck>>& decks, int parts) {
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

    std::vector<std::unique_ptr<Card>>::iterator begin() {
        return cards.begin();
    }

    std::vector<std::unique_ptr<Card>>::iterator end() {
        return cards.end();
    }

    void sort();
    void add_card(std::string suit, int value);
    void add_card(std::string label, std::string suit, int value);
    void add_card(std::unique_ptr<Card>& card) {
        cards.push_back(std::move(card)); // transfer card ownership to board deck
    }
    void shuffle();
    unique_ptr<Card>& take_front_card() {
       return cards.back();
    }

    Card& watch_front_card() const {
        return *cards.back();
    }

    Card& watch_card_at(int pos) const {
        assert(pos >=0 && pos < cards.size());
        return *cards.at(pos);
    }

    void remove_front_card() {
        cards.pop_back();
    }

    void pop_front() {
        assert(!cards.empty());
        cards.erase(cards.begin());
    }

    void split_half(std::vector<std::unique_ptr<Deck>>& decks);

    unique_ptr<Card> pick_random();
    unique_ptr<Card>& pick_card(int pos);

    Card& draw();
    int get_nbcards();
    bool isEmpty();

    void distribute(int nb_players, int nb_cards_per_player, std::vector<std::unique_ptr<Deck>> &decks);
};


#endif //CARD_GAME_DECK_H
