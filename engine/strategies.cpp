// strategies.cpp : Defines betting strategies for autonomous players.
//

#include "engine.hpp"

// Betting Strategies
float engine::always10(roundState roundState, logs logs) {
	return float(10);
};

float engine::betCLI(roundState roundState, logs logs) {
	// Print the bankroll
	std::string amount;
	std::cout << "Player " << roundState.i_player << ": $" << roundState.bankroll << std::endl;
	std::cout << "What is your bet?" << std::endl;
	std::cin >> amount;
	std::cout << "----------------------------------------" << std::endl;
	return std::stof(amount);
};

float engine::simpleMartingale(roundState roundState, logs logs) {
	float baseBet = 10;
	if (size(logs.bankroll) <= 1) {
		// First round return the base bet
		return baseBet;
	}
	else {
		float deltaBankroll = logs.bankroll[logs.bankroll.size() - 1] - logs.bankroll[logs.bankroll.size() - 2];
		if (deltaBankroll == 0) {
			// Last time we pushed. Return the same bet
			return logs.bet[logs.bet.size() - 1];
		}
		else if (deltaBankroll > 0) {
			// Last time we won. Go back to the base bet
			return baseBet;
		}
		else if (deltaBankroll < 0) {
			// Last time we lost. Double the bet
			return logs.bet[logs.bet.size() - 1] * 2;
		};
	};
};

float engine::kellyCriterion(roundState roundState, logs logs) {
	return 1;
};

// Playing Strategies
int engine::standardDealer(roundState roundState, logs logs) {
	if (roundState.dealerHand.score() <= 16) {
		return 1;
	}
	else {
		return 0;
	};
};

int engine::alwaysStand(roundState roundState, logs logs) {
	return 0;
};

int engine::alwaysHit(roundState roundState, logs logs) {
	return 1;
};

int engine::alwaysDouble(roundState roundState, logs logs) {
	return 3;
};

int engine::splitOrStand(roundState roundState, logs logs) {
	bool isSplittable = roundState.playerHand.cards.size() == 2 && roundState.playerHand.cards[0].rank == roundState.playerHand.cards[1].rank;
	if (isSplittable) {
		return 2;
	};
	return 0;
};

int engine::playCLI(roundState roundState, logs logs) {
	// Print the dealer's hand
	roundState.dealerHand.print();
	// Print the player's hand and bet
	roundState.playerHand.print();
	// Print the available options
	prettyPrintActions(roundState.availableActions);
	// Query for action
	std::string action;
	std::cout << "What is your play?" << std::endl;
	std::cin >> action;
	std::cout << "----------------------------------------" << std::endl;
	return std::stoi(action);
};

