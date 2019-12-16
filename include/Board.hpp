#pragma once
#ifndef BOARD_HPP
#define BOARD_HPP

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "Piece.hpp"

typedef std::pair<std::uint_fast8_t, std::uint_fast8_t> PieceMove;

class Board
{
private:
    std::vector<Piece> board;

public:
    Board();
    Board(const Board &other);
    Board(Board &&other);
    Board &operator=(const Board &other);
    Board &operator=(Board &&other);
    ~Board();

    std::uint_fast8_t PosToIndex(std::uint_fast8_t x,
                                 std::uint_fast8_t y) const;
    void              IndexToPos(std::uint_fast8_t i, std::uint_fast8_t &x,
                                 std::uint_fast8_t &y) const;
    bool              IsValidIndex(std::uint_fast8_t i) const;

    void SetPieceAtPos(std::uint_fast8_t i, Piece piece);
    bool GetPieceAtPos(std::uint_fast8_t i, Piece &piece) const;

    bool CoordToIndex(std::string const &coord, std::uint_fast8_t &i) const;
    std::uint_fast8_t CoordToIndex(std::string const &coord) const;
    std::string       IndexToCoord(std::uint_fast8_t i) const;

    std::vector<std::uint_fast8_t> PossibleMoves(std::uint_fast8_t i) const;

    bool CanMovePiece(std::uint_fast8_t fromIndex, std::uint_fast8_t toIndex,
                      Color team) const;

    bool MovePiece(std::uint_fast8_t fromIndex, std::uint_fast8_t toIndex,
                   Color team, bool checkValidity = true);

    std::vector<PieceMove> AllPossibleTeamMoves(Color team) const;

    std::int16_t TeamScore(Color team) const;

    bool IsCheck(Color team) const;

    bool AnyPieceHitSpot(Color team, std::uint_fast8_t index) const;

    void IteratePossibleTurns(
        Color                                                       team,
        std::function<bool(Board const &board, PieceMove moveMade)> action)
        const;

    std::uint_fast8_t GetKingIndex(Color team) const;

    bool IsCheckMate(Color team, bool assumeMate = false) const;
};

#endif
