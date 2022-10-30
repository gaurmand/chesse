#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "board.h"
#include "state.h"

namespace Chess
{

class Game
{
public:
   Game() {};

private:
   Board board_;
   State state_;
};

}  // namespace Chess

#endif   // CHESS_GAME_H