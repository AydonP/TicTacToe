#pragma once

#include "Board.hpp"
#include "rand.hpp"


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


bool minimax_get_random() {
	static std::uniform_int_distribution<std::mt19937::result_type> dist(0, 1);
	return dist(rng);
}

Move minimax(Board board, Player player) {


	if (board.has_won(player))
		return { player, -1 };

	if (board.is_empty())
		return { Neutral, -1};



	auto moves = board.available_moves();

	Player score = Invalid;
	int best_move = -1;

	for (auto& move : moves)
	{
		Player move_score = minimax(board.copy_set(move, player), opponent(player)).eval;

		if (move_score == score) {
			best_move = minimax_get_random() ? move : best_move;
		}

		int old_score = score;

		score = best_score(player, move_score, score);

		if (score != old_score)
			best_move = move;

	}

	return Move{score, best_move};

}