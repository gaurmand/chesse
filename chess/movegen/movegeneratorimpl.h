#ifndef CHESS_INTERNAL_GENERIC_MOVE_GEN_H
#define CHESS_INTERNAL_GENERIC_MOVE_GEN_H

#include "../move.h"
#include "../board.h"
#include "../state.h"
#include "../mailbox.h"
#include "threatgenerator.h"

#include <vector>

namespace Chess::Internal
{

template<typename OutputIt>
class MoveGenerator : public ThreatGenerator
{
public:
   //==========================================================================
   // NOTE: isInCheck is necessary to check if castles are blocked
   MoveGenerator(Board& b, State& s, bool isInCheck, OutputIt it) :
      ThreatGenerator(b, s), board_(b), state_(s), isInCheck_(isInCheck), out_(it) {}

   //==========================================================================
   int exec();

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
   Board& board_;
   State& state_;
   bool isInCheck_ = false;
   OutputIt out_;
   int numOutputted_ = 0;
};

}  // namespace Chess::Internal

#include "movegeneratorimpl.cpp" // template impl

#endif   // CHESS_INTERNAL_GENERIC_MOVE_GEN_H