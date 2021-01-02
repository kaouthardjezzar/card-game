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

void Board::increase_round() {
    round++;
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

void Board::shuffle_deck() {
    deck->shuffle();
}

void Board::add_player(std::unique_ptr<Player>& player) {
    players.push_back(std::move(player));
}

void Board::affect_decks_toplayers(std::vector<std::unique_ptr<Deck>>& decks) {
    for(int i=0; i < get_players().size(); ++i) {
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

