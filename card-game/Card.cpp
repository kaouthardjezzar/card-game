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

// Operator overloading

bool Card::operator>(const Card& c) const {
    return value > c.get_value();
}

bool Card::operator<(const Card& c) const {
    return value < c.get_value();
}

ostream & operator << (ostream & out, Card & aCard) {
    if (!aCard.label.empty()) {
        out << "Label : " << aCard.label << " ";
    }

    out << " Suite : " << aCard.suit << " ";

    out << " Valeur : " ;
    switch (aCard.value) {
        case 1:
            out << "Ace";
            break;
        case 11:
            out << "Jack";
            break;
        case 12:
            out << "Queen";
            break;
        case 13:
            out << "King";
            break;
        default:    // output number
            out << aCard.value;
            break;
    }
    return out;
}

bool Card::operator==(const Card &c) const {
    return value == c.get_value();
}

std::string Card::get_label() const {
    return label;
}

void Card::set_label(string &_label) {
    label = _label;
}

bool Card::isSameCol(const Card &c) {
    // les diamonds et les coeurs sont du meme couleur : rouge
    // club and spade sont du meme couleur : noir
    if(suit == c.get_suit()) return true;
    else { if ((c.get_suit() == "heart" and suit =="diamond" ) || (c.get_suit() == "diamond" and suit =="heart")) return true;
    else {if ((c.get_suit() == "club" and suit =="spade" ) || (c.get_suit() == "spade" and suit =="club")) return true;
    else {return false;} }}
}

bool Card::isSameCol(std::unique_ptr<Card> &c) {
    if(suit == c->get_suit()) return true;
    else { if ((c->get_suit() == "heart" and suit =="diamond" ) || (c->get_suit() == "diamond" and suit =="heart")) return true;
        else {if ((c->get_suit() == "club" and suit =="spade" ) || (c->get_suit() == "spade" and suit =="club")) return true;
            else {return false;} }}
}
