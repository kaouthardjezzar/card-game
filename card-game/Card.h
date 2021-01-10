//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#ifndef CARD_GAME_CARD_H
#define CARD_GAME_CARD_H

#include <iostream>
#include "../lib/logger.h"

class Card {

private:
    std::string suit;
    std::string label;
    int value;

public:
    Card(std::string& _suit, int _value): suit(_suit), value(_value) {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Creating card : " << suit << " , " << value << "\n";
    }
    Card(std::string& _label, std::string& _suit, int _value): suit(_suit), label(_label), value(_value) {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Creating card : " << label << " , " << suit << " , " << value << "\n";
    }
    Card(const Card& cd)
    {
        value=cd.value;
        suit=cd.suit;
    }
    Card(): value(0) {

    }

    virtual ~Card() {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Deleting card \n";
    }

    /*
     * Sont de la même couleur
     */
    bool isSameCol (const Card&c);

    bool isSameCol(std::unique_ptr<Card> &c);

    int get_value() const;

    std::string get_suit() const;

    std::string get_label() const;

    void set_value (int& val);

    void set_suit(std::string& _suit);

    void set_label(std::string& _label);

    /*
     * Surcharge des opérateurs
     */
    virtual bool operator>(const Card& c) const;
    virtual bool operator<(const Card& c) const;
    virtual bool operator==(const Card& c) const;
    friend std::ostream & operator << (std::ostream & out, const Card & aCard);
};


#endif //CARD_GAME_CARD_H
