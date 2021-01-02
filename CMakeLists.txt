cmake_minimum_required(VERSION 3.17)
project(Card_Game)

set(CMAKE_CXX_STANDARD 11)

add_executable(Card_Game main.cpp card-game/Card.cpp card-game/Card.h examples/Bataille.cpp examples/Bataille.h examples/GameTemplate.cpp examples/GameTemplate.h card-game/Player.cpp card-game/Player.h card-game/Deck.cpp card-game/Deck.h card-game/DeckBuilder.cpp card-game/DeckBuilder.h card-game/Board.cpp card-game/Board.h lib/logger.h examples/Uno.cpp examples/Uno.h examples/UnoCards.h examples/HuitAmericain.cpp examples/HuitAmericain.h)

add_subdirectory(lib/Google_tests)