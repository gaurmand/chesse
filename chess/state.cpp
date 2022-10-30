#include "state.h"

namespace Chess
{

bool operator==(const StateStruct& lhs, const StateStruct& rhs)
{
   return lhs.flags_ == rhs.flags_ && lhs.enPassantSquare_ == rhs.enPassantSquare_ && 
      lhs.halfMoveClock_ == rhs.halfMoveClock_ && lhs.fullMoveClock_ == rhs.fullMoveClock_;
}

void fromState(State state, StateStruct& stateObj)
{
   stateObj.fullMoveClock_ = state & 0xFFFF;
   state >>= 16;
   stateObj.halfMoveClock_ = state & 0xFFFF;
   state >>= 16;
   stateObj.enPassantSquare_ = state & 0xFF;
   state >>= 8;
   stateObj.flags_ = state;
}

State toState(const StateStruct& stateObj)
{
   State res = stateObj.flags_.to_ulong();
   res <<= 8;
   res |= stateObj.enPassantSquare_;
   res <<= 16;
   res |= stateObj.halfMoveClock_;
   res <<= 16;
   res |= stateObj.fullMoveClock_;
   return res;
}

}  // namespace Chess
