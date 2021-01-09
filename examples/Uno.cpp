//
// Created by Ny Andrianina Mamy on 29/12/2020.
//

#include <iostream>
#include "Uno.h"


void Uno::initialization() {
    std::cout << "Launching Uno " << std::endl;

    // Configuring cards
    std::vector<std::string> suits = {BLUE, RED, YELLOW, GREEN};
    std::vector<int> range{0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9};
    DeckBuilder deck_builder;

    // Total 108
    // 19 * 4 couleurs numérotées de 0 à 9, tous en double sauf le 0 = 76
    std::unique_ptr<Deck> deck = deck_builder.create()
            .with_suits(suits)
            .with_range(range)
            .build();

    // 8 * 3 * 4 couleurs tous en double
    for(std::string& suit: suits) {
        // 8 cartes « +2 », (2 pour chaque couleur)
        deck->add_card(PLUS_TWO, suit, 20);
        deck->add_card(PLUS_TWO, suit, 20);

        // 8 cartes « Inversement de sens », (2 pour chaque couleur)
        deck->add_card(REVERSE, suit, 20);
        deck->add_card(REVERSE, suit, 20);

        // 8 cartes « Passe ton tour », (2 pour chaque couleur)
        deck->add_card(SKIP, suit, 20);
        deck->add_card(SKIP, suit, 20);

        // 4 cartes « Joker »
        deck->add_card(JOKER, suit, 50);

        // 4 cartes « +4 »
        deck->add_card(PLUS_FOUR, suit, 50);
    }

    assert(deck->get_nbcards() == 108);

    deck->shuffle();

    board.set_deck(std::move(deck));

    // Creating players = default 3 Players
    std::vector<std::string> players = {"John", "Jane", "Doe"};
    board.create_players(players);

    // Affects decks to each players
    std::vector<std::unique_ptr<Deck>> decks;
    board.get_deck().distribute(players.size(), 7, decks);
    board.affect_decks_toplayers(decks);

}

bool Uno::is_special_card(const Card& card) {
    std::string label = card.get_label();

    return label == PLUS_TWO ||
            label == PLUS_FOUR ||
            label == REVERSE ||
            label == SKIP ||
            label == JOKER;
}

void Uno::compute_special_card(const Card& card, Board& board) {
    std::string label = card.get_label();
    Player& next_player = board.get_next_player();
    Player& current_player = board.get_current_player();
    std::cout << "[INFO] " ;
    if(label == PLUS_TWO) {
        std::cout << next_player << " doit piocher deux(2) cartes " << std::endl;
        for(int i =0; i < 2; i++){
            next_player.get_deck()->add_card(
                    board.get_deck().take_front_card()
                    );
        }
        std::cout << "Vos cartes ont été piochées automatiquement " << std::endl;
        std::cout << next_player << " passe son tour" << std::endl;
        board.next_round();
    } else if (label == PLUS_FOUR ) {
        std::cout << next_player << " doit piocher quatres(4) cartes " << std::endl;
        for(int i =0; i < 4; i++){
            next_player.get_deck()->add_card(
                    board.get_deck().take_front_card()
            );
        }
        std::cout << "Vos cartes ont été piochées automatiquement " << std::endl;
        std::cout << next_player << " passe son tour" << std::endl;
        board.next_round();
    } else if (label == REVERSE) {
        std::cout << "Le sens s'inverse" << std::endl;
        board.reverse_direction();
    } else if (label == SKIP) {
        std::cout << next_player << " passe son tour " << std::endl;
        board.next_round();
    } else if (label == JOKER) {
        std::cout << current_player << " choisi une couleur " << std::endl;
    }
    current_player.increase_score_by(card.get_value());
    board.next_round();
}

void Uno::compute_normal_card(const Card& card, Board& board){
    board.get_current_player().increase_score_by(card.get_value());
}

bool is_correct_move(const Card& board_card, const Card& player_move) {
    // Il doit recouvrir la carte de la pioche par une carte d’une même couleur,
    // du même chiffre ou du même symbole.

    if(board_card.get_suit() == player_move.get_suit()
       || board_card.get_label() == player_move.get_label()
       || board_card.get_value() == player_move.get_value()) {
        return true;
    }

    // Si le joueur ne peut pas jouer,
    // il a la possibilité de poser une carte « joker » ou « +4 ».

    if(player_move.get_label() == JOKER || board_card.get_label() == PLUS_FOUR ) {
        return true;
    }

    return false;
}

void Uno::display_valid_move(Player& current_player, const Card& card_on_board) {
    int i = 1;
    bool no_correct_move = true;
    std::cout << "Vous pouvez choisir :" << std::endl;
    for(auto &card: *current_player.get_deck()) {
        if(is_correct_move(card_on_board, *card)) {
            no_correct_move = false;
            std::cout << i << ". " << *card << std::endl;
        }
        i++; // To preserve card position
    }
    // Dans le cas ou le joueur ne possède aucune de ces cartes,
    // il doit en piocher une.
    if(no_correct_move) {
        std::cout << DRAW << ". Vous devez piocher " << std::endl;
    }

    // Si le joueur n'a pas crié Uno
    if(current_player.get_deck()->get_nbcards() == 1) {
        std::cout << NO_UNO << ". Pas de Uno " << std::endl;
    }
}


void Uno::next_turn() {
    Player& current_player = board.get_current_player();
    Card &card_on_board = board.get_temp_deck().watch_front_card();

    display_game_status();

    int choice = make_a_choice();

    compute_choice(choice);
}

void Uno::first_turn() {
    // Piocher une carte et mettre sur la table
    std::cout << "Premier tour " << std::endl;

    Player& player = board.get_current_player();
    std::cout << player << " a pioché une carte" << std::endl;
    board.get_temp_deck().add_card(
            board.get_deck().take_front_card()
    );
    Card &card_on_board = board.get_temp_deck().watch_front_card();

    display_game_status();

    if(is_special_card(card_on_board)) {
        compute_special_card(card_on_board,  board);
    } else {
        int choice = make_a_choice();
        compute_choice(choice);
    }
}

void Uno::display_game_status() {
    Player& current_player = board.get_current_player();
    Card &card_on_board = board.get_temp_deck().watch_front_card();

    SKIPLINE
    std::cout << "[SCORE] Scores actuels : " << std::endl;
    for(auto &player: board.get_players()) {
        std::cout << *player << " est à " << player->get_score() << " point(s) " << std::endl;
    }

    SKIPLINE
    std::cout << "[TABLE] Il reste : " << board.get_deck().get_nbcards() << " carte(s) dans la pioche " << std::endl;
    std::cout << "[JEU] Carte en jeu : " << card_on_board << std::endl;
    std::cout << "[TOUR] Au tour de " << current_player << std::endl;

    SKIPLINE
}

bool Uno::is_the_end() {
    return std::any_of(
            board.get_players().begin(),
            board.get_players().end(),
            [](const std::unique_ptr<Player>& player) {
                return player->get_deck()->isEmpty() || player->get_score() >= 500;
            });
}

void Uno::end_of_game() {
    compute_winner();
}

void Uno::compute_winner() {
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

int Uno::make_a_choice() {
    Player& current_player = board.get_current_player();
    Card &card_on_board = board.get_temp_deck().watch_front_card();

    display_valid_move(current_player, card_on_board);
    int choice = -1;
    choice = ask_player<int>("Votre choix : ");

    return choice;
};

void Uno::compute_choice(int choice) {
    Player &current_player = board.get_current_player();
    if (choice == DRAW) { // Player can't move and needs to draw a card
        Board::safe_draw_cards_from_deck(current_player, board.get_deck(), 1);
    } else if (choice == NO_UNO) { // Player didn't say UNO so he must draw two cards
        std::cout << current_player << " n'a pas crié Uno et doit piocher deux(2) cartes " << std::endl;
        Board::safe_draw_cards_from_deck(current_player, board.get_deck(), 2);
        std::cout << "Vos cartes ont été piochées automatiquement " << std::endl;
    } else { // Pick chosen card
        std::unique_ptr<Card> card = current_player.get_deck()->take_card_at(choice - 1);
        if (card == nullptr) { return; }

        if (is_special_card(*card)) {
            compute_special_card(*card, board);
        } else {
            compute_normal_card(*card, board);
        }
        board.get_temp_deck().add_card(std::move(card));
    }
}
