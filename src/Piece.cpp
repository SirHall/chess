#include "Piece.hpp"

Piece::Piece()
{
    this->SetType(PieceType::None);
    this->SetMoveState(MoveState::Unmoved);
}

Piece::Piece(PieceType type, Color color)
{
    this->SetType(type);
    this->SetColor(color);
    this->SetMoveState(MoveState::Unmoved);
}

Color OtherColor(Color color)
{
    return (color == Color::Blue) ? Color::Red : Color::Blue;
}
