#include <iostream>
#include "board.h"
#include "move.h"
#include "input_utils.h"

int main()
{
    Board board{Settings::STARTING_BOARD};
    Rendering::clearScreen();

    std::cout << board;

    std::cout << '\n';
    Move move{InputUtils::getMoveInputFromUser()};
    std::cout << "Move x: " << move.getOrigin().x << " origin y: " << move.getOrigin().y;
    std::cout << '\n';
    std::cout << "Move x: " << move.getDestination().x << " desti y: " << move.getDestination().y;
    // board.movePiece(move);

    // Rendering::clearScreen();
    // std::cout << board;

    return 0;
}