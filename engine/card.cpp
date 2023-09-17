// card.cpp : Defines the classes for Blackjack cards.
//

#include "engine.hpp"

using namespace std;

engine::Card::Card(engine::Suit suit, int rank): suit(suit), rank(rank) {};

void engine::Card::print() {
	cout << rank << " of " << suit << "\n";
};


