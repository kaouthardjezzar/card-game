//
// Created by Ny Andrianina Mamy on 10/01/2021.
//

#include "gtest/gtest.h"
#include "../card-game/Player.h"

struct PlayerTest: testing::Test {
    Player *john;

    PlayerTest(): john{new Player("John")} {

    }

    ~PlayerTest() override {
        delete john;
    }
};

TEST_F(PlayerTest, PlayerStartsEmpty) {
    ASSERT_TRUE(john->get_deck().isEmpty());
}

