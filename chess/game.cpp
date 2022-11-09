#include "game.h"

namespace Chess
{

//=============================================================================
StateInt Game::stateInt() const
{
   return toStateInt(state_);
}

//=============================================================================
void Game::setState(StateInt state)
{
   fromStateInt(state, state_);
}

//=============================================================================
void Game::move(MoveInt move)
{
   exec_.move(move);
}

//=============================================================================
void Game::undo(MoveInt move, State prevState)
{
   exec_.undo(move);
   setState(prevState);
}

//=============================================================================
void Game::move(Move move)
{
   exec_.move(move);
}

//=============================================================================
void Game::undo(Move move, State prevState)
{
   exec_.undo(move);
   setState(prevState);
}

//=============================================================================
bool Game::isActiveInCheck() const
{
   return tgen_.isInCheck(state_.active_);
}

//=============================================================================
bool Game::isInactiveInCheck() const
{
   return tgen_.isInCheck(state_.inactive_);
}

}  // namespace Chess
