#ifndef CHESS_BITBOARD_H
#define CHESS_BITBOARD_H

#include "square.h"
#include "move.h"
#include "board.h"
#include "state.h"
#include "mailbox.h"

#include <bitset>
#include <array>

namespace Chess
{

using Bitboard = std::bitset<NUM_SQUARES>;
using AttackTable = std::array<Bitboard, NUM_SQUARES>;

//=============================================================================
struct AttackData
{
   AttackTable wAtkTable_;
   AttackTable bAtkTable_;
   Bitboard wAtk_;
   Bitboard bAtk_;
};

//=============================================================================
class AttackTableUpdater
{
public:
   //==========================================================================
   AttackTableUpdater(const Board& b, const State& s) : board_(b), state_(s) {}

   //==========================================================================
   void initialize(Colour friendly, AttackTable& bboard);
   void updateFromMove(const Move& move, AttackTable& friendly, AttackTable& enemy);
   void updateFromUnmove(const Move& move, AttackTable& friendly, AttackTable& enemy);

private:
   //==========================================================================
   void updateAffectedSquares(Square sq, Square stop, Colour friendC, AttackTable& friendly, AttackTable& enemy);
   void setBitsFreedPieces(const Move& move, Bitboard& bboard);

   //==========================================================================
   void updateBitboard(Square sq, Bitboard& bboard);
   void setBitsSlidingPieces(Square sq, Bitboard& bboard, const HalfCompass& dirs);
   void setBitsSlidingPieces(Square sq, Bitboard& bboard, Direction dir);
   static void setIfValid(Bitboard& bboard, Square loc) 
   { 
      if (loc != Sq::Invalid)
      {
         bboard.set(loc); 
      }
   }

   //==========================================================================
   const Board& board_;
   const State& state_;
};

//=============================================================================
Bitboard attackedSquares(const AttackTable& table);

//=============================================================================
bool isAttackedBy(Square sq, const AttackTable& table);

//=============================================================================
void print(const Bitboard& bboard);

}  // namespace Chess

#endif   // CHESS_BITBOARD_H