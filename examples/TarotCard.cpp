//
// Created by Ny Andrianina Mamy on 09/01/2021.
//

#include "TarotCard.h"

bool TarotCard::operator>(const Card &c) const {
    if(label == EXCUSE) {
        return true;
    }
    if(c.get_label() == EXCUSE) {
        return false;
    }
    if(label == ATOUT && c.get_label() != ATOUT) {
        return true;
    }
    if(label != ATOUT && c.get_label() == ATOUT) {
        return false;
    }
    return value > c.get_value();
}

bool TarotCard::operator==(const Card& c) const {
    if((label != ATOUT && c.get_label() != ATOUT)
    || (label == ATOUT && c.get_label() == ATOUT)) {
        return value == c.get_value();
    }

    return false;
}

bool TarotCard::operator<(const Card &c) const {
    return !(*this > c || *this == c);
}

ostream & operator << (ostream & out, Card & aCard) {
    out << aCard.label << " ";
    out << aCard.suit << " ";
    out << aCard.value << " ";
    return out;
}