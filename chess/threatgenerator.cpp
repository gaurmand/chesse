#include "threatgenerator.h"

#include <cassert>

namespace Chess
{

//==========================================================================
bool ThreatGenerator::isInCheck(Colour c) const
{
   assert(board_.WKing() != Sq::Invalid);
   assert(board_.BKing() != Sq::Invalid);
   assert(board_.pieceAt(board_.WKing()) == PieceType::King);
   assert(board_.pieceAt(board_.BKing()) == PieceType::King);
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
   static const std::array<PieceType, 2> straightAttackers = {PieceType::Rook, PieceType::Queen};
   if (isAttackedBySlidingPiece(sq, threat, straights, straightAttackers))
   {
      return true;
   }

   // Diagonal attacks (Bishop or Queen)
   static const std::array<Direction, 4> diagonals = {UR, DR, DL, UL};
   static const std::array<PieceType, 2> diagonalAttackers = {PieceType::Bishop, PieceType::Queen};

   if (isAttackedBySlidingPiece(sq, threat, diagonals, diagonalAttackers))
   {
      return true;
   }

   // Knight attacks
   static const std::array<Direction, 8> knightDirs = {HUR, HRU, HRD, HDR, HDL, HLD, HLU, HUL};
   if (isAttackedByPiece(sq, threat, PieceType::Knight, knightDirs))
   {
      return true;
   }

   // Pawn attacks
   // NOTE: Ignores en passants since we will never need to check if a square is being
   // attacked by an en passant.
   static const std::array<Direction, 2> wAttackDirs = {DL, DR};
   static const std::array<Direction, 2> bAttackDirs = {UL, UR};
   const auto& attackDirs = threat == Colour::White ? wAttackDirs : bAttackDirs;
   if (isAttackedByPawn(sq, threat, attackDirs))
   {
      return true;
   }

   // King attacks
   static const std::array<Direction, 8> kingDirs = {U, UR, R, DR, D, DL, L, UL};
   if (isAttackedByPiece(sq, threat, PieceType::King, kingDirs))
   {
      return true;
   }

   return false;
}

//==========================================================================
bool ThreatGenerator::isAttackedByPiece(Square sq, Colour threat, PieceType piece, const std::array<Direction, 8>& dirs) const
{
   for (const Direction dir : dirs)
   {
      const Square to = squareAt(sq, dir);
      if (to != Sq::Invalid && board_.isPieceAt(to, piece) && board_.isColourAt(to, threat))
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
      if (to != Sq::Invalid && board_.isPieceAt(to, PieceType::Pawn) && board_.isColourAt(to, threat))
      {
         return true;
      }
   }
   return false;
}

//==========================================================================
bool ThreatGenerator::isAttackedBySlidingPiece(Square sq, Colour threat, const std::array<Direction, 4>& dirs, const std::array<PieceType, 2>& pieces) const
{
   const Colour friendly = enemy(threat);
   for (const Direction dir : dirs)
   {
      for (Square to = squareAt(sq, dir); to != Sq::Invalid; to = squareAt(to, dir))
      {
         if (board_.isColourAt(to, friendly))
         {
            break; // Friendly piece reached -> false
         }
         else if (board_.isColourAt(to, threat))
         {
            // Enemy piece reached -> return true or search next direction
            if ((board_.isPieceAt(to, pieces[0]) || board_.isPieceAt(to, pieces[1])))
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
