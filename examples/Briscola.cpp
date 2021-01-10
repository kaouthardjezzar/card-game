//
// Created by Kaou Thaar on 09/01/2021.
//

#include "Briscola.h"

void Briscola::initialization() {

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



    // Split cards to players
    // chaque joueurs a 3 cartes
    std::vector<std::unique_ptr<Deck>> decks;
    board.get_deck().distribute(board.get_players().size(),3,decks);
    board.affect_decks_toplayers(decks);
}


void Briscola::first_turn(){
    atout = board.get_deck().take_front_card();
    cout << "la carte atout est : " << atout->get_suit() << " " << atout->get_value() << endl;
    std::cout << "\n" << endl;
    board.set_round(1);
}


void Briscola::next_turn() {
    if (board.get_round()==0) {
        first_turn();
    }
    // Check round winner
    std::cout << "Tour no : " << board.get_round() << std::endl;

    std::vector<bool> winner(board.get_players().size());

    who_wins_this_turn(winner);

    // As the function said
    display_game_status(winner);

    // Stuff that needs to be done when someone wins
    compute_winner(winner);
    board.set_round(board.get_round()+1);

}

bool Briscola::is_the_end() {
    return std::any_of(
            board.get_players().begin(),
            board.get_players().end(),
            [](const std::unique_ptr<Player> &player) {
                return player->get_deck()->isEmpty();
            });
}

void Briscola::end_of_game() {
    std::cout << "Fin du jeu  : " << std::endl;

    for (int i = 0; i< (int)board.get_players().size(); i++) {
        std::cout << board.get_players()[i]->get_name() << " a ganée  : " << points[i] << "manches " <<std::endl;
    }
    for (int j= 0; j < (int)board.get_players().size();j++) {
    }
        for (int j= 0; j < (int)board.get_players().size();j++) {
        int cpt = 0;
        for (int i = 0; i < (int)board.get_players().size(); i++) {
            if ( points [j] < points [i]) {
                break;
            }
            else {
                cpt ++;
            }
        }
        if (cpt == (int)board.get_players().size()){
            std::cout << board.get_players()[j]->get_name() << " a gagné " << std::endl;
            break;}
    }

}



void Briscola::end_of_manche() {
    std::cout << "Fin de la manche : " << std::endl << std::endl;

    std::vector<int> scores;
    for (const auto &player : board.get_players()) {
        scores.push_back(player->get_score());
        std::cout << player->get_name() << " a eu le score : " << player->get_score() << std::endl;
    }
    for (int j= 0; j < (int)board.get_players().size();j++) {
        int cpt = 0;
        for (int i = 0; i < (int)board.get_players().size(); i++) {
            if (scores[j] < scores [i]) break;
            else cpt ++;
        }
        if (cpt == (int)board.get_players().size()){
        std::cout << board.get_players()[j]->get_name() << " a gagné la manche " << std::endl;
        std::cout << "\n" << endl;
        points [j] ++;
        break;}
    }
    for (int k= 0; k< (int)board.get_players().size();k++)
    {
        board.get_players()[k]->set_score(0);
    }
    board.get_temp_deck().clean_deck();
    board.get_deck().clean_deck();
    board.set_turn(0);
    board.set_round(0);
}


void Briscola::display_game_status(std::vector<bool> winner) {
    for(int i=0 ; i < (int)winner.size(); ++i){
        if(winner[i]) {
            std::cout << board.get_players()[i]->get_name() << " a gagné ce tour " << std::endl;
        }
    }

    // Saut de ligne
    std::cout << "\n" << std::endl;
}

void Briscola::who_wins_this_turn(vector<bool> &winner) {


    std::vector<Card> cards(winner.size());
    for (int i = 0; i < (int)winner.size(); i++) {
        cards[board.get_turn()] = chooseCard();
        if (board.get_turn() +1 == (int)board.get_players().size()) {
            board.set_turn(0);
        }
        else {board.set_turn(board.get_turn() +1);}
    }
    for (int j= 0; j < (int)cards.size();j++) {
        bool ok = true;
        for (int i = 0; i < (int)cards.size(); i++) {
            if ( i !=j ){
            if (cards[j] < cards [i] || cards[j] == cards [i] ) {ok = false;
            break;}}
        }
        winner [j] = ok;
    }
}

void Briscola::compute_winner(std::vector<bool> winner) {
    if(std::all_of(winner.begin(), winner.end(), [](bool win) { return win; })) {
        return; // Don't do anything
    }

    for (int i= 0 ; i < (int)winner.size(); i++){
        if (winner[i]){
            board.get_players()[i]->set_score(
                    board.get_players()[i]->get_score()+2
                    );
        }
    }
}

Card & Briscola::chooseCard() {
    if (board.get_temp_deck().isEmpty()) { // si premier joueur a jouer ;


        for (int i = 0; i < board.get_players()[board.get_turn()]->get_deck()->get_nbcards(); i++) {
            // il joue une carte de meme couleur de l'atout pour augmenter les chances de ganger
            if (board.get_players()[board.get_turn()]->get_deck()->watch_card_at(i).isSameCol
                    (atout)) {
                // on stocke la carte jouée dans temps deck
                board.get_temp_deck().add_card(board.get_players()[board.get_turn()]->get_deck()->take_card_at(i));
                // a chaque fois il joue , il pioche pour le next tour, puisque il doit toujours avoir 3 cartes dans la main
                if (!board.get_deck().isEmpty())
                {board.get_players()[board.get_turn()]->get_deck()->add_card(board.get_deck().take_front_card());}
                std::cout << board.get_players()[board.get_turn()]->get_name() << " : " ;
                cout << "carte jouee : " << board.get_temp_deck().watch_front_card() << endl;
                return board.get_temp_deck().watch_front_card();
            }
        }
        board.get_temp_deck().add_card(board.get_players()[board.get_turn()]->get_deck()->take_front_card());
        // a chaque fois il joue , il pioche pour le next tour, puisque il doit toujours avoir 3 cartes dans la main
        if (!board.get_deck().isEmpty())
        {board.get_players()[board.get_turn()]->get_deck()->add_card(board.get_deck().take_front_card());}
        std::cout << board.get_players()[board.get_turn()]->get_name() << " : " ;
        cout << "carte jouee : " << board.get_temp_deck().watch_front_card() << endl;
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
                if (!board.get_deck().isEmpty())
                {board.get_players()[board.get_turn()]->get_deck()->add_card(board.get_deck().take_front_card());}
                std::cout << board.get_players()[board.get_turn()]->get_name() << " : " ;
                cout << "carte jouee : " << board.get_temp_deck().watch_front_card() << endl;
                return board.get_temp_deck().watch_front_card();
            }
        }
        // si on trouve pas une carte valide, on joue nimporte quelle carte
        board.get_temp_deck().add_card(board.get_players()[board.get_turn()]->get_deck()->take_front_card());
        // a chaque fois il joue , il pioche pour le next tour, puisque il doit toujours avoir 3 cartes dans la main
        if (!board.get_deck().isEmpty())
        {board.get_players()[board.get_turn()]->get_deck()->add_card(board.get_deck().take_front_card());}
        std::cout << board.get_players()[board.get_turn()]->get_name() << " : " ;
        cout << "carte jouee : " << board.get_temp_deck().watch_front_card() << endl;
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

void Briscola::lets_play () {
    std::cout << "Launching Briscola " << std::endl;
    std::cout << "\n" << endl;

    // Players
    std::vector<string> players = {"John", "Jane", "mike", "kaou"};
    board.create_players(players);
    for (int i = 0; i < 3; i++) {  // jouer 3 manches
        std::cout << "Manche :  " << i << std::endl;
        initialization();
        while (!is_the_end()) {
            next_turn();
        }
        end_of_manche();
    }
    end_of_game();
}