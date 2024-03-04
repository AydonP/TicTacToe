#pragma once

enum Player {
	Neutral = 0,
	Player1 = 1,
	Player2 = 2,
	Invalid = 3,
};

Player opponent(Player p) {
	return p == Player1 ? Player2 : Player1;
}

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