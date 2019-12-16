#include "ai/Test.hpp"
#include "Board.hpp"
#include "Piece.hpp"

#include <limits>
#include <utility>
#include <vector>

struct PathResult
{
    PieceMove    pieceMove;
    std::int16_t score;
    PathResult(PieceMove m, std::int16_t s) : pieceMove(m), score(s) {}
    PathResult() : score(0) {}
};

PathResult GetBestSubpath(Board const &board, Color team, int maxDepth,
                          int depth = -1)
{
    if (depth <= 0)
        depth = maxDepth;

    PathResult best;
    best.score = std::numeric_limits<std::int16_t>::min();

    PieceMove currentPieceMove;

    board.IteratePossibleTurns(team, [&](Board const &newboard, auto moveMade) {
        PathResult res =
            (depth <= 1) ? PathResult(moveMade, newboard.TeamScore(team))
                         : GetBestSubpath(newboard, team, maxDepth, depth - 1);

        if (res.score > best.score)
        {
            best.pieceMove = moveMade;
            best.score     = res.score;
        }

        return true;
    });
    return best;
}

PieceMove ai::Test(Board const &board, Color myColor)
{
    auto bestImmediateMove = GetBestSubpath(board, myColor, 4);

    return bestImmediateMove.pieceMove;
}