#include "cpu.h"

// Check who has the most piece
int evaluate(const Board &board)
{
    if (board.hasCPUWon())
    {
        return 100000;
    }
    else if (board.hasPlayerWon())
    {
        return -100000;
    }

    int value{0};
    board.forEachTile([&](const Tile &tile)
                      {
            auto pieceType{board.getPieceType(tile)};
            auto pieceColor{Piece::getPieceColor(pieceType)};
            if (pieceColor == PieceColor::Black)
            {
                value += Piece::getPieceValue(pieceType);
            }
            else if (pieceColor == PieceColor::White)
            {
                value -= Piece::getPieceValue(pieceType);
            } });

    return value;
}

int alphabeta(Board &board, int depth, int alpha, int beta, bool maximizing)
{
    if (depth <= 0 || board.isGameOver())
    {
        return evaluate(board);
    }
    std::array<Move, MoveGenerator::maxMoves> moves;
    int moveCount{MoveGenerator::getAvailableMoves(moves, board, maximizing ? PieceColor::Black : PieceColor::White)};
    if (moveCount == 0)
    {
        return evaluate(board);
    }

    if (maximizing)
    {
        int maxEval{INT_MIN};
        int i{0};
        for (auto &move : moves)
        {
            if (i >= moveCount)
            {
                break;
            }

            board.movePiece(move);

            int eval{alphabeta(board, depth - 1, alpha, beta, !maximizing)};

            board.unMovePiece(move);

            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);

            if (beta <= alpha)
            {
                break;
            }
            i++;
        }

        return maxEval;
    }
    else
    {
        int minEval{INT_MAX};
        int i{0};
        for (auto &move : moves)
        {
            if (i >= moveCount)
            {
                break;
            }

            board.movePiece(move);

            int eval{alphabeta(board, depth - 1, alpha, beta, !maximizing)};

            board.unMovePiece(move);

            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);

            if (beta <= alpha)
            {
                break;
            }
            i++;
        }

        return minEval;
    }
}

Move CPU::generateBestMoves(Board &board)
{
    int bestScore{INT_MIN};
    Move bestMove;

    std::array<Move, MoveGenerator::maxMoves> moves;
    int moveCount{MoveGenerator::getAvailableMoves(moves, board, PieceColor::Black)};

    int i{0};
    for (auto &move : moves)
    {
        if (i >= moveCount)
        {
            break;
        }

        board.movePiece(move);

        int score{alphabeta(board, minmaxDepth, INT_MIN, INT_MAX, false)};

        board.unMovePiece(move);

        if (score > bestScore)
        {
            bestMove = move;
            bestScore = score;
        }
        i++;
    }

    return bestMove;
}