//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#include <iostream>
#include "Bataille.h"

void Bataille::initialization() {
    std::cout << "Launching Bataille " << std::endl;

    // Configuration des cartes
    std::vector<std::string> suits{"spade", "club", "diamond", "heart"};
    std::vector<int> range{1,2,3,4,5,6,7,8,9,10,11,12,13};
    DeckBuilder deck_builder;
    std::unique_ptr<Deck> deck = deck_builder.create()
            .with_suits(suits)
            .with_range(range)
            .build();

    board.set_deck(std::move(deck));

    // Shuffle deck
    board.shuffle_deck();

    // Players
    std::vector<string> players = {"John", "Jane"};
    board.create_players(players);

    // Split cards to players
    std::vector<std::unique_ptr<Deck>> decks;
    board.get_deck().split_half(decks);
    board.affect_decks_toplayers(decks);
}

void Bataille::next_turn() {
    // Check round winner
    std::vector<bool> winner(2);
    who_wins_this_turn(winner);

    // As the function said
    display_game_status(winner);

    // Stuff that needs to be done when someone wins
    compute_winner(winner);

    board.next_round();
}


void Bataille::who_wins_this_turn(std::vector<bool>& winner) {
    auto &player_one = board.get_players()[0];
    auto &player_two = board.get_players()[1];

    const Card card_one = player_one->get_deck()->watch_front_card();
    const Card card_two = player_two->get_deck()->watch_front_card();

    winner[0] = card_one > card_two;
    winner[1] = card_one < card_two;
}


bool Bataille::is_the_end() {
    return std::any_of(
            board.get_players().begin(),
            board.get_players().end(),
            [](const std::unique_ptr<Player>& player) {
                return player->get_deck()->isEmpty();
            });
}

void Bataille::end_of_game() {
    std::cout << "Fin du jeu " << std::endl;

    std::vector<int> scores;
    for (const auto &player : board.get_players()) {
        scores.push_back(player->get_score());
        std::cout << player->get_name() << " a eu le score : " << player->get_score() << std::endl;
    }
    if (scores[0] > scores[1]) {
        std::cout << board.get_players()[0]->get_name() << " a gagné" << std::endl;
    }
    else if (scores[0] < scores[1]) {
        std::cout << board.get_players()[1]->get_name() << " a gagné" << std::endl;
    }
    else {
        std::cout << "les deux joueurs ont eu le meme score" << std::endl;
    }
}

void Bataille::compute_winner(std::vector<bool> winner) {
    // Add cards to board's temporary deck
    for(auto &player: board.get_players()) {
        board.get_temp_deck().add_card(player->get_deck()->take_front_card());

    }

    // If it's a tie
    if(std::all_of(winner.begin(), winner.end(), [](bool win) { return win; })) {
        return; // Don't do anything
    }

    // Player one wins
    if (winner[0]) {
        this->a_player_wins(*board.get_players()[0]);
    }

    // Player two wins
    else if (winner[1]){
        this->a_player_wins(*board.get_players()[1]);
    }
}

void Bataille::a_player_wins(Player &player){
    // Increase score
    player.set_score(
            board.get_players()[0]
                    ->get_score() + 1
            );

    // Add temp_deck cards to player cards
    for(const auto &card: board.get_temp_deck()) {

        board.get_players()[0]
            ->get_deck()
            ->add_card(
                board.get_temp_deck().take_front_card()
                );
    }
}

void Bataille::display_game_status(std::vector<bool> winner) {
    std::cout << "Tour no : " << board.get_round() << std::endl;

    std::cout << "Cartes jouées : " << std::endl;
    for(const auto &player: board.get_players()) {
        std::cout << player->get_name() << " : " <<  player->get_deck()->watch_front_card() << std::endl;
    }

    assert(winner.size() == board.get_players().size());

    // If it's a tie
    if(std::all_of(winner.begin(), winner.end(), [](bool win) { return win; })) {
        std::cout << "Égalité, tour suivant " << endl;
    }

    // Display who wins
    for(int i=0 ; i < winner.size(); ++i){
        if(winner[i]) {
            std::cout << board.get_players()[i]->get_name() << " a gagné ce tour " << std::endl;
        }
    }

    // Saut de ligne
    std::cout << "\n" << std::endl;
}
