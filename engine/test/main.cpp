// main.cpp : Run test suite.
//
#define CATCH_AMALGAMATED_CUSTOM_MAIN 1
#define CATCH_CONFIG_RUNNER
#include "main.hpp"

int main(int argc, char* const argv[]) {
    int result = Catch::Session().run(argc, argv);

    while (true);
    return result;
};

// Test Cards
TEST_CASE("Cards construct properly", "[Card]") {
    engine::Card Card(engine::Suit::Spades, 13);
    Card.print();
    REQUIRE(Card.rank == 13);
    REQUIRE(Card.suit == engine::Suit::Spades);
};

// Test Shoe
TEST_CASE("Single deck builds properly", "[Shoe]") {
    engine::Shoe Shoe(1);
    Shoe.print();
    // Check card array dimensions are good
    REQUIRE(Shoe.n_decks == 1);
    REQUIRE(Shoe.getNumCardsRemaining() == Shoe.n_decks * 52);
    // Check the cards are in the right place
    int iCard = 0;
    for (int iSuit = engine::Suit::Spades; iSuit <= engine::Suit::Diamonds; iSuit++) {
        engine::Suit suit = static_cast<engine::Suit>(iSuit);
        // Loop ranks
        for (int rank = 1; rank <= 13; rank++) {
            // Check the Card
            REQUIRE(Shoe.cards[iCard].suit == suit);
            REQUIRE(Shoe.cards[iCard].rank == rank);
            iCard++;
        };
    }
};

TEST_CASE("Shoe constructs properly", "[Shoe]") {
    engine::Shoe Shoe(2);
    Shoe.print();
    // Check that a shoe of multiple decks has proper dimensions
    REQUIRE(Shoe.n_decks == 2);
    REQUIRE(Shoe.getNumCardsRemaining() == Shoe.n_decks * 52);
    // Check the shoe shuffles as expected

};

TEST_CASE("Shoe shuffles properly", "[Shoe]") {
    engine::Shoe Shoe(2);
    // Check the shoe shuffles as expected
    uint64_t seed = Catch::rngSeed();
    Shoe.shuffle(seed);
    // Plot the values vs position to visually check the distribution  
    Shoe.plot();
};


