// playRound.cpp : Play a CLI round of blackjack.
//

#include "engine.hpp"

int main() {
    // Game settings
    float bankroll = 10000;
    int n_rounds = 10000;
    int n_decks = 6;
    // Create our players
    engine::Player Dealer(0, std::numeric_limits<float>::max(), nullptr, &engine::standardDealer); // For now the dealer has a bankroll equal to the max int
    //engine::Player Player1(1, bankroll, &engine::simpleMartingale, &engine::alwaysStand);
    engine::Player Player1(1, bankroll, &engine::always10, &engine::alwaysStand);
    std::vector<engine::Player> Players = { Dealer , Player1 };
    // Create our table
    engine::Table Table(Players, n_decks);
    Table.n_rounds = n_rounds;
    // Play
    Table.play();
    // Plot player 1 bankroll through the game
    matplot::plot(Table.players[1].logs.bankroll);
    matplot::title("Player 1 Bankroll");
    matplot::xlabel("Hand");
    matplot::ylabel("Bankroll");
    matplot::xlim({0, double(Table.n_rounds)});
    matplot::show();
    return 0;
};

