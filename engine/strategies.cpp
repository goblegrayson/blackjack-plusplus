// strategies.cpp : Defines betting strategies for autonomous players.
//

#include "engine.hpp"

// Betting Strategies
float engine::always10(roundState roundState) {
	return float(10);
};

float engine::betCLI(roundState roundState) {
	// Print the bankroll
	std::string amount;
	std::cout << "Player " << roundState.i_player << ": $" << roundState.bankroll << std::endl;
	std::cout << "What is your bet?" << std::endl;
	std::cin >> amount;
	std::cout << "----------------------------------------" << std::endl;
	return std::stof(amount);
};

// Playing Strategies
int engine::alwaysHit(roundState roundState) {
	return 1;
};

int engine::alwaysDouble(roundState roundState) {
	return 3;
};

int engine::splitOrStand(roundState roundState) {
	bool isSplittable = roundState.playerHand.cards.size() == 2 && roundState.playerHand.cards[0].rank == roundState.playerHand.cards[1].rank;
	if (isSplittable) {
		return 2;
	};
	return 0;
};

int engine::playCLI(roundState roundState) {
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

