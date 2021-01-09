//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#ifndef CARD_GAME_CARD_H
#define CARD_GAME_CARD_H

#include <iostream>
#include "../lib/logger.h"

using namespace std;

class Card {

protected:
    string suit;
    string label;
    int value;

public:
    Card () {  // constructeur par défaut
        value = 0;
        suit = "";
    }
    Card(string _suit, int _value): suit(_suit), label(""), value(_value) {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Creating card : " << suit << " , " << value << "\n";
    }
    Card(string _label, string _suit, int _value): suit(_suit), label(_label), value(_value) {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Creating card : " << label << " , " << suit << " , " << value << "\n";
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
    std::string get_suit() const;
    std::string get_label() const;
    void set_value (int& val);
    void set_suit(std::string& _suit);
    void set_label(std::string& _label);

    bool isSameCol (const Card&c);
    // Operator overloading
    virtual bool operator>(const Card& c) const;
    virtual bool operator<(const Card& c) const;
    virtual bool operator==(const Card& c) const;
    friend ostream & operator << (ostream & out, Card & aCard);
};


#endif //CARD_GAME_CARD_H
