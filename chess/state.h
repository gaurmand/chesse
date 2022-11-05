#ifndef CHESS_STATE_H
#define CHESS_STATE_H

#include "square.h"
#include "common.h"

namespace Chess
{

//=============================================================================
// StateInt bit structure (32 bits):
// 0-9:  fullMoveClock (10 bits)
// 10-18: halfMoveClock (9 bits)
// 19-26: enPassantSquare (8 bits)
// 27-32: flags (5 bits)
   // 27: canBlackLongCastle
   // 28: canBlackShortCastle
   // 29: canWhiteLongCastle
   // 30: canWhiteShortCastle
   // 31: activeColour (Black = 0 / White = 1)
using StateInt = uint32_t;

//=============================================================================
struct State
{  
   Colour activeColour_      = Colour::White;
   bool canWhiteShortCastle_ = true;
   bool canWhiteLongCastle_  = true;
   bool canBlackShortCastle_ = true;
   bool canBlackLongCastle_  = true;
   Square enPassantSquare_   = Sq::Invalid;
   u_int16_t halfMoveClock_  = 0;
   u_int16_t fullMoveClock_  = 0;
};

//=============================================================================
bool operator==(const State&, const State&);
bool operator!=(const State&, const State&);

//=============================================================================
void fromStateInt(StateInt state, State& stateObj);
StateInt toStateInt(const State& stateObj);

}  // namespace Chess

#endif   // CHESS_STATE_H