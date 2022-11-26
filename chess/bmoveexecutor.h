#ifndef CHESS_BMOVEEXECUTOR_H
#define CHESS_BMOVEEXECUTOR_H

#include "move.h"
#include "bboard.h"
#include "state.h"

namespace Chess
{

class BMoveExecutor
{
public:
   // =========================================================================
   BMoveExecutor(BBoard& b, State& s) : board_(b), state_(s) {};

   // =========================================================================
   void move(const BMove& move);

   // =========================================================================
   /* 
      NOTE: We cannot undo the state since we do not know:
      - En passant state before any move
      - Castling state before king/rook move/capture
      - Half move clock before capture/double advance
   */
   void unmove(const BMove& move);

private:
   // =========================================================================
   // Updates board and state for move
   void updateBoard(const BMove& mv);
   void updateEnPassant(const BMove& mv);
   void updateCastling(const BMove& mv);
   void updateHalfMoveClock(const BMove& mv);
   void updateFullMoveClock(const BMove& mv);

   // =========================================================================
   // Updates board and state for undo
   void updateBoardUnmove(const BMove& mv);

   // =========================================================================
   // Assertions for testing
   void assertMove(const BMove& mv) const;
   void assertUnmove(const BMove& mv) const;

   // =========================================================================
   BBoard& board_;
   State& state_;
};

}  // namespace Chess

#endif   // CHESS_BMOVEEXECUTOR_H