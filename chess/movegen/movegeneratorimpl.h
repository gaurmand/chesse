#ifndef CHESS_INTERNAL_GENERIC_MOVE_GEN_H
#define CHESS_INTERNAL_GENERIC_MOVE_GEN_H

#include "../move.h"
#include "../board.h"
#include "../state.h"
#include "../mailbox.h"
#include "outputter.h"

#include <vector>

namespace Chess::Internal
{

template<typename MoveFormat, typename OutputIt>
class MoveGenerator
{
public:
   //==========================================================================
   MoveGenerator(Board& b, State& s, OutputIt it) :
      board_(b), state_(s), out_(it) {}

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
   bool isAttacked(Square sq) const;
   bool isAttackedByPiece(Square from, Piece piece, const std::vector<Direction>& dirs) const;
   bool isAttackedByPawn(Square from, const std::array<Direction, 2>& dirs) const;
   bool isAttackedBySlidingPiece(Square from, const std::array<Direction, 4>& dirs, const std::array<Piece, 2>& pieces) const;

   //==========================================================================
   Board& board_;
   State& state_;
   Outputter<MoveFormat, OutputIt> out_;
};

}  // namespace Chess::Internal

#include "movegeneratorimpl.cpp" // template impl

#endif   // CHESS_INTERNAL_GENERIC_MOVE_GEN_H