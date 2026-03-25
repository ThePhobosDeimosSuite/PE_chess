#include "game.h"

void Game::render()
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

void Game::playerTurn()
{
    while (true)
    {
        render();

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

        std::array<Move, MoveGenerator::maxMoves> availableMoves;
        int count{0};
        MoveGenerator::getAvailableMoves(availableMoves, count, m_board, move.getOrigin());

        for (const Move &availableMove : availableMoves)
        {
            if (move == availableMove)
            {
                m_board.movePiece(move);

                m_messageBuffer.emplace_back(std::format("Tile ({}, {}) moved to ({}, {})",
                                                         originCoordinate.first,
                                                         originCoordinate.second,
                                                         destinationCoordinate.first,
                                                         destinationCoordinate.second),
                                             Message::Success);
                return;
            }
        }

        m_messageBuffer.emplace_back(std::format("Tile ({}, {}) cannot go to ({}, {})",
                                                 originCoordinate.first,
                                                 originCoordinate.second,
                                                 destinationCoordinate.first,
                                                 destinationCoordinate.second),
                                     Message::Alert);
    }
}

void Game::CPUTurn()
{
    m_messageBuffer.emplace_back("\nCPU is thinking...", Message::Info);
    render();

    Move bestMove{CPU::generateBestMoves(m_board)};

    auto originCoordinate{bestMove.getOrigin().toCoordinate()};
    auto destinationCoordinate{bestMove.getDestination().toCoordinate()};

    m_board.movePiece(bestMove);

    m_messageBuffer.emplace_back(std::format("CPU moved tile ({}, {}) to ({}, {})",
                                             originCoordinate.first,
                                             originCoordinate.second,
                                             destinationCoordinate.first,
                                             destinationCoordinate.second),
                                 Message::Info);
}

bool Game::isGameOver()
{
    return m_board.hasCPUWon() || m_board.hasPlayerWon();
}

void Game::emplaceGameOverMessage()
{
    if (m_board.hasPlayerWon())
    {
        m_messageBuffer.emplace_back("You won!!!", Message::Success);
    }
    else if (m_board.hasCPUWon())
    {
        m_messageBuffer.emplace_back("You lost :(", Message::Alert);
    }
}

void Game::run()
{
    while (true)
    {
        playerTurn();
        if (isGameOver())
        {
            emplaceGameOverMessage();
            break;
        }

        CPUTurn();
        if (isGameOver())
        {
            emplaceGameOverMessage();
            break;
        }
    }

    render();
}
