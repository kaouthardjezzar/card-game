//
// Created by Ny Andrianina Mamy on 21/12/2020.
//

#include "Board.h"

#include <utility>

Deck& Board::get_deck() {
    return *deck;
}
void Board::set_deck(std::unique_ptr<Deck> _deck) {
    deck = std::move(_deck);
}

Deck& Board::get_temp_deck() {
    return *temp_deck;
}

void Board::next_round() {
    round++;
    turn = compute_next_turn();
}

int Board::get_round() const {
    return round;
}

int Board::get_turn() const {
    return turn;
}

void Board::set_turn(int _turn) {
    turn = _turn;
}

void Board::set_round(int _round){
    round = _round;
}

void Board::shuffle_deck() {
    deck->shuffle();
}

void Board::add_player(std::unique_ptr<Player>& player) {
    players.push_back(std::move(player));
}

void Board::affect_decks_toplayers(std::vector<std::unique_ptr<Deck>>& decks) {
    for(int i=0; i < (int) get_players().size(); ++i) {
        get_players()[i]->set_deck(decks[i]);
    }
}

std::vector<std::unique_ptr<Player>>& Board::get_players() {
    return players;
}

void Board::create_players(std::vector<string>& _players) {
    for(const string& name: _players) {
        std::unique_ptr<Player> player = std::unique_ptr<Player>(new Player(name));
        add_player(player);
    }
}

int Board::compute_next_turn() const {
    int next = turn+direction;
    if(next < 0) {
        return (int)players.size()-1;
    }
    if (next== (int)players.size()) {
        return 0;
    }
    return next;
}

Player& Board::get_current_player() {
    int current_player_id = get_turn() % (int)players.size();
    auto& current_player = players[current_player_id];
    return *current_player;
}

Player& Board::get_next_player() {
    int next_player_id = compute_next_turn() % (int) players.size();
    auto& next_player = players[next_player_id];
    return *next_player;
}

void Board::reverse_direction() {
    direction = -direction;
}

void Board::safe_draw_cards_from_deck(Deck &dest, Deck &source, int how_many) {
    assert(how_many > 0);
    for(int i=0; i < how_many; ++i){
        std::unique_ptr<Card> card = source.take_front_card();
        if(card != nullptr) {
            dest.add_card(std::move(card));
        }
    }
}

void Board::safe_draw_cards_from_deck(Player &player, Deck &deck, int how_many) {
    Board::safe_draw_cards_from_deck(*player.get_deck(), deck, how_many);
}

int Board::get_direction() const {
    return direction;
}

