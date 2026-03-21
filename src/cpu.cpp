#include "cpu.h"

int evaluate(const Board &board)
{
}

int alphabeta(Board &board, int depth, int alpha, int beta, bool maximizing)
{
    if (depth <= 0 || board.isGameOver())
    {
        return evaluate(board);
    }
    std::array<Move, MoveGenerator::maxMoves> moves;
    MoveGenerator::getAvailableMoves(moves, board, maximizing ? PieceColor::Black : PieceColor::White);

    if (maximizing)
    {
        int maxEval{INT_MIN};
        for (const auto &move : moves)
        {
            board.movePiece(move);

            int eval{alphabeta(board, depth - 1, alpha, beta, !maximizing)};

            board.unMovePiece(move);

            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);

            if (beta <= alpha)
            {
                break;
            }
        }

        return maxEval;
    }
    else
    {
        int minEval{INT_MAX};
        for (const auto &move : moves)
        {
            board.movePiece(move);

            int eval{alphabeta(board, depth - 1, alpha, beta, !maximizing)};

            board.unMovePiece(move);

            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);

            if (beta <= alpha)
            {
                break;
            }
        }

        return minEval;
    }
}

Move CPU::generateBestMoves(Board &board)
{
    int bestScore{INT_MIN};
    Move bestMove;

    std::array<Move, MoveGenerator::maxMoves> moves;
    MoveGenerator::getAvailableMoves(moves, board, PieceColor::Black);

    for (const auto &move : moves)
    {
        board.movePiece(move);

        int score{alphabeta(board, alphabetaDepth, INT_MIN, INT_MAX, false)};

        board.unMovePiece(move);

        if (score > bestScore)
        {
            bestMove = move;
            bestScore = score;
        }
    }

    return bestMove;
}