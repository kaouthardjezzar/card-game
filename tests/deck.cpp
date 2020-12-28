//
// Created by Ny Andrianina Mamy on 28/12/2020.
//

//
// Created by Ny Andrianina Mamy on 21/12/2020.
//
#include "gtest/gtest.h"
#include "../card-game/Deck.h"

TEST(Deck, CreateBasicDeck) {
    Deck deck;
    ASSERT_TRUE(true);
}

TEST(Deck, SplitDeck) {
    Deck deck;

    int parts = 20;

    for(int i = 0; i < parts; ++i){
        std::unique_ptr<Card> card = std::unique_ptr<Card>(new Card("spade", i));
        deck.add_card(card);
    }

    ASSERT_TRUE(deck.get_nbcards() == parts);

    std::vector<std::unique_ptr<Deck>> decks;

    decks.push_back(std::unique_ptr<Deck>(new Deck()));
    decks.push_back(std::unique_ptr<Deck>(new Deck()));

    deck.split(decks);

    ASSERT_TRUE(deck.get_nbcards() == 0);
    ASSERT_TRUE(decks[0]->get_nbcards() == parts/2);
    ASSERT_TRUE(decks[1]->get_nbcards() == parts/2);
};

TEST(Deck, TakeFrontCard) {
    Deck deck;
    std::unique_ptr<Card> card1 = std::unique_ptr<Card>(new Card("spade", 1));
    std::unique_ptr<Card> card2 = std::unique_ptr<Card>(new Card("spade", 2));

    deck.add_card(card1);
    deck.add_card(card2);
    std::unique_ptr<Card> took_card2 = std::move(deck.take_front_card());
    ASSERT_TRUE(took_card2->get_value() == 2);
}

TEST(Deck, RemoveFrontCard) {
    Deck deck;
    std::unique_ptr<Card> card1 = std::unique_ptr<Card>(new Card("spade", 1));
    std::unique_ptr<Card> card2 = std::unique_ptr<Card>(new Card("spade", 2));

    deck.add_card(card1);
    deck.add_card(card2);

    deck.remove_front_card();

    std::unique_ptr<Card> took_card1 = std::move(deck.take_front_card());
    ASSERT_TRUE(took_card1->get_value() == 1);
}