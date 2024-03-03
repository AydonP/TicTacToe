
#include "Engine.hpp"
#include "Game.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#else
#include <iostream>
#endif


using namespace std;


#ifndef __EMSCRIPTEN__ 
void print_board(Board board) {
	for (size_t i = 0; i < 9; i++)
	{
		std::cout << board[i];
		if ((i % 3) == 2)
			std::cout << "\n";
	}
}

int main()
{
	Game game{12};
	while (1)
	{
		while (!game.has_finished())
		{
			game.ai_move();
			print_board(game.board);

			if (game.has_finished())
				continue;

			std::cout << "> ";
			int move;
			std::cin >> move;
			game.player_move(move);
		}
		game.reset();
		std::cout << "--------\n";
	}
}

#else

Game game{8};

extern "C" {
	EMSCRIPTEN_KEEPALIVE
	int reset() {
		return game.reset();
	}

	EMSCRIPTEN_KEEPALIVE
	int has_finished() {
		return game.has_finished();
	}

	EMSCRIPTEN_KEEPALIVE
	int ai_move() {
		return game.ai_move();
	}

	EMSCRIPTEN_KEEPALIVE
	int player_move(int move) {
		return game.player_move(move);

	}

	EMSCRIPTEN_KEEPALIVE
	const char* get_key() {
		return game.get_key();
	}
}

#endif

