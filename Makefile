
card-game: main.o Card.o Deck.o Player.o DeckBuilder.o Board.o GameTemplate.o Bataille.o Uno.o
	g++ main.o Card.o Deck.o Player.o DeckBuilder.o Board.o GameTemplate.o Bataille.o Uno.o HuitAmericain.o Scopa.o Briscola.o -o card-game

main.o: main.cpp
	g++ -c main.cpp

Card.o: card-game/Card.cpp card-game/Card.h
	g++ -c card-game/Card.cpp

Deck.o: card-game/Deck.cpp card-game/Deck.h
	g++ -c card-game/Deck.cpp
		
Player.o: card-game/Player.cpp card-game/Player.h
	g++ -c card-game/Player.cpp
	
DeckBuilder.o: card-game/DeckBuilder.cpp card-game/DeckBuilder.h
	g++ -c card-game/DeckBuilder.cpp

Board.o: card-game/Board.cpp card-game/Board.h
	g++ -c card-game/Board.cpp

GameTemplate.o: examples/GameTemplate.cpp examples/GameTemplate.h
	g++ -c examples/GameTemplate.cpp

Bataille.o: examples/Bataille.cpp examples/Bataille.h
	g++ -c examples/Bataille.cpp

Uno.o: examples/Uno.cpp examples/Uno.h
	g++ -c examples/Uno.cpp

HuitAmericain.o: examples/HuitAmericain.cpp examples/HuitAmericain.h
	g++ -c examples/HuitAmericain.cpp

Briscola.o: examples/Briscola.cpp examples/Briscola.h
	g++ -c examples/Briscola.cpp

Scopa.o: examples/Scopa.cpp examples/Scopa.h
	g++ -c examples/Scopa.cpp

clean: 
	rm *.o card-game.exe

