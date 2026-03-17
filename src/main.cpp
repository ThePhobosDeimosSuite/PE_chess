#include "board.h"
#include "rendering.h"
#include "input.h"
#include "message.h"
#include "move_generator.h"
#include <iostream>
#include <format>
#include <vector>

void printUI(const Board &board, std::vector<Message> &messageBuffer)
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
}

int main()
{
    std::vector<Message> messageBuffer{};
    Board board{Chess::startingBoard};

    while (true)
    {
        printUI(board, messageBuffer);

        Move move{Input::getMoveInputFromUser()};
        auto originCoordinate{move.getOrigin().toCoordinate()};
        auto destinationCoordinate{move.getDestination().toCoordinate()};

        if (!board.isPlayerTile(move.getOrigin()))
        {
            messageBuffer.emplace_back(std::format("Tile ({}, {}) is not one of your piece",
                                                   originCoordinate.first,
                                                   originCoordinate.second),
                                       Message::Alert);
            continue;
        }

        auto availableMoves{MoveGenerator::getAvailableMoves(board, move.getOrigin())};

        bool found{false};
        for (const Move &availableMove : availableMoves)
        {
            if (move == availableMove)
            {
                found = true;
                board.movePiece(move);

                messageBuffer.emplace_back(std::format("Tile ({}, {}) moved to ({}, {})",
                                                       originCoordinate.first,
                                                       originCoordinate.second,
                                                       destinationCoordinate.first,
                                                       destinationCoordinate.second),
                                           Message::Success);
                break;
            }
        }

        if (!found)
        {
            messageBuffer.emplace_back(std::format("Tile ({}, {}) cannot go to ({}, {})",
                                                   originCoordinate.first,
                                                   originCoordinate.second,
                                                   destinationCoordinate.first,
                                                   destinationCoordinate.second),
                                       Message::Alert);
        }

        if (board.hasPlayerWon())
        {
            messageBuffer.emplace_back("You won!!!", Message::Success);
            break;
        }
        else if (board.hasCPUWon())
        {
            messageBuffer.emplace_back("You lost :(", Message::Alert);
            break;
        }
    }

    printUI(board, messageBuffer);
    return 0;
}