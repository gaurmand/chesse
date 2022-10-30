#include "state.h"

namespace Chess
{

bool operator==(const State& lhs, const State& rhs)
{
   return lhs.flags_ == rhs.flags_ && lhs.enPassantSquare_ == rhs.enPassantSquare_ && 
      lhs.halfMoveClock_ == rhs.halfMoveClock_ && lhs.fullMoveClock_ == rhs.fullMoveClock_;
}

void fromStateInt(StateInt state, State& stateObj)
{
   stateObj.fullMoveClock_ = state & 0xFFFF;
   state >>= 16;
   stateObj.halfMoveClock_ = state & 0xFFFF;
   state >>= 16;
   stateObj.enPassantSquare_ = state & 0xFF;
   state >>= 8;
   stateObj.flags_ = state;
}

StateInt toStateInt(const State& stateObj)
{
   StateInt res = stateObj.flags_.to_ulong();
   res <<= 8;
   res |= stateObj.enPassantSquare_;
   res <<= 16;
   res |= stateObj.halfMoveClock_;
   res <<= 16;
   res |= stateObj.fullMoveClock_;
   return res;
}

}  // namespace Chess
