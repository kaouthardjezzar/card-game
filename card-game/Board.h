//
// Created by Ny Andrianina Mamy on 21/12/2020.
//

#ifndef CARD_GAME_BOARD_H
#define CARD_GAME_BOARD_H

#include <vector>
#include <memory>
#include "DeckBuilder.h"
#include "Player.h"

class Board {
private:
    /*
     * Contient le paquet de carte principal
     */
    std::unique_ptr<Deck> deck;

    /*
     * Contient les joueurs
     */
    std::vector<std::unique_ptr<Player>> players;

    /*
     * Contient les cartes qui sont posées sur la table
     * Soit des cartes venant de la main des joueurs
     * Soit des cartes piochées du paquet principal
     */
    std::unique_ptr<Deck> temp_deck;

    /*
     * Indique le nombre de ronde
     */
    int round;

    /*
     * Indique l'index du joueur qui joue
     */
    int turn;

    /*
     * Indique le sens du jeu
     * -1: sens contraire de l'aiguille d'une montre
     * 1: sens de l'aiguille d'une montre
     */
    int direction;


public:

    /*
     * Permet de prendre des cartes d'un deck vers un autre deck
     * Et surtout d'eviter qu'un nullptr soit ajouté
     */
    static void safe_draw_cards_from_deck(Player& player, Deck& deck, int how_many = 1); // Handle nullptr if deck is empty
    static void safe_draw_cards_from_deck(Deck& dest, Deck& source, int how_many = 1); // Handle nullptr if deck is empty

    explicit Board(): deck{new Deck()}, players{}, temp_deck{new Deck()}, round{0}, turn{0}, direction(1) {
    }
    virtual ~Board() = default;

    /*
     * Affecte des vecteurs de Deck aux Joueurs
     * Ils devront être de mêmes longueurs
     */
    void affect_decks_toplayers(std::vector<std::unique_ptr<Deck>>& decks);

    /*
     * Mélange le paquet principal
     */
    void shuffle_deck();

    void set_deck(std::unique_ptr<Deck> _deck);

    Deck& get_deck();

    Deck& get_temp_deck();

    void next_round();

    int get_round() const;

    int get_turn() const;

    int get_direction() const;

    void set_turn(int _turn);

    void set_round(int _round);

    void create_players(std::vector<std::string>& _players);

    void add_player(std::unique_ptr<Player>& player);

    std::vector<std::unique_ptr<Player>>& get_players();

    Player& get_current_player();

    Player& get_next_player();

    void reverse_direction();
    int compute_next_turn() const;

};

#endif //CARD_GAME_BOARD_H
