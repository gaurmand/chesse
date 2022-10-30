#include "move.h"

namespace Chess
{

bool operator==(const Move& lhs, const Move& rhs)
{
   return lhs.from_ == rhs.from_ && lhs.to_ == rhs.to_ && lhs.type_ == rhs.type_; 
}

void fromMoveInt(MoveInt move, Move& moveObj)
{
   moveObj.type_ = static_cast<MoveType>(move & 0xFF);
   move >>= 8;
   moveObj.to_ = move & 0xFF;
   move >>= 8;
   moveObj.from_ = move & 0xFF;
}

MoveInt toMoveInt(const Move& moveObj)
{
   MoveInt res = moveObj.from_;
   res <<= 8;
   res |= moveObj.to_;
   res <<= 8;
   res |= static_cast<uint8_t>(moveObj.type_);
   return res;
}

}  // namespace Chess