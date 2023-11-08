#include <iostream>
#include "TickTackToe.h"

int main()
{

    TickTackToe game{};

    std::cout << "Welcome to tick tack toe!! You are playing as " << game.getSideName() << '\n';

    game.gameLoop();

}