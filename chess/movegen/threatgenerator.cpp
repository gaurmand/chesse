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
bool ThreatGenerator::isAttacked(Square sq, Colour threat) const
{
   // Straight attacks (Rook or Queen)
   static const std::array<Direction, 4> straights = {U, R, D, L};
   static const std::array<Piece, 2> straightAttackers = {Piece::Rook, Piece::Queen};
   if (isAttackedBySlidingPiece(sq, threat, straights, straightAttackers))
   {
      return true;
   }

   // Diagonal attacks (Bishop or Queen)
   static const std::array<Direction, 4> diagonals = {UR, DR, DL, UL};
   static const std::array<Piece, 2> diagonalAttackers = {Piece::Bishop, Piece::Queen};

   if (isAttackedBySlidingPiece(sq, threat, diagonals, diagonalAttackers))
   {
      return true;
   }

   // Knight attacks
   static const std::vector<Direction> knightDirs = {HUR, HRU, HRD, HDR, HDL, HLD, HLU, HUL};
   if (isAttackedByPiece(sq, threat, Piece::Knight, knightDirs))
   {
      return true;
   }

   // Pawn attacks
   // NOTE: Ignores en passants since we will never need to check if a square is being
   // attacked by an en passant.
   static const std::array<Direction, 2> wAttackDirs = {UL, UR};
   static const std::array<Direction, 2> bAttackDirs = {DL, DR};
   const auto& attackDirs = state_.active_ == Colour::White ? wAttackDirs : bAttackDirs;
   if (isAttackedByPawn(sq, threat, attackDirs))
   {
      return true;
   }

   // King attacks
   static const std::vector<Direction> kingDirs = {U, UR, R, DR, D, DL, L, UL};
   if (isAttackedByPiece(sq, threat, Piece::King, kingDirs))
   {
      return true;
   }

   return false;
}

//==========================================================================
bool ThreatGenerator::isAttackedByPiece(Square sq, Colour threat, Piece piece, const std::vector<Direction>& dirs) const
{
   for (const Direction dir : dirs)
   {
      const Square to = squareAt(sq, dir);
      if (to != Sq::Invalid && board_.pieceAt(to) == piece && board_.colourAt(to) == threat)
      {
         return true;
      }
   }
   return false;
}

//==========================================================================
bool ThreatGenerator::isAttackedByPawn(Square sq, Colour threat, const std::array<Direction, 2>& dirs) const
{
   for (const Direction dir : dirs)
   {
      const Square to = squareAt(sq, dir);
      if (to != Sq::Invalid && board_.pieceAt(to) == Piece::Pawn && board_.colourAt(to) == threat)
      {
         return true;
      }
   }
   return false;
}

//==========================================================================
bool ThreatGenerator::isAttackedBySlidingPiece(Square sq, Colour threat, const std::array<Direction, 4>& dirs, const std::array<Piece, 2>& pieces) const
{
   const Colour friendly = enemy(threat);
   for (const Direction dir : dirs)
   {
      for (Square to = squareAt(sq, dir); to != Sq::Invalid; to = squareAt(to, dir))
      {
         const Colour toColour = board_.colourAt(to);
         if (toColour == friendly)
         {
            break; // Friendly piece reached -> false
         }
         else if (toColour == threat)
         {
            // Enemy piece reached -> return true or search next direction
            if ((board_.pieceAt(to) == pieces[0] || board_.pieceAt(to) == pieces[1]))
            {
               return true;
            }
            else
            {
               break;
            }
         }
         else
         {
            // Empty square -> continue
         }
      }
   }
   return false;
}

}  // namespace Chess
