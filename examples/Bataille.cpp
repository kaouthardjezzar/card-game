//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#include <iostream>
#include "Bataille.h"
bool play_bataille() {

    /*
    // Shuffle deck
    // while (!end_game)
     // Turn begins here
     // TEMP
a:   Display game status
     Wait for draw
     Draw
     Check current turn winner // Should be on game start section
         If A wins over B:
            Add A.card and B.card to TEMP
            Add TEMP to A.deck
         Else if : same for B
         Else if no winner :
            // Add cards to TEMP
            goto a:

     Display final score

    */


    return true; // When game is finished
}

void Bataille::who_wins_this_turn() {
    // Last_card_of_Mamy = Mamy.deck.pick_front_card()
    // Last_card_of_Kaou = Kaou.deck.pick_front_card()
    // Apply Bataille Rules
    // Display current turn winner
    // Update scores
}

void Bataille::next_turn() {
    // Wait for Mamy to draw a card
    // Mamy.deck.add(Board.deck.pick_front_card()) // Transférer le pointeur d'une carte de Board vers Mamy
    // Wait for Kaou to draw a card
    // Kaou.deck.add(Board.deck.pick_front_card())

}

void Bataille::initialization() {
    std::cout << "Launching Bataille " << std::endl;

    // Configuration des cartes
    std::vector<Suit> suits{Suit::spade};
    std::vector<int> range{1,2,3,4,5};
    DeckBuilder deck_builder;
    std::unique_ptr<Deck> deck = deck_builder.create()
                                    ->with_suits(suits)
                                    ->with_range(range)
                                    ->build();
    board.set_deck(std::move(deck));

    // deck.shuffle()
    // board.add_player(Mamy)
    // board.add_player(Kaou)
}

bool Bataille::is_the_end() {
    // if Mamy.deck.size() == 0 or Kaou.deck.size() == 0 return true
    return true;
}

//void GameTemplate::lets_play() {
//    // Get called by main function
//    // How to arrange function call
//    initialization();
//    while(!is_the_end()) {
//        next_turn();
//        who_wins_this_turn();
//    }
//}
