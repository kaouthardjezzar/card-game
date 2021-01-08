//
// Created by Kaou Thaar on 02/01/2021.
//

#include <iostream>
#include "HuitAmericain.h"
static int pos_player = 0;
void HuitAmericain::initialization() {
    std::cout << "Launching HuitAmericain " << std::endl;

    // Configuration des cartes
    std::vector<std::string> suits{"spade", "club", "diamond", "heart"};
    std::vector<int> range{0,1,2,3,4,5,6,7,8,9,10,11,12,13};
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
        return (special_cards[i] == card.get_value()) ;
    }
}
void HuitAmericain::first_turn(){
    Card card = board.get_deck().watch_front_card();
    while (isSpecialCard(card)){
        board.get_deck().shuffle();
        card = board.get_deck().watch_front_card();
    }
    board.get_temp_deck().add_card(board.get_deck().take_front_card());

};

void HuitAmericain::next_turn() {
  //  std::vector<bool> winner(board.get_players().size());
    excute_round();
    // As the function said
    display_game_status();


}

void HuitAmericain::display_game_status() {

}

void HuitAmericain::excute_round() {
        displayPlayerStat(pos_player);
        if(!chooseCard(reinterpret_cast<Player &>(board.get_players()[pos_player]))){
            if (validCard(board.get_deck().watch_front_card())){
                board.get_temp_deck().add_card(board.get_deck().take_front_card());
                // si la dernière carté joué par le joueur précédent était spécial (traitement spécial)
                if (isSpecialCard(board.get_temp_deck().watch_front_card())) specialProcess ();
                if (pos_player++ == board.get_players().size()) pos_player = 0 ;
                else pos_player++;
            }
            else {
                board.get_players()[pos_player]->get_deck()->add_card(board.get_deck().take_front_card());
                if (pos_player++ == board.get_players().size()) pos_player = 0 ;
                else pos_player++;
            }
        }
}

void HuitAmericain::specialProcess() {
    if (board.get_temp_deck().watch_front_card().get_label()=="joker") { // piocher +4 cartes
        pos_player ++;
        for (int i =0; i<4 ; i++){
            board.get_players()[pos_player]->get_deck()->add_card(board.get_deck().take_front_card());
        }
        pos_player --;
    }
    else {
        switch (board.get_temp_deck().watch_front_card().get_value()) {
            case 1: {

            }
            case 11: {
                pos_player++;
            }
            case 2: {
                    pos_player++;
                    for (int i = 0; i < 4; i++) {
                        board.get_players()[pos_player]->get_deck()->add_card(board.get_deck().take_front_card());
                    }
                    pos_player--;
            }
            case 8: {

            }
        }
    }

}

bool HuitAmericain::chooseCard(Player &player) {
    for (int i= 0; i< player.get_deck()->get_nbcards();i++)
    {
        if (validCard(player.get_deck()->watch_card_at(i))){
            board.get_temp_deck().add_card(player.get_deck()->take_card_at(i));
            if (pos_player++ == board.get_players().size()) pos_player = 0 ;
            else pos_player++;
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

}

void HuitAmericain::compute_winner(std::vector<bool> winner) {

}

bool HuitAmericain::validCard(Card &card) {
    return (card.get_value() ==
    board.get_temp_deck().watch_front_card().get_value() or
    card.isSameCol(board.get_temp_deck().watch_front_card()) or isSpecialCard(card));
}

void HuitAmericain::displayPlayerStat(int pos) {
        std::cout << "c'est le tour de joueur" << pos +1 << std::endl;
        std::cout << "le joueur" << board.get_players()[pos]->get_name() << " a comme cartes " << std::endl;
        std::cout << board.get_players()[pos]->affdeck();
        std::cout << std::endl;
        std::cout << "la carte à recouvrir est : " << board.get_temp_deck().watch_front_card() << std::endl;
}


