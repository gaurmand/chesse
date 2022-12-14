#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "board.h"
#include "state.h"
#include "move.h"
#include "moveexecutor.h"
#include "movegenerator.h"
#include "threatgenerator.h"

namespace Chess
{

class Game
{
public:
   //==========================================================================
   Game() {};
   Game(const Board& b, const State& s): board_(b), state_(s) {};

   //==========================================================================
   Board board() const { return board_; }
   State state() const { return state_; }
   StateInt stateInt() const;

   //==========================================================================
   void setBoard(const Board& b) { board_ = b; }
   void setState(const State& s) { state_ = s; }
   void set(const Board& b, const State& s) { board_ = b; state_= s; }
   void setState(StateInt s);

   //==========================================================================
   // Returns true if legal move, false otherwise
   bool move(MoveInt mv);
   bool move(Move mv);

   //==========================================================================
   void unmove(MoveInt mv, State prevState);
   void unmove(Move mv, State prevState);

   //==========================================================================
   template <typename OutputIt>
   int moves(OutputIt it) { return MoveGenerator<OutputIt>(board_, state_, it)(); }

   //==========================================================================
   bool isInCheck(Colour c) const;

private:
   //==========================================================================
   Board board_;
   State state_;
   MoveExecutor exec_    = MoveExecutor(board_, state_);
   ThreatGenerator tgen_ = ThreatGenerator(board_, state_);
};

}  // namespace Chess

#endif   // CHESS_GAME_H