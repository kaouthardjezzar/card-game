//
// Created by Ny Andrianina Mamy on 09/01/2021.
//

#ifndef CARD_GAME_SCOPA_H
#define CARD_GAME_SCOPA_H

#include "../card-game/Board.h"
#include <iostream>

#define SKIPLINE std::cout<<std::endl;

class Scopa {
private:
    Board board;

    void initialization() ;

    void next_turn() ;

    void first_turn() ;

    bool is_the_end();

    void end_of_game();

    void display_game_status();

    int make_a_choice();

    void compute_choice(int choice);

    void display_valid_move(Player& current_player);

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
public:
    Scopa() = default;
    virtual ~Scopa() = default;

    void lets_play() {
        initialization();
        first_turn();
        while(!is_the_end()) {
            next_turn();
        }
        end_of_game();
    }


};

bool is_correct_move(Deck& deck, const Card& player_move);
int is_same_value(Deck& deck, const Card& player_move);
std::vector<int> is_a_sum(Deck& deck, const Card& player_move);


#endif //CARD_GAME_SCOPA_H
