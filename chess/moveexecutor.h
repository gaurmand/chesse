#ifndef CHESS_MOVE_EXECUTOR_H
#define CHESS_MOVE_EXECUTOR_H

#include "move.h"
#include "board.h"
#include "state.h"

namespace Chess
{

class MoveExecutor
{
public:
   MoveExecutor(Board& b, State& s) : board_(b), state_(s) {};

   void doMove(MoveInt move);
   void undoMove(MoveInt move);

private:
   Board& board_;
   State& state_;
};

}  // namespace Chess

#endif   // CHESS_MOVE_EXECUTOR_H