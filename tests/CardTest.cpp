//
// Created by Ny Andrianina Mamy on 21/12/2020.
//
#include "gtest/gtest.h"
#include "../card-game/Card.h"

TEST(Card, CreateBasicCard) {
    Card card("spade", 3);

    ASSERT_EQ(card.get_value(), 3);
}

TEST(Card, CompareCardValue) {
    // Only compare card by value
    Card card_inf("spade", 3);
    Card card_sup("spade", 4);

    ASSERT_GT(card_sup, card_inf);
}

