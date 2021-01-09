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
    // Check round winner
    std::vector<bool> winner(2);
    who_wins_this_turn(winner);

    // As the function said
    display_game_status(winner);

    // Stuff that needs to be done when someone wins
    compute_winner(winner);

    board.next_round();
}

bool Briscola::is_the_end() {
    return false;
}

void Briscola::end_of_game() {

}

void Briscola::display_game_status(std::vector<bool> winner) {

}

void Briscola::who_wins_this_turn(vector<bool> &winner) {
    auto &player_one = board.get_players()[0];
    auto &player_two = board.get_players()[1];

    const Card card_one = player_one->get_deck()->watch_front_card();
    const Card card_two = player_two->get_deck()->watch_front_card();

    winner[0] = card_one > card_two;
    winner[1] = card_one < card_two;
}

void Briscola::compute_winner(std::vector<bool> winner) {

}

Card & Briscola::chooseCard() {
    for (int i= 0; i< board.get_players()[board.get_turn()]->get_deck()->get_nbcards();i++)
    {
        if (validCard(board.get_players()[board.get_turn()]->get_deck()->watch_card_at(i))){
            board.get_temp_deck().add_card(board.get_players()[board.get_turn()]->get_deck()->take_card_at(i));
            board.next_round();
            cout << "carte jouee : " << board.get_temp_deck().watch_front_card() << endl;
        }
    }
}

bool Briscola::validCard(Card &card) {
    if (card.get_value() ==board.get_temp_deck().watch_front_card().get_value() ||
        card.isSameCol(board.get_temp_deck().watch_front_card()) ) {
        return true;
    }
    else {return false;}
}