#ifndef CHESS_STATE_H
#define CHESS_STATE_H

#include "square.h"
#include "common.h"

namespace Chess
{

// StateInt bit structure (45 bits):
// 0-15:  fullMoveClock (16 bits)
// 16-31: halfMoveClock (16 bits)
// 32-39: enPassantSquare (8 bits)
// 40-44: flags (5 bits)
   // 40: canBlackLongCastle
   // 41: canBlackShortCastle
   // 42: canWhiteLongCastle
   // 43: canWhiteShortCastle
   // 44: activeColour (Black = 0 / White = 1)
using StateInt = uint64_t;

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

bool operator==(const State&, const State&);

void fromStateInt(StateInt state, State& stateObj);
StateInt toStateInt(const State& stateObj);

}  // namespace Chess

#endif   // CHESS_STATE_H