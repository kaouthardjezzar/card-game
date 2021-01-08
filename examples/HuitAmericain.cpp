//
// Created by Kaou Thaar on 02/01/2021.
//

#include <iostream>
#include "HuitAmericain.h"

void HuitAmericain::initialization() {
    std::cout << "Launching HuitAmericain " << std::endl;

    // Configuration des cartes
    std::vector<std::string> suits{"spade", "club", "diamond", "heart"};
    std::vector<int> range{0,1,2,3,4,5,6,7,8,9,10,11,12,13};
    DeckBuilder deck_builder;
    std::unique_ptr<Deck> deck = deck_builder.create()
            ->with_suits(suits)
            ->with_range(range)
            ->build();

    deck->add_card("joker", "", 0);
    deck->add_card("joker", "", 0);

    assert(deck->get_nbcards() == 54);

    board.set_deck(std::move(deck));

    // Shuffle deck
    board.shuffle_deck();

    // Players
    std::vector<string> players = {"John", "Jane"};
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
        return (special_cards[i] == card.get_suit() or special_cards[i]==card.get_label()) ;
    }
}
void HuitAmericain::first_turn(){
    Card card = board.get_deck().watch_front_card();
    while (isSpecialCard(card)){
        board.get_deck().shuffle();
        card = board.get_deck().watch_front_card();
    }
    board.get_temp_deck().add_card(board.get_deck().take_front_card());
    board.get_deck().remove_front_card();

};

void HuitAmericain::next_turn() {
    std::vector<bool> winner(2);
    who_wins_this_turn();

    // As the function said
    display_game_status(winner);

    // Stuff that needs to be done when someone wins
    compute_winner(winner);

    board.increase_round();
}

void HuitAmericain::display_game_status(std::vector<bool> winner) {

}

void HuitAmericain::who_wins_this_turn() {
    auto &player_one = board.get_players()[0];
    auto &player_two = board.get_players()[1];

    for (int i= 0; i< player_one->get_deck()->get_nbcards();i++)
    {
        if (player_one->get_deck()->watch_card_at(i).get_value() ==
        board.get_temp_deck().watch_front_card().get_value() or
        player_one->get_deck()->watch_card_at(i).isSameCol(board.get_temp_deck().watch_front_card()) ){
            board.get_temp_deck().add_card(player_one->get_deck()->take_front_card());
            player_one->get_deck()->remove_front_card();
            break;
        }
        else {
            if (isSpecialCard(player_one->get_deck()->watch_card_at(i))) {
                board.get_temp_deck().add_card(player_one->get_deck()->take_front_card());
                player_one->get_deck()->remove_front_card();
                break;
            }
            else {
                
            }
        }
    }
    for (int i= 0; i< player_two->get_deck()->get_nbcards();i++)
    {
        if (player_two->get_deck()->watch_card_at(i).get_value() ==
            board.get_temp_deck().watch_front_card().get_value() or
            player_two->get_deck()->watch_card_at(i).isSameCol(board.get_temp_deck().watch_front_card()) ){
            board.get_temp_deck().add_card(player_two->get_deck()->take_front_card());
            player_two->get_deck()->remove_front_card();
            break;
        }
        else {
            if (isSpecialCard(player_two->get_deck()->watch_card_at(i))) {
                board.get_temp_deck().add_card(player_two->get_deck()->take_front_card());
                player_two->get_deck()->remove_front_card();
                break;
            }
        }
    }

}



void HuitAmericain::is_the_end() {

}

void HuitAmericain::end_of_game() {

}

void HuitAmericain::compute_winner(std::vector<bool> winner) {

}

bool HuitAmericain::isSameCol(const Card card) {

    return false;
}


