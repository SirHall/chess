#pragma once
#ifndef AI_PLAYER_HPP
#define AI_PLAYER_HPP

#include "AIFactory.hpp"
#include "Board.hpp"
#include "Piece.hpp"

#include <ncurses.h>

namespace ai
{
    std::pair<std::uint_fast8_t, std::uint_fast8_t> Player(Board const &board,
                                                           Color myColor);
} // namespace ai

#endif
