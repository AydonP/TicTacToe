﻿
#include "Engine.hpp"
#include "CTicTacToe.h"
#include <emscripten.h>
#include <random>

using namespace std;


static Board board{};
static Player player = Player1;

const char* key = "winterkey3";
const char* empty_string = "NULL";

int main()
{

}

static int prob = 8;

static std::random_device dev;
static std::mt19937 rng(dev());

bool get_random() {
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, prob);

	return dist(rng) == prob;
}

extern "C" {


	EMSCRIPTEN_KEEPALIVE
	int reset() {
		int result;
		if (board.has_won(Player1))
			result = 1;
		else if (board.has_won(Player2))
			result = 2;
		else
			result = 0;

		if (prob != 0)
			prob -= 1;

		board = Board();
		player = Player1;
		return result;
	}

	EMSCRIPTEN_KEEPALIVE
		int has_finished() {
		return board.is_empty() || board.has_won(Player1) || board.has_won(Player2);
	}

	EMSCRIPTEN_KEEPALIVE
	int ai_move() {
		if (player == Player2) {
			return -1;
		}

		if (get_random()) {
			auto moves = board.available_moves();
			auto move = moves[std::uniform_int_distribution<std::mt19937::result_type>(0, moves.size() - 1)(rng)];
			board[move] = Player1;
			player = Player2;
			return move + 100;
		}

		Move move = minimax(board, Player1);
		board[move.move] = Player1;



		player = Player2;
		return move.move;
	}

	EMSCRIPTEN_KEEPALIVE
	int player_move(int move) {

		if (player == Player1 || board[move] !=Neutral)
			return -10;

		board[move] = Player2;
		player = Player1;
		return move;
	}

	EMSCRIPTEN_KEEPALIVE
	const char* get_key() {
		if (board.has_won(Player2))
			return key;

		return empty_string;
	}

}