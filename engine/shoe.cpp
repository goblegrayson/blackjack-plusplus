// shoe.cpp : Defines the class for a shoe of decks.
//

#include "engine.hpp"

engine::Shoe::Shoe(int n_decks) : n_decks(n_decks), n_initial(52 * n_decks){
	// Initialize the cards
	std::vector<Card> deck = buildDeck();
	for (int i_deck = 0; i_deck < n_decks; i_deck++) {
		cards.insert(end(cards), begin(deck), end(deck));
	};
	// Initialize the uniform intiger distribution
	std::random_device rand_dev = std::random_device();
	std::mt19937 generator = std::mt19937(rand_dev());
};

void engine::Shoe::print() {
	std::cout << "Shoe: " << getNumCardsRemaining() << " of " << n_initial << " Remaining\n";
};

void engine::Shoe::plot() {
	std::vector<int> x = {};
	std::vector<int> y = {};
	for (int i = 0; i < cards.size(); i++) {
		x.push_back(i);
		y.push_back(cards[i].rank);
	}
	matplot::bar(x, y);
	matplot::show();
};

int engine::Shoe::getNumCardsRemaining() {
	return size(cards);
};

std::vector<engine::Card> engine::Shoe::buildDeck() {
	// Init the deck
	std::vector<engine::Card> Deck;
	// Loop suits
	for (int iSuit = engine::Suit::Spades; iSuit <= engine::Suit::Diamonds; iSuit++) {
		engine::Suit suit = static_cast<engine::Suit>(iSuit);
		// Loop ranks
		for (int rank = 1; rank <= 13; rank++) {
			// Add the card
			Deck.push_back(engine::Card(suit, rank));
		}
	}
	return Deck;
};

void engine::Shoe::shuffle(uint64_t seed) {
	// Implement a Thorp Shuffle [Ref. 1]
	for (int i_round = 1; i_round <= n_shuffles; i_round++) {
		// Cut somewhere in the middle third of the deck
		int i_cut = cards.size() / 2;
		std::vector<engine::Card> leftDeck = {};
		std::vector<engine::Card> rightDeck = {};
		for (int i_card = 0; i_card < size(cards); i_card++) {
			if (i_card < i_cut) {
				leftDeck.push_back(cards[i_card]);
			}
			else {
				rightDeck.push_back(cards[i_card]);
			}
		}
		// Rifle cards with 0.5 probability of left before right and vice versa
		std::vector<engine::Card> shuffledDeck = {};
		for (int i_card = 0; i_card < leftDeck.size(); i_card++) {
			// Choose number
			int randResult = chooseRandomInt();
			if (randResult > 0) {
				shuffledDeck.push_back(leftDeck[i_card]);
				shuffledDeck.push_back(rightDeck[i_card]);
			}
			else {
				shuffledDeck.push_back(rightDeck[i_card]);
				shuffledDeck.push_back(leftDeck[i_card]);
			}
			
		}
		// Store the temp deck
		cards = shuffledDeck;
	};
};

int engine::Shoe::chooseRandomInt() {
	static std::random_device rand_dev;
	static std::mt19937 generator(rand_dev());
	std::uniform_int_distribution<int> uid(0, 1);
	return uid(generator);
};
