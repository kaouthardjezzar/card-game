//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#ifndef CARD_GAME_CARD_H
#define CARD_GAME_CARD_H

#include <iostream>
#include "../lib/logger.h"

using namespace std;
class Card {

private:
    string suit;
    int value;

public:
    Card () {  // constructeur par défaut
        value = 0;
        suit = "";
    }
    Card(string _suit, int _value): suit(_suit), value(_value) {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Creating card : " << suit << " , " << value << "\n";
    }

    Card(const Card& cd)//constructeur par copie
    {
        value=cd.value;
        suit=cd.suit;
    }

    virtual ~Card() {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Deleting card \n";
    }

    int get_value() const;
    string get_suit () const;
    void set_value (int& val) ;
    void set_suit(string& _suit) ;
    int compare(Card &cd);// comparer les valeurs de 2 cartes
    void exchange(Card& cd); //echanger deux carte


};


#endif //CARD_GAME_CARD_H
