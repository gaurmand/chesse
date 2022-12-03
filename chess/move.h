#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include "square.h"
#include "common.h"

#include <iostream>

namespace Chess
{

// MoveInt bit structure (32 bits):
// 0-7: capture (8 bits)
// 8-15:  moveType (8 bits)
// 16-23: toSquare (8 bits)
// 24-31: fromSquare (8 bits)
using MoveInt = uint32_t;

using MoveAN = std::string;

//=============================================================================
struct Move
{
   Square from_   = Sq::Invalid;
   Square to_     = Sq::Invalid;
   MoveType type_ = MoveType::Invalid;
   Piece capture_ = Piece::Empty;

   operator MoveInt() const;
   operator MoveAN() const;
};

//=============================================================================
bool operator==(const Move&, const Move&);
std::ostream& operator<<(std::ostream&, const Move&);

//=============================================================================
void fromMoveInt(MoveInt, Move&);
MoveInt toMoveInt(const Move&);

//=============================================================================
void fromMoveAN(const MoveAN&, Move&);
MoveAN toMoveAN(const Move&);

//=============================================================================
struct BMove
{
   Square from_        = Sq::Invalid;
   Square to_          = Sq::Invalid;
   PieceType moved_    = PieceType::EmptyPiece;
   PieceType captured_ = PieceType::EmptyPiece;
   Color movedColour_  = Color::EmptyColor;
   Color capColour_    = Color::EmptyColor;
   MoveType type_      = MoveType::Invalid;

   operator Move() const;
   operator MoveAN() const;
};

//=============================================================================
bool operator==(const BMove&, const BMove&);
std::ostream& operator<<(std::ostream&, const BMove&);

}  // namespace Chess

#endif   // CHESS_MOVE_H