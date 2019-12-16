#pragma once
#ifndef PIECE_HPP
#define PIECE_HPP

#include <cstdint>

enum PieceType : std::uint8_t
{
    None,
    Pawn,
    Rook,
    Bishop,
    Knight,
    King,
    Queen
};

enum Color : std::uint8_t
{
    Blue = 0, // Replaces black team
    Red  = 1  // Replaces red team
};

Color OtherColor(Color color);

enum MoveState : std::uint8_t
{
    Unmoved = 0,
    Moved   = 1
};

struct Piece
{
private:
    std::uint8_t v;

public:
    Piece();
    Piece(PieceType type, Color color);

    inline void      SetType(PieceType icon) { v = (v & 0b11111000) | icon; }
    inline PieceType GetType()
    {
        return static_cast<PieceType>(v & 0b00000111);
    }

    inline void  SetColor(Color color) { v = (v & 0b11110111) | (color << 3); }
    inline Color GetColor() { return static_cast<Color>((v & 0b00001000) > 0); }

    inline void SetMoveState(MoveState moveState)
    {
        v = (v & 0b11101111) | (moveState << 4);
    }
    inline MoveState GetMoveState()
    {
        return static_cast<MoveState>((v & 0b00010000) > 0);
    }
};

#endif
