//
// Created by Ny Andrianina Mamy on 29/12/2020.
//

#ifndef CARD_GAME_UNO_H
#define CARD_GAME_UNO_H

#include "GameTemplate.h"
#include "../card-game/Board.h"
#include <iostream>

#define SKIPLINE std::cout<<std::endl;

class Uno  {
private:
    Board board;

    int get_nb_valid_move(const Card& card, Player& player);

protected:
    void initialization() ;

    void next_turn() ;

    void first_turn() ;

    std::unique_ptr<Card> choose_card(Player&, Card&);

    // Utils
    template<typename T>
    T ask_player(const std::string& title)
    {
        T x = 0;
        std::cout << title;
        while (!( std::cin >> x))
        {
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Veuillez entrer un nombre/mot correct: " << endl;
            std::cout << title;
        }
        std::cin.clear();
        std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return (x);
    }

    void display_game_status();

    bool is_the_end();

public:
    Uno() = default;
    virtual ~Uno() = default;

    void lets_play() {
        initialization();
        first_turn();
        int i = 0;
        while(i++ < 4) {
            next_turn();
        }
    }

};


#endif //CARD_GAME_UNO_H
