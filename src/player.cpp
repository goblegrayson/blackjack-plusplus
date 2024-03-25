// player.cpp : Defines the class for Blackjack players.
//

#include "engine.hpp"

engine::Player::Player(int playerNumber, float bankroll, BettingFuncPtr bettingFunc, PlayingFuncPtr playingFunc): playerNumber_(playerNumber), bankroll(bankroll), bettingFunc(bettingFunc), playingFunc(playingFunc) {
	// Dealer is always player 0
	if (playerNumber == 0) {
		isDealer = true;
	}
	else {
		isDealer = false;
	};
	// Init the logs
	initLogs(1);
};

void engine::Player::print() {
	std::cout << "Player " << playerNumber_ << ": $" << bankroll << std::endl;
};

int engine::Player::playerNumber() {
	return playerNumber_;
};

void engine::Player::addHand() {
	engine::Hand newHand(isDealer);
	hands.push_back(newHand);
};

void engine::Player::makeBet(int iHand, float amount) {
	float amountLimited = std::min(amount, bankroll);
	if (iHand < hands.size()) {
		bankroll = bankroll - amountLimited;
		hands[iHand].bet += amountLimited;
	}
};

void engine::Player::initLogs(int n_rounds) {
	// Reserve the right number of rounds
	logs.bankroll.clear();
	logs.bankroll.reserve(n_rounds);
	logs.bankroll.push_back(bankroll);

	logs.bet.clear();
	logs.bet.reserve(n_rounds);
	logs.bet.push_back(0);
};

void engine::Player::logRound() {
	// Set the value for the round in the logs
	logs.bankroll.push_back(bankroll);
	logs.bet.push_back(hands[0].bet);
};