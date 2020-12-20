//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#ifndef CARD_GAME_DECK_H
#define CARD_GAME_DECK_H

class Card;

class Deck {
private:
    Card *cards;
public:
    Deck() {
        // Initialize cards here ?
        // Or inside a builder
    }
    void shuffle();
    Card* pick_random(int);

};


#endif //CARD_GAME_DECK_H
