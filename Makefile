CC = g++
#CC = clang++
CFLAGS = -Wall -std=c++11
#CFLAGS = -std=c++11 -stdlib=libc++ -Wc++11-extensions

TARGET_OUTPUT = main

OBJS = main.o Card.o Deck.o Player.o DeckBuilder.o Board.o GameTemplate.o Bataille.o Uno.o Scopa.o Briscola.o HuitAmericain.o

.PHONY: all clean test

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET_OUTPUT)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Card.o: card-game/Card.cpp card-game/Card.h
	$(CC) $(CFLAGS) -c card-game/Card.cpp

Deck.o: card-game/Deck.cpp card-game/DeckTest.h
	$(CC) $(CFLAGS) -c card-game/Deck.cpp
		
Player.o: card-game/Player.cpp card-game/Player.h
	$(CC) $(CFLAGS) -c card-game/Player.cpp
	
DeckBuilder.o: card-game/DeckBuilder.cpp card-game/DeckBuilder.h
	$(CC) $(CFLAGS) -c card-game/DeckBuilder.cpp

Board.o: card-game/Board.cpp card-game/Board.h
	$(CC) $(CFLAGS) -c card-game/Board.cpp

GameTemplate.o: examples/GameTemplate.cpp examples/GameTemplate.h
	$(CC) $(CFLAGS) -c examples/GameTemplate.cpp

Bataille.o: examples/Bataille.cpp examples/Bataille.h
	$(CC) $(CFLAGS) -c examples/Bataille.cpp

Uno.o: examples/Uno.cpp examples/Uno.h examples/UnoCards.h
	$(CC) $(CFLAGS) -c examples/Uno.cpp

HuitAmericain.o: examples/HuitAmericain.cpp examples/HuitAmericain.h
	$(CC) $(CFLAGS) -c examples/HuitAmericain.cpp

Briscola.o: examples/Briscola.cpp examples/Briscola.h
	$(CC) $(CFLAGS) -c examples/Briscola.cpp

Scopa.o: examples/Scopa.cpp examples/Scopa.h examples/ScopaCards.h
	$(CC) $(CFLAGS) -c examples/Scopa.cpp

# TEST SECTION
TEST_OBJS = Card.o Deck.o Gtest.o DeckTest.o
TEST_OUTPUT = test
TEST_DIR = tests
GTEST_MAIN := lib/Google_tests/
GTEST_DIR := lib/Google_tests/lib/googletest
LDFLAGS := lgtest.a lgtest_main.a -lpthread

test: Gtest-all Gtest-main $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(LDFLAGS) -o $(TEST_OUTPUT)

Gtest.o: $(GTEST_MAIN)/gtest.cpp
	$(CC) $(CFLAGS) -I$(GTEST_DIR)/include -c $(GTEST_MAIN)/gtest.cpp

DeckTest.o: tests/DeckTest.cpp
	$(CC) $(CFLAGS) -I$(GTEST_DIR)/include -c $(TEST_DIR)/DeckTest.cpp

Gtest-all:
	$(CC) $(CFLAGS) -I$(GTEST_DIR)/include -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest-all.cc
	ar -rv lgtest.a gtest-all.o

Gtest-main:
	$(CC) $(CFLAGS) -I$(GTEST_DIR)/include -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest_main.cc
	ar -rv lgtest_main.a gtest_main.o

clean: 
	rm *.o *.a $(TARGET_OUTPUT) $(TEST_OUTPUT)

