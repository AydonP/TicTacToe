#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#else
#include <iostream>
#define EMSCRIPTEN_KEEPALIVE
#endif

#ifndef TICTACTOE_WON_CODE
#define TICTACTOE_WON_CODE alert("You won!!");
#endif

#define STRING_(str) #str
#define STRING(str) STRING_(str)

#include "Game.hpp"

Game game{12, STRING(TICTACTOE_WON_CODE) };

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
		return game.get_key().c_str();
	}
}

#ifndef __EMSCRIPTEN__
int main()
{
	for (;;)
	{
		while (!game.has_finished())
		{
			game.ai_move();

			for (size_t i = 0; i < 9; i++)
			{
				std::cout << game.board[i];
				if ((i % 3) == 2)
					std::cout << "\n";
			}

			if (game.has_finished())
				continue;

			std::cout << "> ";
			char move;
			std::cin >> move;

			if (move == 'q')
				return 0;

			game.player_move(move - '0');
		}
		game.reset();
		std::cout << "--------\n";
	}
}
#endif