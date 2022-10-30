#ifndef CHESS_STATE_H
#define CHESS_STATE_H

#include "square.h"

#include <bitset>

namespace Chess
{

using StateInt = uint64_t;

struct State
{
   std::bitset<5> flags_     = 0b11111;
   Square enPassantSquare_   = Sq::Invalid;
   u_int16_t halfMoveClock_  = 0;
   u_int16_t fullMoveClock_  = 0;
};

bool operator==(const State&, const State&);

void fromStateInt(StateInt state, State& stateObj);
StateInt toStateInt(const State& stateObj);

}  // namespace Chess

#endif   // CHESS_STATE_H