//
// Created by Ny Andrianina Mamy on 12/12/2020.
//

#ifndef CARD_GAME_DECK_H
#define CARD_GAME_DECK_H

#include <vector>
#include <memory>
#include "Card.h"
#include <cassert>


class Deck {
private:
    /*
     * Contient les cartes du paquet
     */
    std::vector<std::unique_ptr<Card>> cards;

    /*
     * Permet de diviser ce paquet en plusieurs paquets selon une part
     */
    void split(std::vector<std::unique_ptr<Deck>>& decks, int parts);

public:
   Deck(): cards{} {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Creating Deck \n";
    }

    virtual ~Deck() {
        LOG_INIT_COUT();
        logd(LOG_DEBUG) << "Deleting Deck containing" << " , Cards : " << (int)cards.size() << "\n";
    }

    /*
     * Utilisation de la Classe en tant qu'Iterator
     */
    typedef Card * iterator;
    typedef const Card * const_iterator;

    std::vector<std::unique_ptr<Card>>::iterator begin();
    std::vector<std::unique_ptr<Card>>::iterator end();

    /*
     * Ajoute une carte à ce paquet
     */
    void add_card(std::string suit, int value);
    void add_card(std::string label, std::string suit, int value);
    void add_card(std::unique_ptr<Card> card);

    /*
     * Mélange les cartes
     */
    void shuffle();

    /*
     * Vide le paquet
     */
    void clean_deck();

    /*
    * Distribue des paquets de "n" cartes vers "n" joueurs
    */
    void distribute(int nb_players, int nb_cards_per_player, std::vector<std::unique_ptr<Deck>> &decks);

    /*
     * Prend la première carte en haut
     */
    unique_ptr<Card> take_front_card();

    /*
     * Prend une carte à une certaine position
     */
    unique_ptr<Card> take_card_at(int pos);

    /*
     * Permet de regarder la carte en haut sans l'enlever du paquet
     */
    Card& watch_front_card() const;

    /*
     * Permet de regarder une carte à une position sans l'enlever du paquet
     */
    Card& watch_card_at(int pos) const;

    /*
     * Divise un paquet en deux paquets
     */
    void split_half(std::vector<std::unique_ptr<Deck>>& decks);

    /*
     * Indique le nombre de cartes
     */
    int get_nbcards() const;

    /*
     * Indique si le paquet est vide
     */
    bool isEmpty() const;

    friend std::ostream & operator << (std::ostream & out,const Deck & aDeck);
};


#endif //CARD_GAME_DECK_H
