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
   PieceType capture_ = PieceType::Empty;

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


}  // namespace Chess

#endif   // CHESS_MOVE_H