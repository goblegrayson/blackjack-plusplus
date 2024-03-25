// table.cpp : Defines the class for Blackjack tables.
//

#include "engine.hpp"

engine::Table::Table(std::vector<Player> players, int n_decks) : players(players), n_decks(n_decks), shoe(engine::Shoe::Shoe(n_decks)) {};

void engine::Table::play() {
	// Round loop
	initLogs();
	while (i_round < n_rounds) {
		// Play the round
		i_round++;
		engine::Round Round(*this);
		Round.play();
		//// Post round logging
		//logRound();
		// Post-round cleanup
		if (shoe.numCardsRemaining() <= reshuffleAt) {
			shoe.shuffle();
		}
	};
	// Post-game cleanup
};

void engine::Table::initLogs() {
	for (int i_player = 0; i_player < size(players); i_player++) {
		players[i_player].initLogs(n_rounds);
	};
};

void engine::Table::logRound() {
	for (int i_player = 0; i_player < size(players); i_player++) {
		players[i_player].logRound();
	};
};