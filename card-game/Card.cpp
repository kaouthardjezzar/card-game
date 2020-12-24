//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#include "Card.h"

int Card::get_value() const {
    return value;
}

string Card::get_suit() const {
    return suit;
}

void Card::set_value(int &val) {
    value = val;
}

void Card::set_suit(string &_suit) {
    suit = _suit;
}

int Card::compare(Card& cd)
{
if(value > cd.value) return 1;//si la premier carte est superieur à la 2 eme
else if(value < cd.value) return 2;//si la premier carte est inferieur a la 2 eme
else return 0;// les cartes sont égales
}

void Card::exchange(Card &cd) {
        Card temp=*this;
        value=cd.value;
        suit=cd.suit;
        cd=temp;
}