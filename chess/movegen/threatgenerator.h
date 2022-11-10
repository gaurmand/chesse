#ifndef CHESS_THREAT_GENERATOR_H
#define CHESS_THREAT_GENERATOR_H

#include "../board.h"
#include "../state.h"
#include "../mailbox.h"

#include <vector>
#include <array>

namespace Chess
{

class ThreatGenerator
{
public:
   //==========================================================================
   ThreatGenerator(const Board& b, const State& s): board_(b), state_(s) {}
 
   //==========================================================================
   bool isInCheck(Colour c) const;

   //==========================================================================
   bool isAttacked(Square sq, Colour threat) const;

private:
   //==========================================================================
   bool isAttackedByPiece(Square sq, Colour threat, Piece piece, const std::vector<Direction>& dirs) const;
   bool isAttackedByPawn(Square sq, Colour threat, const std::array<Direction, 2>& dirs) const;
   bool isAttackedBySlidingPiece(Square sq, Colour threat, const std::array<Direction, 4>& dirs, const std::array<Piece, 2>& pieces) const;

protected:
   //==========================================================================
   const Board& board_;
   const State& state_;
};

}  // namespace Chess

#endif   // CHESS_THREAT_GENERATOR_H