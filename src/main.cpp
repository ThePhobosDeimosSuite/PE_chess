#include "board.h"
#include "rendering.h"
#include "input.h"
#include "message.h"
#include <iostream>
#include <vector>

int main()
{
    std::vector<Message> messageBuffer{};
    Board board{Chess::startingBoard, messageBuffer};

    while (true)
    {
        Rendering::clearScreen();
        std::cout << '\n';
        std::cout << board;
        std::cout << '\n';

        for (Message m : messageBuffer)
        {
            std::cout << m << '\n';
        }
        messageBuffer.clear();

        Move move{Input::getMoveInputFromUser()};

        board.movePlayerPiece(move);
    }
    return 0;
}