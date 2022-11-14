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
bool Game::move(MoveInt mv)
{
   Move obj;
   fromMoveInt(mv, obj);
   return move(obj);
}

//=============================================================================
bool Game::move(Move move)
{
   exec_.move(move);
   tgen_.updateAttackTablesFromMove(move);
   return !tgen_.isInCheck(state_.inactive_);
}

//=============================================================================
void Game::unmove(MoveInt mv, State prevState)
{
   Move obj;
   fromMoveInt(mv, obj);
   unmove(obj, prevState);
}

//=============================================================================
void Game::unmove(Move mv, State prevState)
{
   exec_.unmove(mv);
   setState(prevState);
}

//=============================================================================
bool Game::isInCheck(Colour c) const
{
   return tgen_.isInCheck(c);
}

}  // namespace Chess
