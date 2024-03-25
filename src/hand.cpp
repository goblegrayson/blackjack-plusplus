// hand.cpp : Defines the class for Blackjack hands.
//

#include "engine.hpp"

engine::Hand::Hand(bool isDealer): isDealer(isDealer) {};

void engine::Hand::addCard(engine::Card Card) {
	cards.push_back(Card);
};

void engine::Hand::print() {
	if (int(cards.size()) < 1) {
		return;
	};
	// Print the first card
	std::cout << cards[0].toStr();
	for (int i_card = 1; i_card < size(cards); i_card++) {
		std::cout << ", " << cards[i_card].toStr();
	};
	std::cout << " -> " << score() << std::endl;
};

int engine::Hand::score() {
	// First sort the ranks in descending order so if we bust, we bust faster
	// and so we can determine ace values at the end
	std::vector<int> sortedRanks;
	for (int i_card = 0; i_card < size(cards); i_card++) {
		sortedRanks.push_back(cards[i_card].rank);
	};
	std::sort(sortedRanks.begin(), sortedRanks.end(), std::greater<int>());
	// Now step through and sum each card, stepping out if we bust
	int score = 0;
	std::vector<int> faceRanks {11, 12, 13};
	for (int i_card = 0; i_card < size(sortedRanks); i_card++) {
		// Add the card score
		int thisRank = sortedRanks[i_card];
		if (std::find(faceRanks.begin(), faceRanks.end(), thisRank) != faceRanks.end()) {
			// Face cards
			score += 10;
		}
		else if (thisRank == 1) {
			// Aces
			if (score > 10 && !isDealer) {
				score += 1;
			}
			else {
				score += 11;
			};
		}
		else {
			// Number cards
			score += thisRank;
		};
		// Check the bust
		// Dealer busts to 0, player busts to -1 so that bust/bust is player loss
		if (score > 21) {
			if (isDealer) {
				score = 0;
			}
			else {
				score = -1;
			}
			break;
		};
	};
	return score;
};

bool engine::Hand::isBlackjack() {
	// Do we have two cards?
	if (size(cards) != 2) {
		return false;
	};
	// Is our score 21?
	if (score() != 21) {
		return false;
	};
	return true;
};

std::vector<int> engine::Hand::actionsAvailable() {
	std::vector<int> validActions;
	// Common things that end the turn
	bool turnOver = score() == 21 || score() < 1 || isDoubled;
	if (turnOver) {
		return validActions;
	};
	// If we get here, we can stand and hit
	validActions.push_back(0);
	validActions.push_back(1);
	// That's all the dealer can do
	if (isDealer) {
		return validActions;
	};
	// Check Split
	if (cards.size() == 2 && cards[0].rank == cards[1].rank) {
		validActions.push_back(2);
	};
	// Check Double - Double on any 2 cards - Double on split ok
	if (cards.size() == 2) {
		validActions.push_back(3);
	};
	return validActions;
};

void engine::prettyPrintActions(std::vector<int> actions) {
	for (auto action : actions) {
		std::cout << action << ": " << engine::actionMap.find(action)->second << std::endl;
	};
};
