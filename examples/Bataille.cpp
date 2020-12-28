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

    // Build Deck
    std::vector<std::unique_ptr<Deck>> decks;
    std::unique_ptr<Deck> part1 = std::unique_ptr<Deck>(new Deck());
    std::unique_ptr<Deck> part2 = std::unique_ptr<Deck>(new Deck());

    decks.push_back(std::move(part1));
    decks.push_back(std::move(part2));

    // Split cards to players
    board.get_deck().split(decks);
    for(int i=0; i < board.get_players().size(); ++i) {
        board.get_players()[i]->set_deck(decks[i]);
    }
}

void Bataille::who_wins_this_turn() {
    // Draw cards and move to temp deck
    auto &player_one = board.get_players()[0];
    auto &player_two = board.get_players()[1];

    std::unique_ptr<Card> card_one = std::move(player_one->get_deck()->take_front_card());
    std::unique_ptr<Card> card_two = std::move(player_two->get_deck()->take_front_card());

    player_one->get_deck()->remove_front_card();
    player_two->get_deck()->remove_front_card();

    // Display game status
    std::cout << "Tour no : " << board.get_round() << std::endl;

    std::cout << "Cartes jouées : " << std::endl;
    std::cout << player_one->get_name() << " : " <<  *card_one << std::endl;
    std::cout << player_two->get_name() << " : " <<  *card_two << std::endl;

    // Check round winner
    std::vector<bool> winner(2);
    bool tie = *card_one == *card_two;
    winner[0] = *card_one > *card_two;
    winner[1] = *card_one < *card_two;

    board.get_temp_deck().add_card(card_one);
    board.get_temp_deck().add_card(card_two);

    if(tie) {
        return; // Don't do anything
    }

    // Player one wins
    if (winner[0]) {
        this->compute_winner(*board.get_players()[0]);
    }
    // Player two wins
    else if (winner[1]){
        this->compute_winner(*board.get_players()[1]);
    }
}


void Bataille::next_turn() {
    // i guess we dont need this method ....
}


bool Bataille::is_the_end() {
    board.increase_round();
    for(const auto &player : board.get_players()) {
        if (player->get_deck()->isEmpty()) {
            return true;
        }
    }
    return false;
}

void Bataille::end_of_game() {
    vector <int> scores;
    for (auto &&Player : board.get_players()) { //chaque joueur tire une carte
        scores.push_back(Player->get_score());
        cout << Player->get_name() << " a eu le score : " << Player->get_score() << endl;
    }
    if (scores[0] > scores[1]) cout << board.get_players()[0]->get_name() << " est le gagnant" << endl;
    else if (scores[0] < scores[1]) cout << board.get_players()[1]->get_name() << " est le gagnant" << endl;
    else cout << "les deux joueurs ont eu le meme score" << endl;
}

void Bataille::compute_winner(Player &player){
    // Increase score
    player.set_score(
            board.get_players()[0]->get_score() + 1
    );

    // Add temp_deck cards to player cards
    for(const auto &card: board.get_temp_deck()) {
        board.get_players()[0]->get_deck()->add_card(
                board.get_temp_deck().take_front_card()
        );
        board.get_temp_deck().remove_front_card();
    }
}
