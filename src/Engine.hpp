#pragma once

#include "Board.hpp"

#define MAX_DEPTH 10

enum Values
{
	has_won = 100,
};

Player best_score(Player player, Player a, Player b) {
	if (a == Invalid)
		return b;

	if (b == Invalid)
		return a;

	if (a == player || b == player)
		return player;

	if (a == Neutral || b == Neutral)
		return Neutral;

	return opponent(player);
}


struct Move
{
	Player eval;
	int move;

	Move(Player eval, int move) {
		this->eval = eval;
		this->move = move;
	}
};

Move minimax(Board board, Player player, int depth = MAX_DEPTH) {


	if (board.has_won(player))
		return { player, -1 };

	if (board.is_empty())
		return { Neutral, -1};

	if (depth == 0)
		return { Neutral, -1 };


	auto moves = board.available_moves();

	Player score = Invalid;
	int best_move = -1;

	for (auto& move : moves)
	{
		Player move_score = minimax(board.copy_set(move, player), opponent(player), depth - 1).eval;

		int old_score = score;
		score = best_score(player, move_score, score);
		if (score != old_score)
			best_move = move;
	}

	return Move{score, best_move};

}