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
    for(auto &player: board.get_players()) {
        board.get_temp_deck().add_card(player->get_deck()->take_front_card());
        player->get_deck()->remove_front_card();
    }

    // Player 1 wins
    board.get_players()[0]->set_score(
            board.get_players()[0]->get_score() + 1
            );

    // Add temp_deck cards to player 1 cards
    for(auto &card: board.get_temp_deck()) {
        board.get_players()[0]->get_deck()->add_card(card);
    }

}


void Bataille::next_turn() {
    // i guess we dont need this method ....
}


bool Bataille::is_the_end() {
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
        cout << Player->get_name() << "a eu le score : " << Player->get_score() << endl;
    }
    if (scores[0] > scores[1]) cout << board.get_players()[0]->get_name() << " est le gagnant" << endl;
    else if (scores[0] < scores[1]) cout << board.get_players()[1]->get_name() << " est le gagnant" << endl;
    else cout << "les deux joueurs ont eu le meme score" << endl;
}
