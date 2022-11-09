#include "move.h"

namespace Chess
{

//=============================================================================
bool operator==(const Move& lhs, const Move& rhs)
{
   return lhs.from_ == rhs.from_ && 
      lhs.to_ == rhs.to_ && 
      lhs.type_ == rhs.type_ && 
      lhs.capture_ == rhs.capture_; 
}

//=============================================================================

std::ostream& operator<<(std::ostream& os, const Move& m)
{
   return os << toMoveAN(m);
}

//=============================================================================
void fromMoveInt(MoveInt move, Move& moveObj)
{
   moveObj.capture_ = static_cast<Piece>(move & 0xFF);
   move >>= 8;
   moveObj.type_ = static_cast<MoveType>(move & 0xFF);
   move >>= 8;
   moveObj.to_ = move & 0xFF;
   move >>= 8;
   moveObj.from_ = move & 0xFF;
}

//=============================================================================
MoveInt toMoveInt(const Move& moveObj)
{
   MoveInt res = moveObj.from_;
   res <<= 8;
   res |= moveObj.to_;
   res <<= 8;
   res |= static_cast<uint8_t>(moveObj.type_);
   res <<= 8;
   res |= static_cast<uint8_t>(moveObj.capture_);
   return res;
}

//=============================================================================
void fromMoveAN(const MoveAN& str, Move& obj)
{
   obj.from_    = fromAN(str.substr(0,2));
   obj.to_      = fromAN(str.substr(3,2));
   obj.type_    = MoveType::Invalid;
   obj.capture_ = Piece::Empty;
}

//=============================================================================
MoveAN toMoveAN(const Move& obj)
{
   return toAN(obj.from_) + toAN(obj.to_);
}

//=============================================================================
Move::operator MoveInt() const
{
   return toMoveInt(*this);
}

//=============================================================================
Move::operator MoveAN() const
{
   return toMoveAN(*this);
}


}  // namespace Chess