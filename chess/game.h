#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "board.h"
#include "state.h"
#include "move.h"

namespace Chess
{

class Game
{
public:
   Game() {};

   StateInt state() const;

   void doMove(MoveInt move);
   void undoMove(MoveInt move);
   void setState(StateInt state);

private:
   Board board_;
   State state_;
};

}  // namespace Chess

#endif   // CHESS_GAME_H