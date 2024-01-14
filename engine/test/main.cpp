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
    //Shoe.plot();
};

TEST_CASE("Shoe draws properly", "[Shoe]") {
    engine::Shoe Shoe(2);
    // Shuffle
    uint64_t seed = Catch::rngSeed();
    Shoe.shuffle(seed);
    // Check the rank and suit of the first two cards
    int rank1 = Shoe.cards[0].rank;
    int rank2 = Shoe.cards[1].rank;
    engine::Suit suit1 = Shoe.cards[0].suit;
    engine::Suit suit2 = Shoe.cards[1].suit;
    // Draw two cards
    engine::Card card1 = Shoe.draw();
    engine::Card card2 = Shoe.draw();
    Shoe.print();
    // Check we get the cards we expect
    REQUIRE(card1.suit == suit1);
    REQUIRE(card1.rank == rank1);
    REQUIRE(card2.suit == suit2);
    REQUIRE(card2.rank == rank2);
};

// Test Player
TEST_CASE("Players construct properly", "[Player]") {
    float bankroll = 10000;
    engine::Player Player(1, bankroll, &engine::always10, &engine::alwaysHit);
    Player.print();
    REQUIRE(Player.bankroll == bankroll);
};

TEST_CASE("Players bet properly", "[Player]") {
    float bankroll = 10000;
    // Well sized bet
    float bet = 500;
    engine::Player Player1(1, bankroll, &engine::always10, &engine::alwaysHit);
    Player1.addHand();
    Player1.makeBet(0, bet);
    Player1.print();
    REQUIRE(Player1.bankroll == bankroll - bet);
    REQUIRE(Player1.hands[0].bet == bet);
    // Poorly sized bet
    bet = 20000;
    engine::Player Player2(2, bankroll, &engine::always10, &engine::alwaysHit);
    Player2.addHand();
    Player2.makeBet(0, bet);
    Player2.print();
    REQUIRE(Player2.bankroll == 0);
    REQUIRE(Player2.hands[0].bet == bankroll);
    // 2 hand bet
    bet = 500;
    engine::Player Player3(2, bankroll, &engine::always10, &engine::alwaysHit);
    Player3.addHand();
    Player3.addHand();
    Player3.makeBet(0, bet);
    Player3.makeBet(1, bet);
    Player3.print();
    REQUIRE(Player3.bankroll == bankroll - 2*bet);
    REQUIRE(Player3.hands[0].bet == bet);
    REQUIRE(Player3.hands[1].bet == bet);
};

TEST_CASE("Hands score properly", "[Hand]") {
    // Simple 2 card hand
    engine::Hand Hand1(false);
    Hand1.addCard(engine::Card(engine::Suit::Spades, 12));
    Hand1.addCard(engine::Card(engine::Suit::Spades, 13));
    Hand1.print();
    REQUIRE(Hand1.score() == 20);
    REQUIRE(!Hand1.isBlackjack());
    // 3 card bust - Player
    engine::Hand Hand2(false);
    Hand2.addCard(engine::Card(engine::Suit::Spades, 12));
    Hand2.addCard(engine::Card(engine::Suit::Spades, 13));
    Hand2.addCard(engine::Card(engine::Suit::Spades, 13));
    Hand2.print();
    REQUIRE(Hand2.score() == -1);
    REQUIRE(!Hand2.isBlackjack());
    // 3 card bust - Dealer
    engine::Hand Hand3(true);
    Hand3.addCard(engine::Card(engine::Suit::Spades, 12));
    Hand3.addCard(engine::Card(engine::Suit::Spades, 13));
    Hand3.addCard(engine::Card(engine::Suit::Spades, 13));
    Hand3.print();
    REQUIRE(Hand3.score() == 0);
    REQUIRE(!Hand3.isBlackjack());
    // Blackjack
    engine::Hand Hand4(false);
    Hand4.addCard(engine::Card(engine::Suit::Spades, 13));
    Hand4.addCard(engine::Card(engine::Suit::Spades, 1));
    Hand4.print();
    REQUIRE(Hand4.score() == 21);
    REQUIRE(Hand4.isBlackjack());
    // 5 card 21
    engine::Hand Hand5(false);
    Hand5.addCard(engine::Card(engine::Suit::Spades, 5));
    Hand5.addCard(engine::Card(engine::Suit::Spades, 1));
    Hand5.addCard(engine::Card(engine::Suit::Spades, 2));
    Hand5.addCard(engine::Card(engine::Suit::Spades, 2));
    Hand5.addCard(engine::Card(engine::Suit::Spades, 1));
    Hand5.print();
    REQUIRE(Hand5.score() == 21);
    REQUIRE(!Hand5.isBlackjack());
};

//TEST_CASE("Hands compute actions available correctly", "[Hand]") {
//    // Initial deal w/ different rank
//    engine::Hand Hand1(false);
//    Hand1.addCard(engine::Card(engine::Suit::Spades, 12));
//    Hand1.addCard(engine::Card(engine::Suit::Spades, 13));
//    Hand1.print();
//    std::vector<int> expected = { 0, 1, 3 };
//    REQUIRE(Hand1.actionsAvailable() == expected);
//    // 21
//    engine::Hand Hand2(false);
//    Hand2.addCard(engine::Card(engine::Suit::Spades, 12));
//    Hand2.addCard(engine::Card(engine::Suit::Spades, 13));
//    Hand2.addCard(engine::Card(engine::Suit::Spades, 1));
//    Hand2.print();
//    expected = {};
//    REQUIRE(Hand2.actionsAvailable() == expected);
//    // Bust
//    engine::Hand Hand3(false);
//    Hand3.addCard(engine::Card(engine::Suit::Spades, 12));
//    Hand3.addCard(engine::Card(engine::Suit::Spades, 13));
//    Hand3.addCard(engine::Card(engine::Suit::Spades, 13));
//    Hand3.print();
//    expected = {};
//    REQUIRE(Hand3.actionsAvailable() == expected);
//    // Split
//    engine::Hand Hand4(false);
//    Hand4.addCard(engine::Card(engine::Suit::Spades, 1));
//    Hand4.addCard(engine::Card(engine::Suit::Spades, 1));
//    Hand4.print();
//    expected = { 0, 1, 2, 3 };
//    REQUIRE(Hand4.actionsAvailable() == expected);
//    // Dealer can only hit or stand
//    engine::Hand Hand5(true);
//    Hand5.addCard(engine::Card(engine::Suit::Spades, 5));
//    Hand5.addCard(engine::Card(engine::Suit::Spades, 5));
//    Hand5.print();
//    expected = { 0, 1 };
//    REQUIRE(Hand5.actionsAvailable() == expected);
//};

//TEST_CASE("Play a 2 player round where everyone busts", "[Round]") {
//    // Create our players
//    float bankroll = 10000;
//    engine::Player Dealer(0, std::numeric_limits<int>::max(), &engine::always10, &engine::alwaysHit); // For now the dealer has a bankroll equal to the max int
//    engine::Player Player1(1, bankroll, &engine::always10, &engine::alwaysHit);
//    engine::Player Player2(2, bankroll, &engine::always10, &engine::alwaysHit);
//    std::vector<engine::Player> Players = { Dealer , Player1 , Player2 };
//    // Create our shoe
//    engine::Shoe Shoe(6);
//    // Create our round
//    engine::Round Round(Players, Shoe);
//    // Start the round
//    Round.play();
//    // Check bankroles
//    Round.players[1].print();
//    Round.players[2].print();
//    REQUIRE(Round.players[1].bankroll == 9990);
//    REQUIRE(Round.players[2].bankroll == 9990);
//};

//TEST_CASE("Play a 1 player round where the player doubles and wins", "[Round]") {
//    // Create our players
//    float bankroll = 10000;
//    engine::Player Dealer(0, std::numeric_limits<int>::max(), nullptr, &engine::alwaysHit); // For now the dealer has a bankroll equal to the max int
//    engine::Player Player1(1, bankroll, &engine::always10, &engine::alwaysDouble);
//    std::vector<engine::Player> Players = { Dealer , Player1 };
//    // Create our shoe
//    engine::Shoe Shoe(6);
//    // Create our round
//    engine::Round Round(Players, Shoe);
//    // Start the round
//    Round.play();
//    // Check bankroles
//    Round.players[1].print();
//    REQUIRE(Round.players[1].bankroll == 10020);
//};

TEST_CASE("Play a 1 player round where the player splits and wins", "[Round]") {
    // Create our players
    float bankroll = 10000;
    engine::Player Dealer(0, std::numeric_limits<float>::max(), nullptr, &engine::alwaysHit); // For now the dealer has a bankroll equal to the max int
    engine::Player Player1(1, bankroll, &engine::always10, &engine::splitOrStand);
    std::vector<engine::Player> Players = { Dealer , Player1 };
    // Create our shoe and make the first 4 cards the same
    engine::Shoe Shoe(6);
    engine::Card FirstCard = Shoe.cards[0];
    Shoe.cards.insert(Shoe.cards.begin(), FirstCard);
    Shoe.cards.insert(Shoe.cards.begin(), FirstCard);
    Shoe.cards.insert(Shoe.cards.begin(), FirstCard);
    Shoe.cards.insert(Shoe.cards.begin(), FirstCard); // Dealer hits 21 without this lol
    // Create our round
    engine::Round Round(Players, Shoe);
    // Start the round
    Round.play();
    // Check bankroles
    Round.players[1].print();
    REQUIRE(Round.players[1].bankroll == 10030); // The setup here ends up with 2 splits
};
