//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#ifndef CARD_GAME_DECK_H
#define CARD_GAME_DECK_H

#include <vector>
#include <memory>
#include "Suit.h"
#include "Card.h"


class Deck {
private:
//    std::vector<Suit> suits;
    std::vector<std::shared_ptr<Card>> cards; // Or Shared ptr ?
public:
    Deck() {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Creating Deck \n";
    }
    virtual ~Deck() {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Deleting Deck containing" << " Suits : " << suits.size() << " , Cards : " << cards.size() << "\n";
    }

//    void set_suits(std::vector<Suit> _suits);
//    std::vector<Suit> get_suits();
    void add_card(Suit suit, int value);
    void shuffle();
    Card* pick_random(int);

};


#endif //CARD_GAME_DECK_H
