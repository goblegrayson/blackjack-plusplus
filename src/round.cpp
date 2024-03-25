// round.cpp : Defines the class for Blackjack round.
//

#include "engine.hpp"

engine::Round::Round(engine::Table& table): table(table) {};

void engine::Round::play() {
	// Bet and deal the players first card
	for (i_player = 1; i_player < size(table.players); i_player++) {
		table.players[i_player].addHand();
		engine::roundState roundState;
		roundState.i_player = i_player;
		roundState.i_hand = 1;
		roundState.bankroll = table.players[i_player].bankroll;
		table.players[i_player].makeBet(0, table.players[i_player].bettingFunc(roundState, table.players[i_player].logs));
		table.players[i_player].hands[0].addCard(table.shoe.draw());
	};
	// Dealer's down card
	table.players[0].addHand();
	table.players[0].hands[0].addCard(table.shoe.draw());
	// Players second card
	for (int i_player = 1; i_player < size(table.players); i_player++) {
		table.players[i_player].hands[0].addCard(table.shoe.draw());
	};
	// Dealer's up card
	table.players[0].hands[0].addCard(table.shoe.draw());
	// Check dealer blackjack
	if (!table.players[0].hands[0].isBlackjack()) {
		// Main player loop
		isStarted = true;
		std::vector<int> playerOrder(table.players.size() - 1);
		std::iota(playerOrder.begin(), playerOrder.end(), 1);
		playerOrder.push_back(0);
		for (auto i_player : playerOrder) {
			// Main hand loop
			for (i_hand = 0; i_hand < size(table.players[i_player].hands); i_hand++) {
				while (table.players[i_player].hands[i_hand].actionsAvailable().size() > 0) {
					// Get the decided action
					engine::roundState roundState;
					roundState.i_player = i_player;
					roundState.i_hand = i_hand;
					roundState.playerHand = table.players[i_player].hands[i_hand];
					roundState.dealerHand = table.players[0].hands[0];
					roundState.bankroll = table.players[i_player].bankroll;
					roundState.bet = table.players[i_player].hands[i_hand].bet;
					roundState.availableActions = table.players[i_player].hands[i_hand].actionsAvailable();
					int action = table.players[i_player].playingFunc(roundState, table.players[i_player].logs);
					// Now do it
					if (action == 0) {
						// Stand
						break;
					}
					else if (action == 1) {
						// Hit
						table.players[i_player].hands[i_hand].addCard(table.shoe.draw());
					}
					else if (action == 2) {
						// Split the hand
						table.players[i_player].addHand();
						table.players[i_player].hands.back().addCard(table.players[i_player].hands[i_hand].cards[1]);
						table.players[i_player].hands[i_hand].cards.pop_back();
						table.players[i_player].makeBet(table.players[i_player].hands.size() - 1, table.players[i_player].hands[i_hand].bet);
						// Deal them both another card
						table.players[i_player].hands[i_hand].addCard(table.shoe.draw());
						table.players[i_player].hands.back().addCard(table.shoe.draw());
					}
					else if (action == 3) {
						// Double
						table.players[i_player].makeBet(i_hand, table.players[i_player].hands[i_hand].bet);
						table.players[i_player].hands[i_hand].addCard(table.shoe.draw());
						table.players[i_player].hands[i_hand].isDoubled = true;
					}
				};
			};
		};
	}
	// Score and settle
	int dealerScore = table.players[0].hands[0].score();
	for (i_player = 1; i_player < size(table.players); i_player++) {
		for (i_hand = 0; i_hand < size(table.players[i_player].hands); i_hand++) {
			// Pay out
			int handScore = table.players[i_player].hands[i_hand].score();
			if (table.players[i_player].hands[i_hand].isBlackjack() && !table.players[0].hands[0].isBlackjack()) {
				// Blackjack pays 3:2
				table.players[i_player].bankroll += float(2.5) * table.players[i_player].hands[i_hand].bet;
			}
			else if (handScore > dealerScore) {
				table.players[i_player].bankroll += 2 * table.players[i_player].hands[i_hand].bet;
			}
			else if (handScore == dealerScore) {
				table.players[i_player].bankroll += table.players[i_player].hands[i_hand].bet;
			};
		};
		// Player log
		table.players[i_player].logRound();
		// Turn in the cards - maybe put this into a discard pile in shoe at some point
		table.players[i_player].hands.clear();
	};
	// Dealer log
	table.players[0].logRound();
	// Dealer discard
	table.players[0].hands.clear();
	// Mark complete
	isComplete = true;
};
