#ifndef CHESS_MOVE_GENERATOR_H
#define CHESS_MOVE_GENERATOR_H

#include "../board.h"
#include "../state.h"
#include "../move.h"
#include "movegeneratorimpl.h"

#include <string>

namespace Chess
{
namespace Internal
{

template<typename MoveFormat>
class GenericMoveGenerator
{
public:
   //==========================================================================
   GenericMoveGenerator(Board& b, State& s): board_(b), state_(s) {}
 
   //==========================================================================
   template<typename OutputIt> 
   int operator()(OutputIt it) const;

private:
   //==========================================================================
   Board& board_;
   State& state_;
};

}  // namespace Internal

using MoveIntGenerator = Internal::GenericMoveGenerator<MoveInt>;
using MoveGenerator    = Internal::GenericMoveGenerator<Move>;
using MoveANGenerator  = Internal::GenericMoveGenerator<MoveAN>;

}  // namespace Chess

#include "movegenerator.cpp" // template impl

#endif   // CHESS_MOVE_GENERATOR_H