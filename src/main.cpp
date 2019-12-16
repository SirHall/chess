#include <ncurses.h>

#include "AIFactory.hpp"
#include "Board.hpp"
#include "NCursesTerm.hpp"

#include <functional>
#include <string>
#include <thread>
#include <utility>
#include <vector>

int main(int argc, char *argv[])
{
    auto term = NCursesTerm();

    auto board = Board();

    auto aiFactory       = AIFactory();
    auto teamAIS         = std::vector<AIFunc>(2);
    teamAIS[Color::Blue] = aiFactory.GetAI("test");
    teamAIS[Color::Red]  = aiFactory.GetAI("player");

    Color currentTeam = Color::Red;

    while (true)
    {
        term.DrawBoard(board);

        // Draw which team's turn it is
        short colorPair =
            (currentTeam == Color::Red) ? RED_ON_BLACK : BLUE_ON_BLACK;

        std::string teamMsg = (currentTeam == Color::Red) ? "RED " : "BLUE";

        attron(COLOR_PAIR(colorPair));
        mvprintw(11, 4, teamMsg.c_str());
        attroff(COLOR_PAIR(colorPair));

        auto desiredMove = teamAIS[currentTeam](board, currentTeam);
        // If this move can be performed, then perform it and switch to the
        // other team. Otherwise ask the ai again
        if (board.CanMovePiece(desiredMove.first, desiredMove.second,
                               currentTeam))
        {
            // Move the piece
            board.MovePiece(desiredMove.first, desiredMove.second, currentTeam,
                            false);

            // Print out the team's move
            std::string moveStr = board.IndexToCoord(desiredMove.first) +
                                  board.IndexToCoord(desiredMove.second);
            attron(COLOR_PAIR(colorPair));
            mvprintw(13, 4, moveStr.c_str());
            attroff(COLOR_PAIR(colorPair));

            // std::this_thread::sleep_for(std::chrono::milliseconds(500));
            // I could have done (team=1-team), but felt this was more clear
            currentTeam =
                (currentTeam == Color::Red) ? Color::Blue : Color::Red;
        }
    }

    return 0;
}