
#include "rand.hpp"

const char* key = "continue";
const char* empty_string = "NULL";

class Game {

public:
	int prob;

	Board board{};
	Player player = Player1;

	Game(int prob) : prob(prob) {}


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

	int has_finished() {
		return board.is_empty() || board.has_won(Player1) || board.has_won(Player2);
	}

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

	int player_move(int move) {
		if (player == Player1 || board[move] != Neutral)
			return -10;

		board[move] = Player2;
		player = Player1;
		return move;
	}

	const char* get_key() {
		if (board.has_won(Player2))
			return key;

		return empty_string;
	}


private:

	bool get_random() {
		std::uniform_int_distribution<std::mt19937::result_type> dist(0, prob);
		return dist(rng) == prob;
	}
};

