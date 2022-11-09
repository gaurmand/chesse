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

   bool wasToggled = false;
   if (state_.active_ != c)
   {
      toggleColour(state_);
      wasToggled = true;
   }

   bool res = false;
   if (state_.active_ == Colour::White)
   {
      res = isAttacked(board_.WKing());
   }
   else
   {
      res = isAttacked(board_.BKing());
   }

   if (wasToggled)
   {
      toggleColour(state_);
   }

   return res;
}

//==========================================================================
bool ThreatGenerator::isAttacked(Square sq) const
{
   // Straight attacks (Rook or Queen)
   static const std::array<Direction, 4> straights = {U, R, D, L};
   static const std::array<Piece, 2> straightAttackers = {Piece::Rook, Piece::Queen};
   if (isAttackedBySlidingPiece(sq, straights, straightAttackers))
   {
      return true;
   }

   // Diagonal attacks (Bishop or Queen)
   static const std::array<Direction, 4> diagonals = {UR, DR, DL, UL};
   static const std::array<Piece, 2> diagonalAttackers = {Piece::Bishop, Piece::Queen};

   if (isAttackedBySlidingPiece(sq, diagonals, diagonalAttackers))
   {
      return true;
   }
   //std::cout << "Not attacked by Queen" << std::endl;

   // Knight attacks
   static const std::vector<Direction> knightDirs = {HUR, HRU, HRD, HDR, HDL, HLD, HLU, HUL};
   if (isAttackedByPiece(sq, Piece::Knight, knightDirs))
   {
      return true;
   }

   // Pawn attacks
   // NOTE: Ignores en passants since we will never need to check if a square is being
   // attacked by an en passant.
   static const std::array<Direction, 2> wAttackDirs = {UL, UR};
   static const std::array<Direction, 2> bAttackDirs = {DL, DR};
   const auto& attackDirs = state_.active_ == Colour::White ? wAttackDirs : bAttackDirs;
   if (isAttackedByPawn(sq, attackDirs))
   {
      return true;
   }

   // King attacks
   static const std::vector<Direction> kingDirs = {U, UR, R, DR, D, DL, L, UL};
   if (isAttackedByPiece(sq, Piece::King, kingDirs))
   {
      return true;
   }

   return false;
}

//==========================================================================
bool ThreatGenerator::isAttackedByPiece(Square sq, Piece piece, const std::vector<Direction>& dirs) const
{
   for (const Direction dir : dirs)
   {
      const Square to = squareAt(sq, dir);
      if (to != Sq::Invalid && board_.pieceAt(to) == piece && board_.colourAt(to) == state_.inactive_)
      {
         return true;
      }
   }
   return false;
}

//==========================================================================
bool ThreatGenerator::isAttackedByPawn(Square sq, const std::array<Direction, 2>& dirs) const
{
   for (const Direction dir : dirs)
   {
      const Square to = squareAt(sq, dir);
      if (to != Sq::Invalid && board_.pieceAt(to) == Piece::Pawn && board_.colourAt(to) == state_.inactive_)
      {
         return true;
      }
   }
   return false;
}

//==========================================================================
bool ThreatGenerator::isAttackedBySlidingPiece(Square sq, const std::array<Direction, 4>& dirs, const std::array<Piece, 2>& pieces) const
{
   for (const Direction dir : dirs)
   {
      for (Square to = squareAt(sq, dir); to != Sq::Invalid; to = squareAt(to, dir))
      {
         const Colour toColour = board_.colourAt(to);
         if (toColour == state_.active_)
         {
            break; // Friendly piece reached -> false
         }
         else if (toColour == state_.inactive_)
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
