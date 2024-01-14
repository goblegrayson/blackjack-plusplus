// round.cpp : Defines the class for Blackjack round.
//

#include "engine.hpp"

engine::Round::Round(std::vector<Player> players, engine::Shoe shoe): players(players), shoe(shoe) {};

bool engine::Round::isStarted() {
	return true;
};

bool engine::Round::isComplete() {
	return true;
};

void engine::Round::play() {
	// Bet and deal the players first card
	for (i_player = 1; i_player < size(players); i_player++) {
		players[i_player].addHand();
		engine::roundState roundState;
		roundState.i_player = i_player;
		roundState.i_hand = 1;
		roundState.bankroll = players[i_player].bankroll;
		players[i_player].makeBet(0, players[i_player].bettingFunc(roundState));
		players[i_player].hands[0].addCard(shoe.draw());
	};
	// Dealer's down card
	players[0].addHand();
	players[0].hands[0].addCard(shoe.draw());
	// Players second card
	for (int i_player = 1; i_player < size(players); i_player++) {
		players[i_player].hands[0].addCard(shoe.draw());
	};
	// Dealer's up card
	players[0].hands[0].addCard(shoe.draw());
	// Check dealer blackjack
	if (!players[0].hands[0].isBlackjack()) {
		// Main player loop
		isStarted_ = true;
		std::vector<int> playerOrder(players.size() - 1);
		std::iota(playerOrder.begin(), playerOrder.end(), 1);
		playerOrder.push_back(0);
		for (auto i_player : playerOrder) {
			// Main hand loop
			for (i_hand = 0; i_hand < size(players[i_player].hands); i_hand++) {
				while (players[i_player].hands[i_hand].actionsAvailable().size() > 0) {
					// Get the decided action
					engine::roundState roundState;
					roundState.i_player = i_player;
					roundState.i_hand = i_hand;
					roundState.playerHand = players[i_player].hands[i_hand];
					roundState.dealerHand = players[0].hands[0];
					roundState.bankroll = players[i_player].bankroll;
					roundState.bet = players[i_player].hands[i_hand].bet;
					roundState.availableActions = players[i_player].hands[i_hand].actionsAvailable();
					int action = players[i_player].playingFunc(roundState);
					// Now do it
					if (action == 0) {
						// Stand
						break;
					}
					else if (action == 1) {
						// Hit
						players[i_player].hands[i_hand].addCard(shoe.draw());
					}
					else if (action == 2) {
						// Split the hand
						players[i_player].addHand();
						players[i_player].hands.back().addCard(players[i_player].hands[i_hand].cards[1]);
						players[i_player].hands[i_hand].cards.pop_back();
						players[i_player].makeBet(players[i_player].hands.size() - 1, players[i_player].hands[i_hand].bet);
						// Deal them both another card
						players[i_player].hands[i_hand].addCard(shoe.draw());
						players[i_player].hands.back().addCard(shoe.draw());
					}
					else if (action == 3) {
						// Double
						players[i_player].makeBet(i_hand, players[i_player].hands[i_hand].bet);
						players[i_player].hands[i_hand].addCard(shoe.draw());
						players[i_player].hands[i_hand].isDoubled = true;
					}
				};
			};
		};
	}
	// Score and settle
	int dealerScore = players[0].hands[0].score();
	for (i_player = 1; i_player < size(players); i_player++) {
		for (i_hand = 0; i_hand < size(players[i_player].hands); i_hand++) {
			// Pay out
			if (players[i_player].hands[i_hand].isBlackjack()) {
				// Blackjack pays 3:2
				players[i_player].bankroll += float(2.5) * players[i_player].hands[i_hand].bet;
			}
			else if (players[i_player].hands[i_hand].score() > dealerScore) {
				players[i_player].bankroll += 2 * players[i_player].hands[i_hand].bet;
			}
			else if (players[i_player].hands[i_hand].score() == dealerScore) {
				players[i_player].bankroll += players[i_player].hands[i_hand].bet;
			};
			
		};
		// Turn in the cards - maybe put this into a discard pile in shoe at some point
		players[i_player].hands.clear();
	};
	// Dealer discard
	players[0].hands.clear();
};
