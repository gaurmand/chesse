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
void Game::undo(MoveInt move, StateInt prevState)
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

}  // namespace Chess
