#include "ai/Player.hpp"

std::pair<std::uint_fast8_t, std::uint_fast8_t> ai::Player(Board const &board,
                                                           Color        myColor)
{
    mvprintw(12, 0, "> ");
    std::string coords = "A1A1";
    // Player AI
    for (std::size_t i = 0; i < 4; i++)
    {
        coords[i] = getch();
        mvprintw(12, 2 + i, "%c", coords[i]);
        mvprintw(12, 2 + i + 1,
                 "       "); // Clear everything after the typed character
        move(12, 2 + i + 1);
    }

    std::uint_fast8_t index1 = board.CoordToIndex(coords.substr(0, 2)),
                      index2 = board.CoordToIndex(coords.substr(2, 2));
    if (board.IsValidIndex(index1) && board.IsValidIndex(index2))
    {
        Piece movingPiece;
        if (board.GetPieceAtPos(index1, movingPiece))
        {
            // This piece exists, now let's see if we can actually move
            // this piece to the desired location
            if (board.CanMovePiece(index1, index2, myColor))
            {
                // This is an invalid move
                mvprintw(12, 0, "> Moved");
                return std::pair(index1, index2);
            }
            else
            {
                // This is an invalid move
                mvprintw(12, 0, "> Invalid");
            }
        }
        else // There is not piece at this coordinate
        {
            mvprintw(12, 0, "> No Piece");
        }
    }
    else // Invalid move
    {
        mvprintw(12, 0, "> Try again");
    }
    return std::make_pair<std::uint_fast8_t, std::uint_fast8_t>(255, 255);
}