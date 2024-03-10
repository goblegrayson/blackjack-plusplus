#pragma once

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <unordered_map>
#include <random>
#include <matplot/matplot.h>

namespace  engine {
	// Card
	enum Suit {
		Spades,
		Hearts,
		Clubs,
		Diamonds
	};

	const std::unordered_map<int, std::string> suitMap = {
		{0, "Spades"},
		{1, "Hearts"},
		{2, "Clubs"},
		{3, "Diamonds"}
	};

	const std::unordered_map<int, std::string> rankNameMap = {
		{1, "Ace"},
		{2, "2"},
		{3, "3"},
		{4, "4"},
		{5, "5"},
		{6, "6"},
		{7, "7"},
		{8, "8"},
		{9, "9"},
		{10, "10"},
		{11, "Jack"},
		{12, "Queen"},
		{13, "King"}
	};

	const std::unordered_map<int, std::string> actionMap = {
		{0, "Stand"},
		{1, "Hit"},
		{2, "Split"},
		{3, "Double"}
	};

	// logging structure with fields which corresponds to members in the Player class
	struct logs {
		std::vector<float> bankroll;
		std::vector<float> bet;
	};

	class Card {
		public:
			Suit suit;
			int rank;

			Card(Suit suit, int rank);
			void print();
			std::string toStr();
	};

	// Shoe
	class Shoe {
		private:
			int i_nextCard = 0;

		public:
			const int n_shuffles = 10;
			const int n_decks;
			const int n_initial;
			std::vector<Card> cards;

			Shoe(int n_decks);
			void print();
			void plot();
			int numCardsRemaining();
			std::vector<Card> buildDeck();
			int chooseRandomInt();
			void shuffle(uint64_t seed = 0);
			Card draw();
	};

	// Hand
	class Hand {
		private:

		public:
			float bet = 0;
			std::vector<Card> cards;
			bool isDoubled = false;
			bool isDealer = false;

			Hand(bool isDealer);
			Hand() = default;
			void addCard(engine::Card Card);
			void print();
			int score();
			bool isBlackjack();
			std::vector<int> actionsAvailable();
	};
	// nice function to print actions in a pretty way
	void prettyPrintActions(std::vector<int> actions);

	// Game state data for betting strategies
	struct roundState {
		int i_player;
		int i_hand;
		Hand playerHand;
		Hand dealerHand;
		float bankroll;
		float bet;
		std::vector<int> availableActions;
	};
	typedef float (*BettingFuncPtr)(roundState roundState, logs logs);
	typedef int (*PlayingFuncPtr)(roundState roundState, logs logs);


	// Player
	class Player {
		private:
			int playerNumber_;
			bool isDealer;

		public:
			std::vector<Hand> hands;
			BettingFuncPtr bettingFunc;
			PlayingFuncPtr playingFunc;
			float bankroll;
			logs logs;

			Player(int playerNumber, float bankroll, BettingFuncPtr bettingFunc, PlayingFuncPtr playingFunc);
			void print();
			
			int playerNumber();
			void addHand();
			void makeBet(int iHand, float amount);
			void initLogs(int n_rounds);
			void logRound();	
	};

	// Table
	class Table {
	private:
		int i_round = 0;
		int n_decks;
		int reshuffleAt = 52;
		void initLogs();
		void logRound();

	public:
		std::vector<Player> players;
		Shoe shoe;
		int n_rounds = 100;

		Table(std::vector<Player> players, int n_decks);
		void play();
	};

	// Round
	class Round {
	private:
		bool isStarted = false;
		bool isComplete = false;
		int i_player;
		int i_hand;
		Table& table;

	public:
		Round(Table& table);
		void play();

	};

	// Betting Strategies
	float betCLI(roundState roundState, logs logs);
	float always10(roundState roundState, logs logs);
	float simpleMartingale(roundState roundState, logs logs);
	float kellyCriterion(roundState roundState, logs logs);

	// Playing Strategies
	int playCLI(roundState roundState, logs logs);
	int standardDealer(roundState roundState, logs logs);
	int alwaysHit(roundState roundState, logs logs);
	int alwaysDouble(roundState roundState, logs logs);
	int alwaysStand(roundState roundState, logs logs);
	int splitOrStand(roundState roundState, logs logs);
};