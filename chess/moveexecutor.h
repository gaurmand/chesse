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
   // =========================================================================
   MoveExecutor(Board& b, State& s) : board_(b), state_(s) {};

   // =========================================================================
   void move(MoveInt move);
   void undo(MoveInt move);

private:
   // =========================================================================
   // Updates board and state for move
   void updateBoard(const Move& mv);
   void updateEnPassant(const Move& mv);
   void updateCastling(const Move& mv);
   void updateHalfMoveClock(const Move& mv);
   void updateFullMoveClock();

   // =========================================================================
   // Updates board and state for undo
   void updateBoardUndo(const Move& mv);

   // =========================================================================
   // Toggles active colour in state
   void toggleColour();

   // =========================================================================
   // Assertions for testing
   void assertMove(const Move& mv) const;
   void assertUndo(const Move& mv) const;

   // =========================================================================
   Board& board_;
   State& state_;
};

}  // namespace Chess

#endif   // CHESS_MOVE_EXECUTOR_H