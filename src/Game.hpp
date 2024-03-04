
#include <random>
#include <vector>

#include "Board.hpp"

const std::string empty_string = "";

struct Move
{
	Player eval;
	int move;

	Move(Player eval, int move) {
		this->eval = eval;
		this->move = move;
	}
};

class Game {
public:

	Board board{};
	Player player = Player1;

	Game(unsigned short prob, std::string key) : prob(prob), key(key) {}


	Player reset() {
		Player result;
		if (board.has_won(Player1))
			result = Player1;
		else if (board.has_won(Player2))
			result = Player2;
		else
			result = Neutral;

		if (this->prob > 0)
			--this->prob;

		this->board = Board{};
		this->player = Player1;
		this->dist = std::uniform_int_distribution<std::mt19937::result_type>{ 0, prob };
		return result;
	}

	bool has_finished() {
		return board.is_empty() || board.has_won(Player1) || board.has_won(Player2);
	}

	int ai_move() {
		if (player == Player2) {
			return -1;
		}

		if (board.count() == 9 || dist(rng) == 0) {
			auto move = board.available().begin();
			move += std::uniform_int_distribution<std::mt19937::result_type>(0, board.count() - 1)(rng);
			board.set(*move, Player1);
			player = Player2;

			if (board.count() == 8)
				return *move;
			else
				return *move + 100;
		}
		else
		{
			Move move = minimax(board, Player1);
			board.set(move.move, Player1);
			player = Player2;
			return move.move;
		}
	}

	int player_move(int move) {
		if (player == Player1 || board[move] != Neutral)
			return -10;

		board.set(move, Player2);
		player = Player1;
		return move;
	}

	const std::string& get_key() {
		if (board.has_won(Player2))
			return key;

		return empty_string;
	}


private:
	std::string key;
	unsigned short prob;

	std::random_device dev{};
	std::mt19937 rng{ dev() };
	std::uniform_int_distribution<std::mt19937::result_type> dist{ 0, prob };


	Move minimax(Board& board, Player player) {

		if (board.has_won(player))
			return { player, -1 };

		if (board.is_empty())
			return { Neutral, -1 };


		Player score = Invalid;
		std::vector<int> best_moves;

		for (auto move : board.available())
		{
			board.set(move, player);
			Player move_score = minimax(board, opponent(player)).eval;
			board.set(move, Neutral);

			if (move_score == score) {
				best_moves.push_back(move);
			}
			else {

				int old_score = score;
				score = best_score(player, move_score, score);

				if (score != old_score) {
					best_moves.clear();
					best_moves.push_back(move);
				}
			}
		}

		return Move{ 
			score, 
			best_moves[ std::uniform_int_distribution<std::mt19937::result_type>{ 0, best_moves.size() - 1 }(rng) ]
		};

	}

};

