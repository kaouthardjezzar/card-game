//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#include "GameTemplate.h"

void GameTemplate::lets_play() {
        // Get called by main function
        // How to arrange function call
        initialization();
        while(!is_the_end()) {
            next_turn();
        }
        end_of_game();
}

template<typename T>
T GameTemplate::ask_player(const std::string& title)
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
