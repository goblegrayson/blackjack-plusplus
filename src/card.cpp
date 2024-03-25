// card.cpp : Defines the classes for Blackjack cards.
//

#include "engine.hpp"

engine::Card::Card(engine::Suit suit, int rank): suit(suit), rank(rank) {};

void engine::Card::print() {
	std::cout << engine::rankNameMap.find(rank)->second << " of " << engine::suitMap.find(suit)->second << std::endl;
	/*cout << rank << " of " << suit << "\n";*/
};

std::string engine::Card::toStr() {
	return engine::rankNameMap.find(rank)->second + " of " + engine::suitMap.find(suit)->second;
	/*cout << rank << " of " << suit << "\n";*/
};

