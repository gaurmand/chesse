#include "game.h"
#include "moveexecutor.h"

#include <cassert>

namespace Chess
{

StateInt Game::state() const
{
   return toStateInt(state_);
}

void Game::doMove(MoveInt move)
{
   MoveExecutor(board_, state_).doMove(move);
}

void Game::undoMove(MoveInt move)
{
   MoveExecutor(board_, state_).undoMove(move);
}

void Game::setState(StateInt state)
{
   fromStateInt(state, state_);
}

}  // namespace Chess
