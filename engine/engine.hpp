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
			int getNumCardsRemaining();
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
	typedef float (*BettingFuncPtr)(roundState roundState);
	typedef int (*PlayingFuncPtr)(roundState roundState);


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

			Player(int playerNumber, float bankroll, BettingFuncPtr bettingFunc, PlayingFuncPtr playingFunc);
			void print();
			
			int playerNumber();
			void addHand();
			void makeBet(int iHand, float amount);
			
	};

	const std::unordered_map<int, std::string> actionMap = {
		{0, "Stand"},
		{1, "Hit"},
		{2, "Split"},
		{3, "Double"}
	};

	// Round
	class Round {
	private:
		bool isStarted_ = false;
		int i_player;
		int i_hand;

	public:
		Shoe shoe;
		std::vector<Player> players;

		Round(std::vector<Player> players, engine::Shoe shoe);
		bool isStarted();
		bool isComplete();
		void play();
	};

	// Table
	class Table {
	private:

	public:
		std::vector<Player> players;
	};

	// Betting Strategies
	float betCLI(roundState roundState);
	float always10(roundState roundState);

	// Playing Strategies
	int playCLI(roundState roundState);
	int alwaysHit(roundState roundState);
	int alwaysDouble(roundState roundState);
	int splitOrStand(roundState roundState);
};