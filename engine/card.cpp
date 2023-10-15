// card.cpp : Defines the classes for Blackjack cards.
//

#include "engine.hpp"

engine::Card::Card(engine::Suit suit, int rank): suit(suit), rank(rank) {};

void engine::Card::print() {
	std::cout << engine::rankMap.find(rank)->second << " of " << engine::suitMap.find(suit)->second << "\n";
	/*cout << rank << " of " << suit << "\n";*/
};


