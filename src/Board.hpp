#pragma once

#include <cassert>
#include "Player.hpp"
#include <cstddef>

struct Diagonal {
	int a, b, c;
};

const Diagonal diagonals[8]{
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
	
	const Player& operator[](uint8_t i) const {
		assert(i < 9);
		return board[i];
	}

	const Player& operator()(uint8_t x, uint8_t y) const {
		return board[y * 3 + x];
	}

	void set(uint8_t cell, Player player) {
		if (this->board[cell] == Neutral)
			--this->available_cells;
		if (player == Neutral)
			++this->available_cells;

		this->board[cell] = player;
	}

	bool has_won(Player player) {

		for (auto& d : diagonals)
			if (board[d.a] == player && board[d.b] == player && board[d.c] == player)
				return true;

		return false;
	}

	bool is_empty() {
		return available_cells == 0;
	}

	struct Cells {
		struct Iterator {

			size_t operator*() {
				assert(i < 9);
				return i;
			}

			Iterator& operator++() {
				assert(i < 9);
				++i;

				while (i < 9 && board[i] != Neutral)
					++i;

				return *this;
			}

			Iterator& operator +=(size_t count) {
				for (size_t i = 0; i < count; i++)
					++*this;
				return *this;
			}

			bool operator ==(const Iterator& i) const {
				assert(&this->board == &i.board);
				return this->i != i.i;
			}

			bool operator !=(const Iterator& i) const {
				assert(&this->board == &i.board);
				return this->i != i.i;
			}

		private:
			Iterator(const Board& board, size_t i = 0) : board(board), i(i) {
				while (this->i < 9 && board[this->i] != Neutral)
					++this->i;
			}

			friend Cells;
			const Board& board;
			size_t i;
		};

		Iterator begin() {
			return Iterator{ board };
		}

		Iterator end() {
			return Iterator{ board, 9 };
		}

	private:
		const Board& board;
		Cells(const Board& board) : board(board) {}
		friend Board;
	};

	Cells available() {
		return Cells{*this};
	}

	size_t count() {
		return this->available_cells;
	}

private:
	Player board[9];
	size_t available_cells = 9;
};