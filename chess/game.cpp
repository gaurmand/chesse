#include "game.h"

#include <cassert>

namespace Chess
{

StateInt Game::state() const
{
   return toStateInt(state_);
}

void Game::doMove(MoveInt move)
{
   // TODO
}

void Game::undoMove(MoveInt move)
{
   // TODO
}

void Game::setState(StateInt state)
{
   fromStateInt(state, state_);
}

}  // namespace Chess
