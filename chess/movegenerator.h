#ifndef CHESS_MOVE_GENERATOR_H
#define CHESS_MOVE_GENERATOR_H

#include "move.h"
#include "board.h"
#include "state.h"
#include "mailbox.h"
#include "threatgenerator.h"

#include <vector>

namespace Chess
{

template<typename OutputIt>
class MoveGenerator : public ThreatGenerator
{
public:
   //==========================================================================
   // NOTE: isInCheck is necessary to check if castles are blocked
   MoveGenerator(const Board& b, const State& s, OutputIt it) :
      ThreatGenerator(b, s), out_(it) {}

   //==========================================================================
   int operator()();

private:
   //==========================================================================
   void genPawnMoves(Square from);
   void genWPawnMoves(Square from);
   void genBPawnMoves(Square from);

   //==========================================================================
   void genKnightMoves(Square from);
   void genKingMoves(Square from);
   void genSingleMoves(Square from, const std::vector<Direction>& directions);
   void genWCastles();
   void genBCastles();

   //==========================================================================
   void genBishopMoves(Square from);
   void genRookMoves(Square from);
   void genQueenMoves(Square from);
   void genSlidingMoves(Square from, const std::vector<Direction>& directions);

   //==========================================================================
   void pushMove(const Move& mv);

   //==========================================================================
   bool isInCheck_   = false;
   int numOutputted_ = 0;
   OutputIt out_;
};

}  // namespace Chess

#include "movegenerator.cpp" // template impl

#endif   // CHESS_MOVE_GENERATOR_H