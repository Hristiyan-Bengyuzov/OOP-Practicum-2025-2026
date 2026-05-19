#include <iostream>
#include "Game.h"

int main()
{
    Game game;
    game.playRound(Rock{}, Scissors{});  // Win
    game.playRound(Paper{}, Rock{});     // Win
    game.playRound(Lizard{}, Spock{});   // Win
    game.playRound(Spock{}, Spock{});    // Draw

    game.printScore(std::cout);
}
