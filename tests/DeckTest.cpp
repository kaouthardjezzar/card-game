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

TEST(Deck, SplitHalfDeck) {
    Deck deck;

    int parts = 20;

    for(int i = 0; i < parts; ++i){
        std::unique_ptr<Card> card = std::unique_ptr<Card>(new Card("spade", i));
        deck.add_card(std::move(card));
    }

    ASSERT_TRUE(deck.get_nbcards() == parts);

    std::vector<std::unique_ptr<Deck>> decks;

    deck.split_half(decks);

    ASSERT_TRUE(deck.get_nbcards() == 0);
    ASSERT_TRUE(decks[0]->get_nbcards() == parts/2);
    ASSERT_TRUE(decks[1]->get_nbcards() == parts/2);
};

TEST(Deck, TakeFrontCard) {
    Deck deck;
    std::unique_ptr<Card> card1 = std::unique_ptr<Card>(new Card("spade", 1));
    std::unique_ptr<Card> card2 = std::unique_ptr<Card>(new Card("spade", 2));

    deck.add_card(std::move(card1));
    deck.add_card(std::move(card2));
    std::unique_ptr<Card> took_card2 = deck.take_front_card();
    ASSERT_TRUE(took_card2->get_value() == 2);
}

TEST(Deck, TakeCardAt) {
    Deck deck;
    std::unique_ptr<Card> card1 = std::unique_ptr<Card>(new Card("spade", 1));
    std::unique_ptr<Card> card2 = std::unique_ptr<Card>(new Card("spade", 2));

    deck.add_card(std::move(card1));
    deck.add_card(std::move(card2));
    std::unique_ptr<Card> took_card2 = std::move(deck.take_card_at(1));
    ASSERT_TRUE(took_card2->get_value() == 2);
}

TEST(Deck, RemoveFrontCard) {
    Deck deck;
    std::unique_ptr<Card> card1 = std::unique_ptr<Card>(new Card("spade", 1));
    std::unique_ptr<Card> card2 = std::unique_ptr<Card>(new Card("spade", 2));

    deck.add_card(std::move(card1));
    deck.add_card(std::move(card2));

    std::unique_ptr<Card> took_card1 = std::move(deck.take_front_card());
    ASSERT_TRUE(took_card1->get_value() == 1);
}

TEST(Deck, SplitLimitedParts) {

    Deck deck;

    int parts = 28;

    for(int i = 0; i < parts; ++i){
        std::unique_ptr<Card> card = std::unique_ptr<Card>(new Card("spade", i));
        deck.add_card(std::move(card));
    }

    ASSERT_TRUE(deck.get_nbcards() == parts);

    std::vector<std::unique_ptr<Deck>> decks;

    deck.distribute(3, 7, decks);

    ASSERT_TRUE(deck.get_nbcards() == 7);
    ASSERT_TRUE(decks[0]->get_nbcards() == 7);
    ASSERT_TRUE(decks[1]->get_nbcards() == 7);
    ASSERT_TRUE(decks[2]->get_nbcards() == 7);

}

TEST(Deck, Shuffle) {
    Deck deck;
    for(int i =0; i < 10; i++) {
       deck.add_card("TEST", i);
    }
    deck.shuffle();

    bool isSorted = true;
    int last = deck.watch_card_at(0).get_value(), next = 0;
    for(int i = 1; i < 10; i++) {
        if(deck.watch_card_at(i).get_value() < last) {
            isSorted = false;
        }
    }

    ASSERT_FALSE(isSorted);
}