//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#include <iostream>
#include "Bataille.h"



void Bataille::initialization() {
    std::cout << "Launching Bataille " << std::endl;

    // Configuration des cartes
    std::vector<std::string> suits{"spade", "club", "diamond", "heart"};
    std::vector<int> range{0,1,2,3,4,5,6,7,8,9,10,11,12,13};
    DeckBuilder deck_builder;
    std::unique_ptr<Deck> deck = deck_builder.create()
            ->with_suits(suits)
            ->with_range(range)
            ->build();

    board.set_deck(std::move(deck));

    // Shuffle deck
    board.shuffle_deck();

    // Players
    std::unique_ptr<Player> john = std::unique_ptr<Player>(new Player("John"));
    std::unique_ptr<Player> jane = std::unique_ptr<Player>(new Player("Jane"));

    board.add_player(john);
    board.add_player(jane);
    // board.add_player(Kaou)

    board.affect_cards_toplayer();


}


void Bataille::who_wins_this_turn() {
    vector<Card> cards;
    int nb_draw = 0;
    for (auto &&Player : board.get_players()) { //chaque joueur tire une carte
        cards.push_back(Player->get_deck()->draw());
        nb_draw ++;
        cout << Player->get_name() << "a joué la carte" << cards[cards.size()] << endl;
    }
    int comp = cards[0].compare(cards[1]);
    while (comp == 0) {
        for (auto &&Player : board.get_players()) { //chaque joueur tire une carte
            cards.push_back(Player->get_deck()->draw());
            nb_draw ++;
            cout << Player->get_name() << "a joué une carte" << endl;
            cards.push_back(Player->get_deck()->draw());
            nb_draw ++;
            cout << Player->get_name() << "a joué la carte" << cards[cards.size()] << endl;
        }
        comp =cards[cards.size()-1].compare(cards[cards.size()-2]);
    }
    if (comp == 1) {
        for (int i = 0; i<nb_draw; i++)
            board.get_players()[0]->increment();
    }
    else if (comp == 2){
        for (int i = 0; i<nb_draw; i++)
            board.get_players()[1]->increment();
    }

}


void Bataille::next_turn() {
    // i guess we dont need this method ....
}


bool Bataille::is_the_end() {
    // if Mamy.deck.size() == 0 or Kaou.deck.size() == 0 return true
    for(int i = 0 ;i<board.get_players().size();i++) {
        if (board.get_players()[i]->get_deck()->isEmpty()) return true;
    }
    return false;
}

void Bataille::end_of_game() {
    vector <int> scors;
    for (auto &&Player : board.get_players()) { //chaque joueur tire une carte
        scors.push_back(Player->get_score());
        cout << Player->get_name() << "a eu le score : " << scors[scors.size()] << endl;
    }
    if (scors[0]>scors[1]) cout << board.get_players()[0]->get_name() << "est le gagnant" << endl;
    else if (scors[0]<scors[1]) cout << board.get_players()[1]->get_name() << "est le gagnant" << endl;
    else cout << "les deux joueurs ont eu le meme score" << endl;
}


bool play_bataille() {

    /*
  // Shuffle deck
  // while (!end_game)
   // Turn begins here
   // TEMP
a:   Display game status
   Wait for draw
   Draw
   Check current turn winner // Should be on game start section
       If A wins over B:
          Add A.card and B.card to TEMP
          Add TEMP to A.deck
       Else if : same for B
       Else if no winner :
          // Add cards to TEMP
          goto a:
   Display final score
  */
    return true; // When game is finished
}


//void GameTemplate::lets_play() {
//    // Get called by main function
//    // How to arrange function call
//    initialization();
//    while(!is_the_end()) {
//        next_turn();
//        who_wins_this_turn();
//    }
//}
