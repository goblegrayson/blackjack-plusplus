#pragma once

#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

namespace  engine {
	// Card
	enum Suit {
		Spades,
		Hearts,
		Clubs,
		Diamonds
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
			const int n_decks;
			const int n_initial;
			vector<Card> cards;
			

			Shoe(int n_decks);
			void print();
			int getNumCardsRemaining();
			vector<Card> buildDeck();
			void shuffle(uint64_t seed = 0);
			
	};
};