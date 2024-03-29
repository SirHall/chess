#include "Board.hpp"

#include <functional>
#include <utility>
#include <vector>

Board::Board()
{
    this->board.resize(8 * 8);

    // Initialize red/white team
    SetPieceAtPos(CoordToIndex("A1"), Piece(PieceType::Rook, Color::Red));
    SetPieceAtPos(CoordToIndex("B1"), Piece(PieceType::Knight, Color::Red));
    SetPieceAtPos(CoordToIndex("C1"), Piece(PieceType::Bishop, Color::Red));
    SetPieceAtPos(CoordToIndex("D1"), Piece(PieceType::King, Color::Red));
    SetPieceAtPos(CoordToIndex("E1"), Piece(PieceType::Queen, Color::Red));
    SetPieceAtPos(CoordToIndex("F1"), Piece(PieceType::Bishop, Color::Red));
    SetPieceAtPos(CoordToIndex("G1"), Piece(PieceType::Knight, Color::Red));
    SetPieceAtPos(CoordToIndex("H1"), Piece(PieceType::Rook, Color::Red));
    SetPieceAtPos(CoordToIndex("A2"), Piece(PieceType::Pawn, Color::Red));
    SetPieceAtPos(CoordToIndex("B2"), Piece(PieceType::Pawn, Color::Red));
    SetPieceAtPos(CoordToIndex("C2"), Piece(PieceType::Pawn, Color::Red));
    SetPieceAtPos(CoordToIndex("D2"), Piece(PieceType::Pawn, Color::Red));
    SetPieceAtPos(CoordToIndex("E2"), Piece(PieceType::Pawn, Color::Red));
    SetPieceAtPos(CoordToIndex("F2"), Piece(PieceType::Pawn, Color::Red));
    SetPieceAtPos(CoordToIndex("G2"), Piece(PieceType::Pawn, Color::Red));
    SetPieceAtPos(CoordToIndex("H2"), Piece(PieceType::Pawn, Color::Red));

    // Initialize blue/black team
    SetPieceAtPos(CoordToIndex("A8"), Piece(PieceType::Rook, Color::Blue));
    SetPieceAtPos(CoordToIndex("B8"), Piece(PieceType::Knight, Color::Blue));
    SetPieceAtPos(CoordToIndex("C8"), Piece(PieceType::Bishop, Color::Blue));
    SetPieceAtPos(CoordToIndex("D8"), Piece(PieceType::King, Color::Blue));
    SetPieceAtPos(CoordToIndex("E8"), Piece(PieceType::Queen, Color::Blue));
    SetPieceAtPos(CoordToIndex("F8"), Piece(PieceType::Bishop, Color::Blue));
    SetPieceAtPos(CoordToIndex("G8"), Piece(PieceType::Knight, Color::Blue));
    SetPieceAtPos(CoordToIndex("H8"), Piece(PieceType::Rook, Color::Blue));
    SetPieceAtPos(CoordToIndex("A7"), Piece(PieceType::Pawn, Color::Blue));
    SetPieceAtPos(CoordToIndex("B7"), Piece(PieceType::Pawn, Color::Blue));
    SetPieceAtPos(CoordToIndex("C7"), Piece(PieceType::Pawn, Color::Blue));
    SetPieceAtPos(CoordToIndex("D7"), Piece(PieceType::Pawn, Color::Blue));
    SetPieceAtPos(CoordToIndex("E7"), Piece(PieceType::Pawn, Color::Blue));
    SetPieceAtPos(CoordToIndex("F7"), Piece(PieceType::Pawn, Color::Blue));
    SetPieceAtPos(CoordToIndex("G7"), Piece(PieceType::Pawn, Color::Blue));
    SetPieceAtPos(CoordToIndex("H7"), Piece(PieceType::Pawn, Color::Blue));
}

Board::Board(const Board &other) { this->board = std::vector(other.board); }

Board::Board(Board &&other) { this->board = std::move(other.board); }

Board &Board::operator=(const Board &other)
{
    this->board = std::vector(other.board);
    return *this;
}

Board &Board::operator=(Board &&other)
{
    this->board = std::move(other.board);
    return *this;
}

Board::~Board() {}

std::uint_fast8_t Board::PosToIndex(std::uint_fast8_t x,
                                    std::uint_fast8_t y) const
{
    if (x >= 8 || y >= 8)
        return 255;
    return x + (y * 8);
}

void Board::IndexToPos(std::uint_fast8_t i, std::uint_fast8_t &x,
                       std::uint_fast8_t &y) const
{
    x = i % 8;
    y = i / 8;
}

void Board::SetPieceAtPos(std::uint_fast8_t i, Piece piece)
{
    board[i] = piece;
}

bool Board::GetPieceAtPos(std::uint_fast8_t i, Piece &piece) const
{
    if (!IsValidIndex(i))
        return false;
    piece = board[i];
    return piece.GetType() != PieceType::None;
}

bool Board::CoordToIndex(std::string const &coord, std::uint_fast8_t &i) const
{
    if (coord.length() != 2)
        return false;

    i = this->PosToIndex(std::toupper(coord[0]) - 'A', coord[1] - '1');

    return true;
}

std::uint_fast8_t Board::CoordToIndex(std::string const &coord) const
{
    std::uint_fast8_t i = 255;
    if (CoordToIndex(coord, i)) {}
    return i;
}

std::string Board::IndexToCoord(std::uint_fast8_t i) const
{
    std::string       coord = "ER";
    std::uint_fast8_t x     = 0;
    std::uint_fast8_t y     = 0;
    this->IndexToPos(i, x, y);
    coord[0] = 'A' + x;
    coord[1] = '1' + y;
    return coord;
}

bool Board::IsValidIndex(std::uint_fast8_t i) const { return i < (8 * 8); }

std::vector<std::uint_fast8_t> Board::PossibleMoves(std::uint_fast8_t i) const
{

    auto moves = std::vector<std::uint_fast8_t>();

    Piece             piece;
    std::uint_fast8_t pieceX = 0;
    std::uint_fast8_t pieceY = 0;
    IndexToPos(i, pieceX, pieceY);

    Piece otherPiece;

    if (GetPieceAtPos(i, piece))
    {
        switch (piece.GetType())
        {
            case PieceType::King:
                for (int i = -1; i <= 1; i++)
                {
                    for (int j = -1; j <= 1; j++)
                    {
                        if (i == 0 && j == 0)
                            continue;

                        std::uint_fast8_t newIndex =
                            PosToIndex(pieceX + i, pieceY + j);

                        if (GetPieceAtPos(newIndex, otherPiece))
                        {
                            if (otherPiece.GetColor() != piece.GetColor() &&
                                otherPiece.GetType() != PieceType::King)
                                moves.push_back(newIndex);
                        }
                        else if (IsValidIndex(newIndex))
                            moves.push_back(newIndex);
                    }
                }
                break;

            case PieceType::Queen:
            case PieceType::Rook:
            case PieceType::Bishop:
                for (int dirX = -1; dirX <= 1; dirX++)
                {
                    for (int dirY = -1; dirY <= 1; dirY++)
                    {
                        if ((piece.GetType() == PieceType::Queen &&
                             (dirX == 0 && dirY == 0)) ||
                            (piece.GetType() == PieceType::Rook &&
                             (dirX != 0 && dirY != 0)) ||
                            (piece.GetType() == PieceType::Bishop &&
                             (dirX == 0 || dirY == 0)))
                            continue;

                        for (int offset = 1; offset <= 8; offset++)
                        {
                            std::uint_fast8_t newIndex =
                                PosToIndex(pieceX + (offset * dirX),
                                           pieceY + (offset * dirY));
                            if (IsValidIndex(newIndex))
                            {
                                if (GetPieceAtPos(newIndex, otherPiece))
                                {
                                    if (otherPiece.GetColor() !=
                                            piece.GetColor() &&
                                        otherPiece.GetType() != PieceType::King)
                                        moves.push_back(newIndex);
                                    break; // Stop searching along this line
                                }
                                else
                                    moves.push_back(newIndex);
                            }
                        }
                    }
                }
                break;
            case PieceType::Knight:
            {
                std::vector<std::pair<signed int, signed int>> jumpDirs = {
                    {1, 2}, {1, -2}, {-1, 2}, {-1, -2},
                    {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};

                for (auto jumpDir : jumpDirs)
                {
                    std::uint_fast8_t newIndex = PosToIndex(
                        pieceX + jumpDir.first, pieceY + jumpDir.second);
                    GetPieceAtPos(newIndex, otherPiece);
                    if (IsValidIndex(newIndex) &&
                        piece.GetColor() != otherPiece.GetColor() &&
                        otherPiece.GetType() != PieceType::King)
                        moves.push_back(newIndex);
                }

                break;
            }
            case PieceType::Pawn:
            {
                int dir = (piece.GetColor() == Color::Red) ? 1 : -1;
                std::uint_fast8_t newIndex = PosToIndex(pieceX, pieceY + dir);
                // Can this piece move atleast one space (not blocked)
                bool moveOneSpace = false;
                if (IsValidIndex(newIndex) &&
                    !GetPieceAtPos(newIndex, otherPiece))
                {
                    moves.push_back(newIndex);
                    moveOneSpace = true;
                }
                if ((piece.GetMoveState() == MoveState::Unmoved) &&
                    moveOneSpace)
                {
                    newIndex = PosToIndex(pieceX, pieceY + (dir * 2));
                    if (IsValidIndex(newIndex) &&
                        !GetPieceAtPos(newIndex, otherPiece))
                        moves.push_back(newIndex);
                }
                // Detect if there are enemies at corners, if there are add them
                // as valid positions
                for (auto xDiff : {1, -1})
                {
                    if (GetPieceAtPos(PosToIndex(pieceX + xDiff, pieceY + dir),
                                      otherPiece))
                    {
                        // If these pieces are on enemy teams
                        if (otherPiece.GetColor() != piece.GetColor() &&
                            otherPiece.GetType() != PieceType::King)
                        {
                            newIndex = PosToIndex(pieceX + xDiff, pieceY + 1);
                            if (IsValidIndex(newIndex))
                                moves.push_back(newIndex);
                        }
                    }
                }
            }

            default:
                break;
        }
    }
    return moves;
}

bool Board::CanMovePiece(std::uint_fast8_t fromIndex, std::uint_fast8_t toIndex,
                         Color team) const
{
    Piece movingPiece;
    GetPieceAtPos(fromIndex, movingPiece);
    if (movingPiece.GetColor() == team)
    {
        auto validMoves = PossibleMoves(fromIndex);
        return std::find(validMoves.begin(), validMoves.end(), toIndex) !=
               validMoves.end();
    }
    return false;
}

bool Board::MovePiece(std::uint_fast8_t fromIndex, std::uint_fast8_t toIndex,
                      Color team, bool checkValidity)
{
    bool validMove = false;
    if (checkValidity)
        validMove = CanMovePiece(fromIndex, toIndex, team);
    else // If we don't check the validity of a move, just move the piece
        validMove = true;

    // Move the piece
    if (validMove)
    {
        Piece movingPiece, otherPiece;
        GetPieceAtPos(fromIndex, movingPiece); // The piece that is being moved
        // GetPieceAtPos(toIndex, otherPiece);    // Where the piece will land

        movingPiece.SetMoveState(MoveState::Moved);
        SetPieceAtPos(toIndex, movingPiece);
        SetPieceAtPos(fromIndex, Piece());
    }
    return validMove;
}

std::vector<std::pair<std::uint_fast8_t, std::uint_fast8_t>>
    Board::AllPossibleTeamMoves(Color team) const
{
    auto allMoves =
        std::vector<std::pair<std::uint_fast8_t, std::uint_fast8_t>>();

    Piece piece;
    for (std::uint_fast8_t i = 0; i < (8 * 8); i++)
    {
        if (GetPieceAtPos(i, piece))
        {
            if (piece.GetColor() == team)
            {
                auto newMoves = PossibleMoves(i);
                for (auto newIndex : newMoves)
                    allMoves.push_back(std::make_pair(i, newIndex));
            }
        }
    }

    return allMoves;
}

std::int16_t PieceValue(PieceType type)
{
    std::int16_t values[7];
    values[PieceType::None]   = 0;
    values[PieceType::Pawn]   = 1;
    values[PieceType::Rook]   = 2;
    values[PieceType::Bishop] = 2;
    values[PieceType::Knight] = 3;
    values[PieceType::King]   = 5;
    values[PieceType::Queen]  = 4;
    return values[type];
}

std::int16_t Board::TeamScore(Color team) const
{
    std::int16_t points = 0;

    for (std::size_t i = 0; i < (8 * 8); i++)
    {
        Piece piece;
        if (GetPieceAtPos(i, piece))
        {
            // Add points for existance
            points += PieceValue(piece.GetType()) *
                      ((piece.GetColor() == team) ? 1 : -1);

            auto possibleMoves = PossibleMoves(i);

            for (auto singleMove : possibleMoves)
            {
                Piece otherPiece;
                if (GetPieceAtPos(singleMove, otherPiece))
                {
                    if (piece.GetColor() == team &&
                        otherPiece.GetColor() != team)
                    {
                        points += PieceValue(otherPiece.GetType());
                    }
                    if (piece.GetColor() != team &&
                        otherPiece.GetColor() == team)
                    {
                        points -= PieceValue(otherPiece.GetType());
                    }
                }
            }
        }
    }
    for (auto kingTeam : {Color::Blue, Color::Red})
    {
        std::uint_fast8_t kingIndex = GetKingIndex(kingTeam);
        std::uint_fast8_t kingX, kingY;
        IndexToPos(kingIndex, kingX, kingY);
        for (int x = -1; x <= 1; x++)
        {
            for (int y = -1; y <= 1; y++)
            {
                if (AnyPieceHitSpot(OtherColor(kingTeam),
                                    PosToIndex(kingX + x, kingY + y)))
                {
                    // Add/lose points for hitting squares around the
                    // king, and the king itself.
                    points += PieceValue(PieceType::King) *
                              ((kingTeam != team) ? 1 : -1);
                }
            }
        }
    }
    return points;
}

bool Board::AnyPieceHitSpot(Color team, std::uint_fast8_t index) const
{
    if (!IsValidIndex(index))
        return false;
    for (std::size_t i = 0; i < (8 * 8); i++)
    {
        if (i == index)
            continue;

        Piece attackingPiece;
        if (GetPieceAtPos(i, attackingPiece) &&
            attackingPiece.GetColor() != team)
        {
            auto possibleMoves = PossibleMoves(i);
            for (auto loc : possibleMoves)
            {
                if (loc == index)
                    return true;
            }
        }
    }
    return false;
}

bool Board::IsCheck(Color team) const
{

    return AnyPieceHitSpot(team, GetKingIndex(team));
}

void Board::IteratePossibleTurns(
    Color           team, std::function<bool(
                    Board const &                                   board,
                    std::pair<std::uint_fast8_t, std::uint_fast8_t> moveMade)>
                    action) const
{
    auto  possibleMoves = AllPossibleTeamMoves(team);
    Board subBoard;
    for (auto loc : possibleMoves)
    {
        subBoard = Board(*this);
        subBoard.MovePiece(loc.first, loc.second, team, false);
        if (!action(subBoard, loc))
            break;
    }
}

std::uint_fast8_t Board::GetKingIndex(Color team) const
{
    for (std::size_t i = 0; i < (8 * 8); i++)
    {
        Piece piece;
        if (GetPieceAtPos(i, piece) && piece.GetType() == PieceType::King &&
            piece.GetColor() == team)
        {
            return i;
        }
    }
    return 255;
}

bool Board::IsCheckMate(Color team, bool assumeMate) const
{
    bool inMate = assumeMate ? true : IsCheck(team);

    if (!inMate)
        return false;

    // Test to see if all the spaces around the king are hit
    std::uint_fast8_t kingIndex = GetKingIndex(team);
    std::uint_fast8_t kingX, kingY;
    IndexToPos(kingIndex, kingX, kingY);
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            if (x == 0 && y == 0)
                continue;

            if (AnyPieceHitSpot(OtherColor(team),
                                PosToIndex(kingX + x, kingY + y)))
            {
                // This spot is hit
            }
            else
            {
                // There is a free spot that the king can move into
                return false;
            }
        }
    }

    bool kingCannotEscape = true;

    // The king has nowhere to go, see if there are any moves we can do to get
    // the king out of check
    IteratePossibleTurns(team, [&](Board const &board, auto moveMade) {
        if (!this->IsCheck(team))
        {
            kingCannotEscape = false;
            return false;
        }
        return true;
    });

    return kingCannotEscape;
}