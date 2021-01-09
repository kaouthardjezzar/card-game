//
// Created by Ny Andrianina Mamy on 09/01/2021.
//

#include "Scopa.h"
#include "ScopaCards.h"

void Scopa::initialization() {
    std::cout << "Launching Scopa " << std::endl;

    // Configuring cards
    std::vector<std::string> suits = {COUPE, BATON, DENIER, EPEE};
    std::vector<int> range{1,2,3,4,5,6,KNIGHT,QUEEN,KING};
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

    // Add 3 cards to board temp deck
    Board::safe_draw_cards_from_deck(board.get_temp_deck(), board.get_deck(), 3);

}

void Scopa::next_turn() {

}
