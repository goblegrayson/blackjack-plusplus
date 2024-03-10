// playRound.cpp : Play a CLI round of blackjack.
//

#include "engine.hpp"

int main(int argc, char* const argv[]) {
    // Game settings
    float bankroll = 10000;
    int n_rounds = 1000000000;
    int n_decks = 6;
    // Create our players
    float bankroll = 10000;
    engine::Player Dealer(0, std::numeric_limits<float>::max(), nullptr, &engine::alwaysHit); // For now the dealer has a bankroll equal to the max int
    engine::Player Player1(1, bankroll, &engine::betCLI, &engine::playCLI);
    std::vector<engine::Player> Players = { Dealer , Player1 };
    // Create our table
    engine::Table Table(Players, n_decks);
    Table.n_rounds = n_rounds;
    // Play
    Table.play();
    return 0;
};

