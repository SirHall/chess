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
