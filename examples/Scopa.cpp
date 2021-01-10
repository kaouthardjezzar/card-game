//
// Created by Ny Andrianina Mamy on 09/01/2021.
//

#include "Scopa.h"
#include "ScopaCards.h"

void Scopa::initialization() {
    std::cout << "Launching Scopa " << std::endl;

    // Configuring cards
    std::vector<std::string> suits = {COUPE, BATON, DENIER, EPEE};
    std::vector<int> range{1,2,3,4,5,6,7,KNIGHT,QUEEN,KING};
    DeckBuilder deck_builder;

    // Total 40
    std::unique_ptr<Deck> deck = deck_builder.create()
            .with_suits(suits)
            .with_range(range)
            .build();

    assert(deck->get_nbcards() == 40);

    deck->shuffle();
    board.set_deck(std::move(deck));

    // Creating players = default 2 Players
    std::vector<std::string> players = {"John", "Doe"};
    board.create_players(players);

    // Affects decks to each players
    std::vector<std::unique_ptr<Deck>> decks;
    board.get_deck().distribute(players.size(), 3, decks);
    board.affect_decks_toplayers(decks);

}

void Scopa::first_turn() {
    // Add 4 cards to board temp deck
    Board::safe_draw_cards_from_deck(board.get_temp_deck(), board.get_deck(), 4);
    display_game_status();
    int choice = make_a_choice();
    if(choice != NOCHOICE) {
        compute_choice(choice - 1);
    }
}

void Scopa::next_turn() {
    // If all players have no cards
    if(std::all_of(board.get_players().begin(), board.get_players().end(), [](std::unique_ptr<Player>& player) {
        return player->get_deck()->get_nbcards() == 0;
    })){
        std::cout << "Carte vide pour tous" << std::endl;
        std::cout << "Trois (3) nouveaux cartes ont été ajoutés à vos mains " << std::endl;

        for(auto &player: board.get_players()) {
            Board::safe_draw_cards_from_deck(*player, board.get_deck(), 3);
        }
    }

    // If the board have no cards
    if(board.get_temp_deck().get_nbcards() == 0) {
        Board::safe_draw_cards_from_deck(board.get_temp_deck(), board.get_deck(), 4);
    }

    display_game_status();
    int choice = 0;
    choice = make_a_choice();
    if(choice != NOCHOICE) {
        compute_choice(choice-1);
    }
}

void Scopa::end_of_game() {
    display_game_status();
    int i = 0;
    int index_max = 0;
    int score_max = -999;
    for(auto &player: board.get_players()) {
        if(player->get_score() > score_max) {
            index_max = i;
            score_max = player->get_score();
        }
        if(player->get_deck()->isEmpty()) {
            index_max = i;
            break;
        }
        i++;
    }
    std::cout << *board.get_players()[index_max] << " a gagné la partie " << std::endl;
}

bool Scopa::is_the_end() {
    return board.get_deck().isEmpty();
}

int Scopa::make_a_choice() {
    Player& current_player = board.get_current_player();

    if(current_player.get_deck()->get_nbcards() == 0) {
        std::cout << "Vous n'avez plus de cartes, vous passez votre tour " << std::endl;
        return NOCHOICE;
    }

    display_valid_move(current_player);
    int choice = -1;
    choice = ask_player<int>("Votre choix : ");
    return choice;
}

void Scopa::display_valid_move(Player& current_player) {
    int i = 1;
    bool no_correct_move = true;
    std::cout << "Vous pouvez choisir :" << std::endl;
    for(auto &card: *current_player.get_deck()) {
        if(is_correct_move(board.get_temp_deck(), *card)) {
            no_correct_move = false;
            std::cout << i << ". " << *card << std::endl;
        }
        i++; // To preserve card position
    }

    if(no_correct_move) {
        std::cout << "Pas de carte possible pour un pli. " << std::endl;
        std::cout << "Vous devez choisir une carte au hasard " << std::endl;

        i = 1;
        for (auto &card: *current_player.get_deck()) {
            std::cout << i++ << ". " << *card << std::endl;
        }
    }
}

bool is_correct_move(Deck& deck, const Card& player_move) {
    // Une carte d'une même valeur que ceux sur la table.
    // Ou
    // [PAS IMPLÉMENTÉ]Une carte d'une même valeur que la somme de deux cartes sur la table.
    return is_same_value(deck, player_move) != NOCHOICE;
}

int is_same_value(Deck& deck, const Card& player_move) {
    for(int i = 0; i < deck.get_nbcards(); ++i){
        Card& card = deck.watch_card_at(i);
        if(card.get_value() == player_move.get_value()) {
            return i;
        }
    }
    return NOCHOICE;
}

void Scopa::display_game_status() {
    Player& current_player = board.get_current_player();
    SKIPLINE
    std::cout << "[SCORE] Scores actuels : " << std::endl;
    for(auto &player: board.get_players()) {
        std::cout << *player << " est à " << player->get_score() << " point(s) " << std::endl;
    }

    SKIPLINE
    std::cout << "[TABLE] Il reste : " << board.get_deck().get_nbcards() << " carte(s) dans la pioche " << std::endl;
    std::cout << "[TABLE] Cartes sur la table" << std::endl;
    for(auto &card: board.get_temp_deck()) {
        std::cout << *card << std::endl;
    }
    SKIPLINE
    std::cout << "[JEU] ";
    std::cout << "Au tour de " << current_player << std::endl;
}

void Scopa::compute_choice(int choice) {
    Player& current_player = board.get_current_player();
    std::unique_ptr<Card> card = current_player.get_deck()->take_card_at(choice);
    assert(card != nullptr);

    // Coup normal
    if(is_correct_move(board.get_temp_deck(), *card)) {
        int same_value_index = is_same_value(board.get_temp_deck(), *card);
        std::unique_ptr<Card> deck_card = board.get_temp_deck().take_card_at(same_value_index);
        current_player.increase_score_by(deck_card->get_value());
        deck_card.reset();
    }
    card.reset();
    board.next_round();
}
