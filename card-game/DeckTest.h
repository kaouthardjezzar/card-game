//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#ifndef CARD_GAME_DECKTEST_H
#define CARD_GAME_DECKTEST_H

#include <vector>
#include <memory>
#include "Card.h"
#include <cassert>


class Deck {
private:
    std::vector<std::unique_ptr<Card>> cards;

    void split(std::vector<std::unique_ptr<Deck>>& decks, int parts);

public:
   Deck(): cards{} {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Creating Deck \n";
    }

    virtual ~Deck() {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Deleting Deck containing" << " , Cards : " << (int)cards.size() << "\n";
    }

    // Iterable Class

    typedef Card * iterator;
    typedef const Card * const_iterator;

    std::vector<std::unique_ptr<Card>>::iterator begin();

    std::vector<std::unique_ptr<Card>>::iterator end();

    void add_card(std::string suit, int value);
    void add_card(std::string label, std::string suit, int value);
    void add_card(std::unique_ptr<Card> card);
    void shuffle();

    void clean_deck();

    unique_ptr<Card> take_front_card();

    unique_ptr<Card> take_card_at(int pos); // pos from 0 -> cards size


    Card& watch_front_card() const;

    Card& watch_card_at(int pos) const;

    void split_half(std::vector<std::unique_ptr<Deck>>& decks);

    int get_nbcards();
    bool isEmpty();

    void distribute(int nb_players, int nb_cards_per_player, std::vector<std::unique_ptr<Deck>> &decks);
    friend ostream & operator << (ostream & out, Deck & aDeck);
};


#endif //CARD_GAME_DECKTEST_H