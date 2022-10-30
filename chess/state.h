#ifndef CHESS_STATE_H
#define CHESS_STATE_H

#include "square.h"

#include <bitset>

namespace Chess
{

using State = uint64_t;

struct StateStruct
{
   std::bitset<5> flags_     = 0b11111;
   Square enPassantSquare_   = Sq::Invalid;
   u_int16_t halfMoveClock_  = 0;
   u_int16_t fullMoveClock_  = 0;
};

bool operator==(const StateStruct&, const StateStruct&);

void fromState(State state, StateStruct& stateObj);
State toState(const StateStruct& stateObj);

}  // namespace Chess

#endif   // CHESS_STATE_H