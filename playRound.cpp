// playRound.cpp : Play a CLI round of blackjack.
//

#include "playRound.hpp"

int main(int argc, char* const argv[]) {
    // Create our players
    float bankroll = 10000;
    engine::Player Dealer(0, std::numeric_limits<float>::max(), nullptr, &engine::alwaysHit); // For now the dealer has a bankroll equal to the max int
    engine::Player Player1(1, bankroll, &engine::betCLI, &engine::playCLI);
    std::vector<engine::Player> Players = { Dealer , Player1 };
    // Create our shoe and make the first 4 cards the same
    engine::Shoe Shoe(6);
    engine::Card FirstCard = Shoe.cards[0];
    Shoe.shuffle();
    // Create our round
    engine::Round Round(Players, Shoe);
    // Play till ya lose
    while (Round.players[1].bankroll > 0) {
        Round.play();
    }
    return 0;
};

