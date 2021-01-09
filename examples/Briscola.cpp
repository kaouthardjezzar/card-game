//
// Created by Kaou Thaar on 09/01/2021.
//

#include "Briscola.h"

void Briscola::initialization() {
    std::cout << "Launching Briscola " << std::endl;

    // Configuration des cartes ; on utilise pas 8, 9 et 10 pour avoir 40 cartes
    std::vector<std::string> suits{"spade", "club", "diamond", "heart"};
    std::vector<int> range{1,2,3,4,5,6,7,11,12,13};
    DeckBuilder deck_builder;
    std::unique_ptr<Deck> deck = deck_builder.create()
            .with_suits(suits)
            .with_range(range)
            .build();

    assert(deck->get_nbcards() == 40);

    board.set_deck(std::move(deck));

    // Shuffle deck
    board.shuffle_deck();

    // Players
    std::vector<string> players = {"John", "Jane"};
    board.create_players(players);

    // Split cards to players
    // chaque joueurs a 3 carte
    std::vector<std::unique_ptr<Deck>> decks;
    board.get_deck().distribute(board.get_players().size(),3,decks);
    for (int i=0; i < board.get_players().size(); i++){
        board.get_players()[i]->set_deck(decks[i]);
    }
}


void Briscola::first_turn(){
    board.get_temp_deck().add_card(board.get_deck().take_front_card());
    board.set_round(1);
}


void Briscola::next_turn() {

}

bool Briscola::is_the_end() {
    return false;
}

void Briscola::end_of_game() {

}
