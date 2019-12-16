#pragma once
#ifndef AI_TEST_HPP
#define AI_TEST_HPP

#include "AIFactory.hpp"
#include "Board.hpp"
#include "Piece.hpp"

#include <ncurses.h>

namespace ai
{
    PieceMove Test(Board const &board, Color myColor);
} // namespace ai
#endif
