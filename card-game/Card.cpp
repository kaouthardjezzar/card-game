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

void Card::exchange(Card &cd) {
        Card temp=*this;
        value=cd.value;
        suit=cd.suit;
        cd=temp;
}

// Operator overloading

bool Card::operator>(const Card& c) const {
    return value > c.get_value();
}

bool Card::operator<(const Card& c) const {
    return value < c.get_value();
}

ostream & operator << (ostream & out, Card & aCard) {
    // afficher la valeur
    switch (aCard.value) {
        case 1:  out << "Ace";   break;
        case 11: out << "Jack";  break;
        case 12: out << "Queen"; break;
        case 13: out << "King";  break;
        default:	// output number
            out << aCard.value; break;
    }
    // afficher la famille
        if ( aCard.suit == "diamond")  out << " of Diamonds";
        if ( aCard.suit == "spade")  out << " of Spades";
        if ( aCard.suit == "heart")  out << " of Hearts";
        if ( aCard.suit == "club")  out << " of Clubs";
    return out;
}