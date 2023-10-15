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
	const std::unordered_map<int, std::string> rankMap = {
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
	};

	// Shoe
	class Shoe {
		private:

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
			
	};
};