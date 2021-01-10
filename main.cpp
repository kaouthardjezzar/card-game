#include <iostream>
#include "examples/Bataille.h"
#include "examples/Uno.h"
#include "examples/HuitAmericain.h"
#include "examples/Scopa.h"
#include "examples/Briscola.h"


#include "lib/logger.h"

using namespace std;

int main() {
    LOG_INIT_CERR();
    logd.set_log_level(LOG_INFO);

    logd(LOG_DEBUG) << "Game is starting ";

    cout << "Bienvenue dans le jeu, " << endl;
    cout << "Nous vous invitons à choisir un des jeux ci dessous, " << endl;

    vector<string> games = {"Bataille", "Uno", "8 Americain", "Scopa", "Briscola"};

    for(int i=1; i <= (int)games.size(); ++i) {
        cout << i << " " << games[i-1] << endl;
    }

    int choice = -1;

    while(choice < 1 || choice > (int)games.size()) {
        cout << "Votre choix : ";
        cin.clear();
        cin >> choice;
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
            HuitAmericain game;
            game.lets_play();
            break;
        }
        case 4: {
            Scopa game;
            game.lets_play();
            break;
        }
        case 5: {
            Briscola game;
            game.lets_play();
            break;
        }
        default:
            cout << "Aucun jeu n'a été lancé" << endl;
            break;
    }

    cout << "\n Au revoir et merci beaucoup " << endl;
    return 0;
}
