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
   void updateBoard(const Move& mv);
   void updateBoardUndo(const Move& mv);
   void updateEnPassant(const Move& mv);
   void updateCastling(const Move& mv);
   void updateHalfMoveClock(const Move& mv);
   void updateFullMoveClock();
   void toggleColour();

   Board& board_;
   State& state_;
};

}  // namespace Chess

#endif   // CHESS_MOVE_EXECUTOR_H