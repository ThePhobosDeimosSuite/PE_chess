#include "game.h"

void Game::printUI()
{
    Rendering::clearScreen();
    std::cout << '\n';
    std::cout << m_board;
    std::cout << '\n';

    for (Message m : m_messageBuffer)
    {
        std::cout << m << '\n';
    }
    m_messageBuffer.clear();
}

void Game::run()
{
    while (true)
    {
        printUI();

        Move move{Input::getMoveInputFromUser()};
        auto originCoordinate{move.getOrigin().toCoordinate()};
        auto destinationCoordinate{move.getDestination().toCoordinate()};

        if (!m_board.isPlayerTile(move.getOrigin()))
        {
            m_messageBuffer.emplace_back(std::format("Tile ({}, {}) is not one of your piece",
                                                     originCoordinate.first,
                                                     originCoordinate.second),
                                         Message::Alert);
            continue;
        }

        // TODO use c-style array here to avoid initialization of moves
        std::array<Move, MoveGenerator::maxMoves> availableMoves{};
        MoveGenerator::getAvailableMoves(availableMoves, m_board, move.getOrigin());

        bool found{false};
        for (const Move &availableMove : availableMoves)
        {
            if (move == availableMove)
            {
                found = true;
                m_board.movePiece(move);

                m_messageBuffer.emplace_back(std::format("Tile ({}, {}) moved to ({}, {})",
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
            m_messageBuffer.emplace_back(std::format("Tile ({}, {}) cannot go to ({}, {})",
                                                     originCoordinate.first,
                                                     originCoordinate.second,
                                                     destinationCoordinate.first,
                                                     destinationCoordinate.second),
                                         Message::Alert);
        }

        if (m_board.hasPlayerWon())
        {
            m_messageBuffer.emplace_back("You won!!!", Message::Success);
            break;
        }
        else if (m_board.hasCPUWon())
        {
            m_messageBuffer.emplace_back("You lost :(", Message::Alert);
            break;
        }
    }

    printUI();
}
