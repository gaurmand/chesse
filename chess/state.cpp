#include "state.h"

namespace Chess
{

//=============================================================================
bool operator==(const State& lhs, const State& rhs)
{
   return lhs.activeColour_ == rhs.activeColour_ && 
      lhs.canWhiteShortCastle_ == rhs.canWhiteShortCastle_ && 
      lhs.canWhiteLongCastle_ == rhs.canWhiteLongCastle_ && 
      lhs.canBlackShortCastle_ == rhs.canBlackShortCastle_ && 
      lhs.canBlackLongCastle_ == rhs.canBlackLongCastle_ && 
      lhs.enPassantSquare_ == rhs.enPassantSquare_ && 
      lhs.halfMoveClock_ == rhs.halfMoveClock_ && 
      lhs.fullMoveClock_ == rhs.fullMoveClock_;
}

//=============================================================================
bool operator!=(const State& lhs, const State& rhs)
{
   return !(lhs == rhs);
}

//=============================================================================
void fromStateInt(StateInt state, State& stateObj)
{
   stateObj.fullMoveClock_ = state & 0x3FF;
   state >>= 10;
   stateObj.halfMoveClock_ = state & 0x1FF;
   state >>= 9;
   stateObj.enPassantSquare_ = state & 0xFF;
   state >>= 8;
   stateObj.canBlackLongCastle_ = state & 0x1;
   state >>= 1;
   stateObj.canBlackShortCastle_ = state & 0x1;
   state >>= 1;
   stateObj.canWhiteLongCastle_ = state & 0x1;
   state >>= 1;
   stateObj.canWhiteShortCastle_ = state & 0x1;
   state >>= 1;
   stateObj.activeColour_ = state ? Colour::White : Colour::Black;
}

//=============================================================================
StateInt toStateInt(const State& stateObj)
{
   StateInt res = stateObj.activeColour_ == Colour::White ? 0x1 : 0x0;
   res <<= 1;
   res |= stateObj.canWhiteShortCastle_;
   res <<= 1;
   res |= stateObj.canWhiteLongCastle_;
   res <<= 1;
   res |= stateObj.canBlackShortCastle_;
   res <<= 1;
   res |= stateObj.canBlackLongCastle_;
   res <<= 8;
   res |= stateObj.enPassantSquare_;
   res <<= 9;
   res |= stateObj.halfMoveClock_;
   res <<= 10;
   res |= stateObj.fullMoveClock_;
   return res;
}

}  // namespace Chess
