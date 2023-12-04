#pragma once

#include <vector>

enum Player {
	Neutral = 0,
	Player1 = 1,
	Player2 = 2,
	Invalid = 3,
};

Player opponent(Player p) {
	return p == Player1 ? Player2 : Player1;
}

struct Diagonal {
	int a, b, c;
};


static const Diagonal diagonals[8]{
		Diagonal{0, 4, 8},
		Diagonal{2, 4, 6},

		Diagonal{0, 3, 6},
		Diagonal{1, 4, 7},
		Diagonal{2, 5, 8},

		Diagonal{0, 1, 2},
		Diagonal{3, 4, 5},
		Diagonal{6, 7, 8},

};

struct Board {

	Player board[9];

	Player& operator()(int x, int y) {
		return board[y * 3 + x];
	}

	Player& operator[](int i) {
		return board[i];
	}

	Board copy_set(int i, Player player) {
		Board b = *this;
		b.board[i] = player;
		return b;
	}

	bool has_won(Player player) {

		for (auto& d : diagonals)
			if (board[d.a] == player && board[d.b] == player && board[d.c] == player)
				return true;

		return false;
	}

	std::vector<size_t> available_moves() {
		std::vector<size_t> v;
		for (size_t i = 0; i < 9; i++)
		{
			if (board[i] == Neutral)
				v.push_back(i);
		}
		return v;
	}
	

	bool is_empty() {
		for (size_t i = 0; i < 9; i++)
			if (board[i] == Neutral)
				return false;
		return true;
	}
};