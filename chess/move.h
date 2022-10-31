#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include "square.h"
#include "common.h"

namespace Chess
{

// MoveInt bit structure (32 bits):
// 0-7: capture (8 bits)
// 8-15:  moveType (8 bits)
// 16-23: toSquare (8 bits)
// 24-31: fromSquare (8 bits)
using MoveInt = uint32_t;

struct Move
{
   Square from_   = Sq::Invalid;
   Square to_     = Sq::Invalid;
   MoveType type_ = MoveType::Invalid;
   Piece capture_ = Piece::Empty;
};

bool operator==(const Move&, const Move&);

void fromMoveInt(MoveInt move, Move& moveObj);
MoveInt toMoveInt(const Move& moveObj);

}  // namespace Chess

#endif   // CHESS_MOVE_H