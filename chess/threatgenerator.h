#ifndef CHESS_THREAT_GENERATOR_H
#define CHESS_THREAT_GENERATOR_H

#include "board.h"
#include "state.h"
#include "mailbox.h"
#include "bitboard.h"

#include <vector>
#include <array>

namespace Chess
{

class ThreatGenerator
{
public:
   //==========================================================================
   ThreatGenerator(const Board& b, const State& s): board_(b), state_(s) { 
      atk_.initialize(Colour::White, wAttackTable_);
      atk_.initialize(Colour::Black, bAttackTable_);
      wAtk_ = attackedSquares(wAttackTable_);
      bAtk_ = attackedSquares(bAttackTable_);
   }

   //==========================================================================
   void attackData(AttackData& data) const
   {
      data.wAtkTable_ = wAttackTable_;
      data.bAtkTable_ = bAttackTable_;
      data.wAtk_ = wAtk_;
      data.bAtk_ = bAtk_;
   }
   
   void setAttackData(AttackData& data)
   {
      wAttackTable_ = data.wAtkTable_;
      bAttackTable_ = data.bAtkTable_;
      wAtk_ = data.wAtk_;
      bAtk_ = data.bAtk_;
   }

   //==========================================================================
   void updateAttackTablesFromMove(const Move& move);

   //==========================================================================
   void updateAttackTablesFromUnmove(const Move& move);
 
   //==========================================================================
   bool isInCheck(Colour c) const;

   //==========================================================================
   bool isAttacked(Square sq, Colour threat) const;

protected:
   //==========================================================================
   const Board& board_;
   const State& state_;

   AttackTableUpdater atk_  = AttackTableUpdater(board_, state_);
   AttackTable wAttackTable_;
   AttackTable bAttackTable_;
   Bitboard wAtk_;
   Bitboard bAtk_;
};

}  // namespace Chess

#endif   // CHESS_THREAT_GENERATOR_H