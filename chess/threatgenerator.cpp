#include "threatgenerator.h"

#include <cassert>

namespace Chess
{

//==========================================================================
bool ThreatGenerator::isInCheck(Colour c) const
{
   assert(board_.WKing() != Sq::Invalid);
   assert(board_.BKing() != Sq::Invalid);
   assert(board_.pieceAt(board_.WKing()) == Piece::King);
   assert(board_.pieceAt(board_.BKing()) == Piece::King);
   assert(board_.colourAt(board_.WKing()) == Colour::White);
   assert(board_.colourAt(board_.BKing()) == Colour::Black);

   if (c == Colour::White)
   {
      return isAttacked(board_.WKing(), Colour::Black);
   }
   else
   {
      return isAttacked(board_.BKing(), Colour::White);
   }
}

//==========================================================================
void ThreatGenerator::updateAttackTablesFromMove(const Move& move)
{
   if (state_.active_ == Colour::White)
   {
      atk_.updateFromMove(move, bAttackTable_, wAttackTable_);
   }
   else
   {
      atk_.updateFromMove(move, wAttackTable_, bAttackTable_);
   }
   wAtk_ = attackedSquares(wAttackTable_);
   bAtk_ = attackedSquares(bAttackTable_);
}

//==========================================================================
void ThreatGenerator::updateAttackTablesFromUnmove(const Move& move)
{
   if (state_.active_ == Colour::White)
   {
      atk_.updateFromUnmove(move, wAttackTable_, bAttackTable_);
   }
   else
   {
      atk_.updateFromUnmove(move, bAttackTable_, wAttackTable_);
   }
}

bool ThreatGenerator::isAttacked(Square sq, Colour threat) const
{
   if (threat == Colour::White)
   {
      return wAtk_.test(sq);
   }
   else
   {
      return bAtk_.test(sq);
   }
}

}  // namespace Chess
