//
// Created by Kaou Thaar on 09/01/2021.
//

#include "Briscola.h"

void Briscola::initialization() {
    std::cout << "Launching Briscola " << std::endl;

    // Configuration des cartes ; on utilise pas 8, 9 et 10 pour avoir 40 cartes
    std::vector<std::string> suits{"spade", "club", "diamond", "heart"};
    std::vector<int> range{1,2,3,4,5,6,7,11,12,13};
    DeckBuilder deck_builder;
    std::unique_ptr<Deck> deck = deck_builder.create()
            .with_suits(suits)
            .with_range(range)
            .build();

    assert(deck->get_nbcards() == 40);

    board.set_deck(std::move(deck));

    // Shuffle deck
    board.shuffle_deck();

    // Players
    std::vector<string> players = {"John", "Jane"};
    board.create_players(players);

    // Split cards to players
    // chaque joueurs a 3 cartes
    std::vector<std::unique_ptr<Deck>> decks;
    board.get_deck().distribute(board.get_players().size(),3,decks);
    board.affect_decks_toplayers(decks);
    for (int i =0;i<board.get_players().size()){
        points.push_back(0);
    }
}


void Briscola::first_turn(){
    atout = board.get_deck().take_front_card();
    board.set_round(1);
}


void Briscola::next_turn() {
    if (board.get_round()==0) {
        first_turn();
    }
    // Check round winner
    std::vector<bool> winner(board.get_players().size());
    who_wins_this_turn(winner);

    // As the function said
    display_game_status(winner);

    // Stuff that needs to be done when someone wins
    compute_winner(winner);

    board.next_round();
}

bool Briscola::is_the_end() {
    if (board.get_deck().get_nbcards() < board.get_players().size()) return true;
    else return false;
}

void Briscola::end_of_game() {
    std::cout << "Fin du jeu  : " << std::endl;

}



void Briscola::end_of_manche() {
    std::cout << "Fin de la manche : " << std::endl;

    std::vector<int> scores;
    for (const auto &player : board.get_players()) {
        scores.push_back(player->get_score());
        std::cout << player->get_name() << " a eu le score : " << player->get_score() << std::endl;
    }
    for (int j= 0; j < board.get_players().size();j++) {
        int cpt = 0;
        for (int i = 0; board.get_players().size(); i++) {
            if (scores[j] < scores [i]) break;
            else cpt ++;
        }
        if (cpt == board.get_players().size()){
        std::cout << board.get_players()[j]->get_name() << " a gagné la manche " << std::endl;
        points [j] ++;
        break;}
    }
}


void Briscola::display_game_status(std::vector<bool> winner) {
    for(int i=0 ; i < winner.size(); ++i){
        if(winner[i]) {
            std::cout << board.get_players()[i]->get_name() << " a gagné ce tour " << std::endl;
        }
    }

    // Saut de ligne
    std::cout << "\n" << std::endl;
}

void Briscola::who_wins_this_turn(vector<bool> &winner) {

    std::vector<Card> cards(winner.size());
    for (int i = 0; i < winner.size(); i++) {
        cards[board.get_turn()-1] = chooseCard();
    }
    for (int j= 0; j < winner.size();j++) {
        bool ok = true;
        for (int i = 0; i < cards.size(); i++) {
            if (cards[j] < cards [i]) {ok = false;}
            break;
        }
        winner [j] = ok;
    }
}

void Briscola::compute_winner(std::vector<bool> winner) {
    if(std::all_of(winner.begin(), winner.end(), [](bool win) { return win; })) {
        return; // Don't do anything
    }

    for (int i= 0 ; i < winner.size(); i++){
        if (winner[i]){
            board.get_players()[i]->set_score(
                    board.get_players()[i]->get_score()+2
                    );
        }
    }
}

Card & Briscola::chooseCard() {
    if (board.get_temp_deck().isEmpty()) { // si premier joueur a jouer ;
        cout << "premier a commencer " << endl;
        std::cout << "Tour no : " << board.get_round() << std::endl;

        for (int i = 0; i < board.get_players()[board.get_turn()]->get_deck()->get_nbcards(); i++) {
            // il joue une carte de meme couleur de l'atout pour augmenter les chances de ganger
            if (board.get_players()[board.get_turn()]->get_deck()->watch_card_at(i).isSameCol
                    (atout)) {
                // on stocke la carte jouée dans temps deck
                board.get_temp_deck().add_card(board.get_players()[board.get_turn()]->get_deck()->take_card_at(i));
                // a chaque fois il joue , il pioche pour le next tour, puisque il doit toujours avoir 3 cartes dans la main
                board.get_players()[board.get_turn()]->get_deck()->add_card(board.get_deck().take_front_card());
                board.next_round();
                std::cout << board.get_players()[board.get_turn()]->get_name() << " : " ;
                cout << "carte jouee : " << board.get_temp_deck().watch_front_card();
                return board.get_temp_deck().watch_front_card();
            }
        }
        board.get_temp_deck().add_card(board.get_players()[board.get_turn()]->get_deck()->take_front_card());
        // a chaque fois il joue , il pioche pour le next tour, puisque il doit toujours avoir 3 cartes dans la main
        board.get_players()[board.get_turn()]->get_deck()->add_card(board.get_deck().take_front_card());
        board.next_round();
        std::cout << board.get_players()[board.get_turn()]->get_name() << " : " ;
        cout << "carte jouee : " << board.get_temp_deck().watch_front_card();
        return board.get_temp_deck().watch_front_card();
    } else {
        // choisir une carte valide qu'elle soit de valeur supérieur et atout ou d'une valeur superieur uniquement
        for (int i = 0; i < board.get_players()[board.get_turn()]->get_deck()->get_nbcards(); i++) {
            if ((validCard(board.get_players()[board.get_turn()]->get_deck()->watch_card_at(i)) and
                    board.get_players()[board.get_turn()]->get_deck()->watch_card_at(i).isSameCol(atout)) or
                    (validCard(board.get_players()[board.get_turn()]->get_deck()->watch_card_at(i)
            ))){
                board.get_temp_deck().add_card(board.get_players()[board.get_turn()]->get_deck()->take_card_at(i));
                // a chaque fois il joue , il pioche pour le next tour, puisque il doit toujours avoir 3 cartes dans la main
                board.get_players()[board.get_turn()]->get_deck()->add_card(board.get_deck().take_front_card());
                board.next_round();
                std::cout << board.get_players()[board.get_turn()]->get_name() << " : " ;
                cout << "carte jouee : " << board.get_temp_deck().watch_front_card();
                return board.get_temp_deck().watch_front_card();
            }
        }
        // si on trouve pas une carte valide, on joue nimporte quelle carte
        board.get_temp_deck().add_card(board.get_players()[board.get_turn()]->get_deck()->take_front_card());
        // a chaque fois il joue , il pioche pour le next tour, puisque il doit toujours avoir 3 cartes dans la main
        board.get_players()[board.get_turn()]->get_deck()->add_card(board.get_deck().take_front_card());
        board.next_round();
        std::cout << board.get_players()[board.get_turn()]->get_name() << " : " ;
        cout << "carte jouee : " << board.get_temp_deck().watch_front_card();
        return board.get_temp_deck().watch_front_card();
    }
}



bool Briscola::validCard(Card &card) {
    bool yes = true;
    for (int i = 0; i < board.get_temp_deck().get_nbcards(); i++) {
        if (card.get_value() < board.get_temp_deck().watch_front_card().get_value()) {
            yes =false;
        }
    }
    return  yes;
}