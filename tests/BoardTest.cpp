//
// Created by Ny Andrianina Mamy on 10/01/2021.
//

#include "gtest/gtest.h"
#include "../card-game/Board.h"

struct BoardTest: testing::Test {
    Board *board;
    std::unique_ptr<Player> john;
    std::unique_ptr<Player> sarah;


    BoardTest(): board{new Board()},
                john(std::unique_ptr<Player>(new Player("John"))),
                sarah(std::unique_ptr<Player>(new Player("Sarah")))
    {

    }

    ~BoardTest() override {
        delete board;
    }
};

TEST_F(BoardTest, BoardStartsEmpty) {
    ASSERT_TRUE( board->get_players().empty());
    ASSERT_TRUE(board->get_deck().isEmpty());
    ASSERT_TRUE(board->get_temp_deck().isEmpty());
    EXPECT_EQ(0, board->get_turn());
    EXPECT_EQ(0, board->get_round());
}

TEST_F(BoardTest, TurnStartsForward) {
    EXPECT_EQ(1, board->get_direction());
}

TEST_F(BoardTest, AddAlreadyCreatedPlayerToBoard) {
    board->add_player(john);
    ASSERT_TRUE(board->get_players()[0]->get_name() == "John");
    ASSERT_TRUE(john == nullptr);
    std::vector<std::string> players = {"Jane", "Doe"};
    board->create_players(players);
    EXPECT_EQ(3, (int)board->get_players().size());
}

TEST_F(BoardTest, AddPlayerFromStringsToBoard) {
    std::vector<std::string> players = {"Jane", "Doe"};
    board->create_players(players);
    EXPECT_EQ(players.size(), board->get_players().size());
}

TEST_F(BoardTest, SafeDrawingCardsWhenDeckIsEmpty) {
    Board::safe_draw_cards_from_deck(board->get_deck(), board->get_temp_deck(), 10);
    Board::safe_draw_cards_from_deck(*john, board->get_temp_deck(), 10);

    ASSERT_TRUE(board->get_deck().isEmpty());
    ASSERT_TRUE(board->get_temp_deck().isEmpty());
}

TEST_F(BoardTest, TurnGoesForward) {
    board->add_player(john);
    board->add_player(sarah);

    EXPECT_EQ(1, board->get_direction());
    EXPECT_EQ(0, board->get_turn());

    board->next_round();

    EXPECT_EQ(1, board->get_direction());
    EXPECT_EQ(1, board->get_turn());
}

TEST_F(BoardTest, TurnGoesBackward) {
    board->add_player(john);
    board->add_player(sarah);

    EXPECT_EQ(1, board->get_direction());
    EXPECT_EQ(0, board->get_turn());

    board->reverse_direction();
    board->next_round();

    EXPECT_EQ(-1, board->get_direction());
    EXPECT_EQ(1, board->get_turn());
}

TEST_F(BoardTest, CheckOnePLayerEmptyDeck) {
    board->add_player(john);
    ASSERT_TRUE(board->a_player_has_empty_deck());
}

