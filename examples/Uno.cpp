//
// Created by Ny Andrianina Mamy on 29/12/2020.
//

#include <iostream>
#include "Uno.h"
#include "UnoCards.h"

void Uno::initialization() {
    std::cout << "Launching Uno " << std::endl;

    // Configuring cards
    std::vector<std::string> suits = {BLUE, RED, YELLOW, GREEN};
    std::vector<int> range{0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9};
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
        deck->add_card(PLUS_TWO, suit, 2);
        deck->add_card(PLUS_TWO, suit, 2);

        // 8 cartes « Inversement de sens », (2 pour chaque couleur)
        deck->add_card(REVERSE, suit, 2);
        deck->add_card(REVERSE, suit, 2);

        // 8 cartes « Passe ton tour », (2 pour chaque couleur)
        deck->add_card(SKIP, suit, 2);
        deck->add_card(SKIP, suit, 2);

        // 4 cartes « Joker »
        deck->add_card(JOKER, suit, 0);

        // 4 cartes « +4 »
        deck->add_card(PLUS_FOUR, suit, 4);
    }

    assert(deck->get_nbcards() == 108);

    board.set_deck(std::move(deck));

    // Creating players = default 3 Players
    std::vector<std::string> players = {"John", "Jane", "Doe"};
    board.create_players(players);

    // Affects decks to each players
    std::vector<std::unique_ptr<Deck>> decks;
    board.get_deck().distribute(players.size(), 7, decks);
    board.affect_decks_toplayers(decks);

}

void Uno::next_turn() {
    auto& players = board.get_players();
    int current_player_id = (int) board.get_round() % players.size();
    auto& current_player = players[current_player_id];

    board.set_turn(current_player_id);

    auto& draw = board.get_deck().watch_front_card();
    std::cout << "Carte de la table pioché : " << draw << std::endl;

    std::cout << "Tour no: " << board.get_round() << std::endl;

    // Pour commencer, le joueur ayant distribué retourne la première carte de la pioche et
    // le joueur situé à gauche commence la partie.

    std::cout << "À " << *current_player << " de jouer !. " << std::endl;
    std::cout << "Vos cartes :" << std::endl;
    int i = 1;
    for(auto& card: *current_player->get_deck()) {
        std::cout << i++ << ". " << *card << std::endl;
    }

    int choice = ask_player<int>("Votre choix :") - 1;
    std::vector<bool> winner(players.size());
    who_wins_this_turn(winner, choice);
}

void Uno::who_wins_this_turn(std::vector<bool>& winner,int choice) {
    auto &player = board.get_players()[board.get_turn()];

    auto& card = player->get_deck()->watch_card_at(choice);

    std::cout << "Vous avez choisi : " << card << std::endl;

    // Il doit recouvrir la carte de la pioche par une carte d’une même couleur,
    // du même chiffre ou du même symbole.

    // Si le joueur ne peut pas jouer,
    // il a la possibilité de poser une carte « joker » ou « +4 ».

    // Dans le cas ou le joueur ne possède aucune de ces cartes,
    // il doit en piocher une.
    // Si cette carte peut être jouée,
    // il peut directement la poser,
    // sinon il devra la conserver dans son jeu.

}


bool Uno::is_the_end() {
    // Lorsque qu’un joueur n’a plus qu’une carte en sa possession,
    // il doit crier « Uno » pour avertir tous les autres joueurs.
    // S’il oublie de le faire et qu’un joueur s’en aperçoit,
    // il devra piocher 2 cartes en pénalité.

    board.increase_round();
    return false;
}

void Uno::end_of_game() {

}

void Uno::compute_winner(std::vector<bool>& winner) {

}

void Uno::a_player_wins(Player &player){

}

void Uno::display_game_status(std::vector<bool> winner) {

}


