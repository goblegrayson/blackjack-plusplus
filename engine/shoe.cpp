// shoe.cpp : Defines the class for a shoe of decks.
//

#include "engine.hpp"

using namespace std;

engine::Shoe::Shoe(int n_decks) : n_decks(n_decks), n_initial(52 * n_decks){
	// Initialize the cards
	vector<Card> deck = buildDeck();
	for (int i_deck = 0; i_deck < n_decks; i_deck++) {
		cards.insert(end(cards), begin(deck), end(deck));
	};
};

void engine::Shoe::print() {
	cout << "Shoe: " << getNumCardsRemaining() << " of " << n_initial << " Remaining\n";
};

int engine::Shoe::getNumCardsRemaining() {
	return size(cards);
};

vector<engine::Card> engine::Shoe::buildDeck() {
	// Init the deck
	vector<engine::Card> Deck;
	// Loop suits
	for (int iSuit = engine::Suit::Spades; iSuit <= engine::Suit::Diamonds; iSuit++) {
		engine::Suit suit = static_cast<engine::Suit>(iSuit);
		// Loop ranks
		for (int rank = 1; rank <= 13; rank++) {
			// Add the card
			Deck.push_back(engine::Card(suit, rank));
		};
	}

	return Deck;
};

void engine::Shoe::shuffle(uint64_t seed) {
	if (seed == 0) {
		cout << "Shuffling without Seed!" << "\n";
	}
	else {
		cout << "Shuffling with Seed!" << "\n";
	}
	// Implement a Thorp Shuffle [Ref. 1]
};
