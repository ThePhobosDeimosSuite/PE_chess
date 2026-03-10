#include "board.h"
#include "move.h"
#include "io_utils.h"
#include <iostream>
#include <vector>

int main()
{
    std::vector<Message> messageBuffer{};
    Board board{Settings::startingBoard, messageBuffer};

    while (true)
    {
        OutputUtils::clearScreen();
        std::cout << '\n';
        std::cout << board;
        std::cout << '\n';

        for (Message m : messageBuffer)
        {
            std::cout << m << '\n';
        }
        messageBuffer.clear();

        Move move{InputUtils::getMoveInputFromUser()};

        board.movePlayerPiece(move);
    }
    return 0;
}