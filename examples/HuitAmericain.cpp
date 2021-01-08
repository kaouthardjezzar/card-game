//
// Created by Kaou Thaar on 02/01/2021.
//

#include <iostream>
#include "HuitAmericain.h"


static string suit = "";
void HuitAmericain::initialization() {
    std::cout << "Launching HuitAmericain " << std::endl;
    board.set_turn(0);
    // Configuration des cartes
    std::vector<std::string> suits{"spade", "club", "diamond", "heart"};
    std::vector<int> range{1,2,3,4,5,6,7,8,9,10,11,12,13};
    DeckBuilder deck_builder;
    std::unique_ptr<Deck> deck = deck_builder.create()
            .with_suits(suits)
            .with_range(range)
            .build();
    // ajouter deux cartes des joker

    deck->add_card("joker", "", 0);
    deck->add_card("joker", "", 0);

    assert(deck->get_nbcards() == 54);

    board.set_deck(std::move(deck));

    // Shuffle deck
    board.shuffle_deck();

    // Players
    std::vector<string> players = {"John", "Jane", "Mike"};
    board.create_players(players);

    // Split cards to players
    std::vector<std::unique_ptr<Deck>> decks;
    board.get_deck().distribute(board.get_players().size(),7,decks);
    for (int i=0; i < board.get_players().size(); i++){
        board.get_players()[i]->set_deck(decks[i]);
    }
}

bool HuitAmericain::isSpecialCard(const Card card) {
    for(int i = 0; i < special_cards.size(); i++){
        if (special_cards[i] == card.get_value()) {
            return true;
        }
    }
    return false;
}

void HuitAmericain::first_turn(){
    Card card = board.get_deck().watch_front_card();
    while (isSpecialCard(card)){
        board.get_deck().shuffle();
        card = board.get_deck().watch_front_card();
    }
    board.get_temp_deck().add_card(board.get_deck().take_front_card());
    board.set_round(1);
};

void HuitAmericain::next_turn() {
    if (board.get_round()==0) {
        first_turn();
    }
  //  std::vector<bool> winner(board.get_players().size());
    excute_round();
    // As the function said

}



void HuitAmericain::excute_round() {
        displayPlayerStat(board.get_turn());
        if (board.get_deck().isEmpty()) {
            std::unique_ptr<Card> card = board.get_temp_deck().take_front_card();
            for (int i=0; i < board.get_temp_deck().get_nbcards();i++) {
                board.get_deck().add_card(board.get_temp_deck().take_front_card());
                board.shuffle_deck();
            }
            board.get_temp_deck().add_card(std::move(card));
        }
        bool ok = chooseCard();
        if(!ok){
            if (validCard(board.get_deck().watch_front_card())){
                board.get_temp_deck().add_card(board.get_deck().take_front_card());
                // si la dernière carté joué par le joueur précédent était spécial (traitement spécial)
                if (isSpecialCard(board.get_temp_deck().watch_front_card())) specialProcess ();
                board.next_round();
            }
            else {
                board.get_players()[board.get_turn()]->get_deck()->add_card(board.get_deck().take_front_card());
                board.next_round();
            }
        }
}

void HuitAmericain::specialProcess() {
    if (board.get_temp_deck().watch_front_card().get_label()=="joker") { // piocher +4 cartes
        board.set_turn(board.get_turn()+1);
        for (int i =0; i<4 ; i++){
            if (board.get_deck().isEmpty()) {
                std::unique_ptr<Card> card = board.get_temp_deck().take_front_card();
                for (int i=0; i < board.get_temp_deck().get_nbcards();i++) {
                    board.get_deck().add_card(board.get_temp_deck().take_front_card());
                    board.shuffle_deck();
                }
                board.get_temp_deck().add_card(std::move(card));
            }
            board.get_players()[board.get_turn()]->get_deck()->add_card(board.get_deck().take_front_card());
        }
        board.set_turn(board.get_turn()-1);
    }
    else {
        switch (board.get_temp_deck().watch_front_card().get_value()) {
            case 1: {
                board.reverse_direction();
            }
            case 11: {
                board.set_turn(board.get_turn()+1);
            }
            case 2: {
                board.set_turn(board.get_turn()+1);
                for (int i = 0; i < 2; i++) {
                    if (board.get_deck().isEmpty()) {
                        std::unique_ptr<Card> card = board.get_temp_deck().take_front_card();
                        for (int i=0; i < board.get_temp_deck().get_nbcards();i++) {
                            board.get_deck().add_card(board.get_temp_deck().take_front_card());
                            board.shuffle_deck();
                        }
                        board.get_temp_deck().add_card(std::move(card));
                    }
                    board.get_players()[board.get_turn()]->get_deck()->add_card(board.get_deck().take_front_card());
                    }
                board.set_turn(board.get_turn()+1);
            }
        }
    }

}

bool HuitAmericain::chooseCard() {
    for (int i= 0; i< board.get_players()[board.get_turn()]->get_deck()->get_nbcards();i++)
    {
        if (validCard(board.get_players()[board.get_turn()]->get_deck()->watch_card_at(i))){
            board.get_temp_deck().add_card(board.get_players()[board.get_turn()]->get_deck()->take_card_at(i));
            if (isSpecialCard(board.get_temp_deck().watch_front_card())) specialProcess ();
            board.next_round();
            return true;
        }
    }
    return false;
}


bool HuitAmericain::is_the_end() {
    return std::any_of(
            board.get_players().begin(),
            board.get_players().end(),
            [](const std::unique_ptr<Player>& player) {
                return player->get_deck()->isEmpty();
            });
}

void HuitAmericain::end_of_game() {
    std::cout << "Fin du jeu " << std::endl;
    for (int i=0; i<board.get_players().size();i++){
        if (board.get_players()[i]->get_deck()->isEmpty()) {
            std::cout << board.get_players()[i]->get_name() << " a gagné" << endl;
        }
    }
}


bool HuitAmericain::validCard(Card &card) {
    return (card.get_value() ==
    board.get_temp_deck().watch_front_card().get_value() or
    card.isSameCol(board.get_temp_deck().watch_front_card()) or isSpecialCard(card));
}

void HuitAmericain::displayPlayerStat(int pos) {
        std::cout << "tour numero : "<<board.get_round() << endl;
        std::cout << "c'est le tour de joueur" << pos +1 << std::endl;
        std::cout << "le joueur" << board.get_players()[pos]->get_name() << " a comme cartes " << std::endl;
        std::cout << board.get_players()[pos]->affdeck();
        std::cout << std::endl;
        std::cout << "la carte à recouvrir est : " << board.get_temp_deck().watch_front_card() << std::endl;
}


