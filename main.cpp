#include <iostream>
#include "examples/Bataille.h"
#include "examples/Uno.h"
#include "examples/HuitAmericain.h"
#include "examples/Scopa.h"
#include "examples/Briscola.h"


#include "lib/logger.h"


int main() {
    LOG_INIT_CERR();
    logd.set_log_level(LOG_INFO);

    logd(LOG_DEBUG) << "Game is starting ";

    std::cout << "Bienvenue dans le jeu, " << std::endl;
    std::cout << "Nous vous invitons à choisir un des jeux ci dessous, " << std::endl;

    std::vector<std::string> games = {"Bataille", "Uno", "8 Americain", "Scopa", "Briscola"};

    for(int i=1; i <= (int)games.size(); ++i) {
        std::cout << i << " " << games[i-1] << std::endl;
    }

    int choice = -1;
    int nbr = 0;
    std::string name ="";

    while(choice < 1 || choice > (int)games.size()) {
        std::cout << "Votre choix : ";
        std::cin.clear();
        std::cin >> choice;
    }

    switch (choice) {
        case 1: {
            Bataille game;
            game.lets_play();
            break;
        }
        case 2: {
            Uno game;
            game.lets_play();
            break;
        }
        case 3: {
            std::cout << "Entrez le nombre de joueurs : " << std::endl;
            std::cin.clear();
            std::cin >> nbr;
            std::vector<std::string> players;
            for(int i=0; i<nbr; i++){
                std::cout << "Entrez le nom de joueur : " << i + 1 << std::endl;
                std::cin.clear();
                std::cin >> name;
                players.push_back(name);
            }
            HuitAmericain game;
            game.lets_play(players);
            break;
        }
        case 4: {
            Scopa game;
            game.lets_play();
            break;
        }
        case 5: {
            std::cout << "Entrez le nombre de joueurs : " << std::endl;
            std::cin.clear();
            std::cin >> nbr;
            std::vector<std::string> players;
            for(int i=0; i<nbr; i++){
                std::cout << "Entrez le nom de joueur : " << i + 1 << std::endl;
                std::cin.clear();
                std::cin >> name;
                players.push_back(name);
            }
            Briscola game;
            game.lets_play(players);
            break;
        }
        default:
            std::cout << "Aucun jeu n'a été lancé" << std::endl;
            break;
    }

    std::cout << "\n Au revoir et merci beaucoup " << std::endl;
    return 0;
}
