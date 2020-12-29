//
// Created by Ny Andrianina Mamy on 29/12/2020.
//

#include <iostream>
#include "Uno.h"

void Uno::initialization() {
    std::cout << "Launching Uno " << std::endl;

    // Configuring cards
    std::vector<std::string> suits = {"bleu", "rouge", "jaune", "verte"};
    std::vector<int> range{1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9};
    DeckBuilder deck_builder;

    // Total 108
    // 19 * 4 couleurs numérotées de 0 à 9, tous en double sauf le 0 = 76
    std::unique_ptr<Deck> deck = deck_builder.create()
            ->with_suits(suits)
            ->with_range(range)
            ->build();

    // 8 * 3 * 4 couleurs tous en double
    for(std::string& suit: suits) {
        // 8 cartes « +2 », (2 pour chaque couleur)
        deck->add_card("+2", suit, 2);
        deck->add_card("+2", suit, 2);

        // 8 cartes « Inversement de sens », (2 pour chaque couleur)
        deck->add_card("Inversement de sens", suit, 2);
        deck->add_card("Inversement de sens", suit, 2);

        // 8 cartes « Passe ton tour », (2 pour chaque couleur)
        deck->add_card("Passe ton tour", suit, 2);
        deck->add_card("Passe ton tour", suit, 2);

        // 4 cartes « Joker »
        deck->add_card("Joker", suit, 0);

        // 4 cartes « +4 »
        deck->add_card("+4", suit, 4);
    }

    assert(deck->get_nbcards() == 108);
}

void Uno::next_turn() {

}

void Uno::who_wins_this_turn(std::vector<bool>& winner) {

}


bool Uno::is_the_end() {
    return true;
}

void Uno::end_of_game() {

}

void Uno::compute_winner(std::vector<bool> winner) {

}

void Uno::a_player_wins(Player &player){

}

void Uno::display_game_status(std::vector<bool> winner) {

}


