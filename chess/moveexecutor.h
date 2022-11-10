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
   void move(const Move& move);

   // =========================================================================
   /* 
      NOTE: We cannot undo the state since we do not know:
      - En passant state before any move
      - Castling state before king/rook move/capture
      - Half move clock before capture/double advance
   */
   void unmove(MoveInt move);
   void unmove(const Move& move);

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
   void updateBoardUnmove(const Move& mv);

   // =========================================================================
   // Assertions for testing
   void assertMove(const Move& mv) const;
   void assertUnmove(const Move& mv) const;

   // =========================================================================
   Board& board_;
   State& state_;
};

}  // namespace Chess

#endif   // CHESS_MOVE_EXECUTOR_H