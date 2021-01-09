//
// Created by Ny Andrianina Mamy on 29/12/2020.
//

#ifndef CARD_GAME_UNO_H
#define CARD_GAME_UNO_H

#include "GameTemplate.h"
#include "../card-game/Board.h"
#include "UnoCards.h"
#include <iostream>

#define SKIPLINE std::cout<<std::endl;

class Uno  {
private:
    Board board;

    static bool is_special_card(const Card& card);

    static void compute_special_card(const Card& card, Board& board);

    static void compute_normal_card(const Card& card, Board& board);

    static void display_valid_move(Player& current_player, const Card& card_on_board);

    int make_a_choice() {
        Player& current_player = board.get_current_player();
        Card &card_on_board = board.get_temp_deck().watch_front_card();

        display_valid_move(current_player, card_on_board);
        int choice = -1;
        choice = ask_player<int>("Vous pouvez choisir : ");
        display_valid_move(current_player, card_on_board);

        return choice;
    };

    void compute_choice(int choice) {
        Player& current_player = board.get_current_player();
        if(choice == DRAW) { // Player can't move and needs to draw a card
            Board::safe_draw_cards_from_deck(current_player, board.get_deck(), 1);
        } else if(choice == NO_UNO) { // Player didn't say UNO so he must draw two cards
            std::cout << current_player << " n'a pas crié Uno et doit piocher deux(2) cartes " << std::endl;
            Board::safe_draw_cards_from_deck(current_player, board.get_deck(), 2);
            std::cout << "Vos cartes ont été piochées automatiquement " << std::endl;
        } else { // Pick chosen card
            std::unique_ptr<Card> card = current_player.get_deck()->take_card_at(choice-1);
            if(card == nullptr) {return;}

            if(is_special_card(*card)) {
                compute_special_card(*card,  board);
            } else {
                compute_normal_card(*card, board);
            }
            board.get_temp_deck().add_card(std::move(card));
        }
    }

protected:
    void initialization() ;

    void next_turn() ;

    void first_turn() ;

    // Utils
    template<typename T>
    T ask_player(const std::string& title)
    {
        T x = 0;
        std::cout << title;
        while (!( std::cin >> x))
        {
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Veuillez entrer un nombre/mot correct: " << endl;
            std::cout << title;
        }
        std::cin.clear();
        std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return (x);
    }

    void display_game_status();

    bool is_the_end();

    void end_of_game();

    void compute_winner();

public:
    Uno() = default;
    virtual ~Uno() = default;

    void lets_play() {
        initialization();
        first_turn();
        while(!is_the_end()) {
            next_turn();
        }
        end_of_game();
    }

};


#endif //CARD_GAME_UNO_H
