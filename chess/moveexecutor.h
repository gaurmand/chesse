#ifndef CHESS_MOVE_EXECUTOR_H
#define CHESS_MOVE_EXECUTOR_H

#include "move.h"
#include "board.h"
#include "state.h"

namespace Chess
{

constexpr int L = -1;
constexpr int R = 1;
constexpr int T = 8;
constexpr int B = -8;

constexpr int TL = 7;
constexpr int BL = -7;
constexpr int TR = 9;
constexpr int BR = -9;

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