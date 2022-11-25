#include "bboard.h"

#include <cassert>

namespace Chess
{

//=============================================================================
void BBoard::setEmpty()
{
   for (int c = 0; c < kNumColors; ++c)
   {
      colours_[c].clear();
      for (int p = 0; p < kNumPieceTypes; ++p)
      {
         pieces_[c][p].clear();
      }
   }

   occupied_.clear();
   empty_.fill();
}

//=============================================================================
void BBoard::setDefault()
{
   static constexpr std::array<Bitboard, kNumPieceTypes> wDefault = {
      0x000000000000FF00, 0x0000000000000042, 0x0000000000000024,
      0x0000000000000081, 0x0000000000000008, 0x0000000000000010
   };
   static constexpr std::array<Bitboard, kNumPieceTypes> bDefault = {
      0x00FF000000000000, 0x4200000000000000, 0x2400000000000000,
      0x8100000000000000, 0x0800000000000000, 0x1000000000000000
   };

   pieces_   = {wDefault, bDefault};
   colours_  = {0x000000000000FFFF, 0xFFFF000000000000};
   occupied_ = 0xFFFF00000000FFFF;
   empty_    = 0x0000FFFFFFFF0000;
}

//=============================================================================
bool BBoard::isValid() const
{
   return isValidPiecePositions() && isValidPieceCounts();
}

//=============================================================================
bool BBoard::isValidPiecePositions() const
{
   for (Square sq = Sq::a1; sq <= Sq::h8; ++sq)
   {
      if (occupied_.test(sq) == empty_.test(sq))
      {
         return false;
      }

      const auto isSet = [sq](const Bitboard& bb){ return bb.test(sq); };
      const int numColoursSet = std::count_if(colours_.begin(), colours_.end(), isSet);
      const int numWPiecesSet = std::count_if(pieces_[Color::White].begin(), pieces_[Color::White].end(), isSet);
      const int numBPiecesSet = std::count_if(pieces_[Color::Black].begin(), pieces_[Color::Black].end(), isSet);

      if (occupied_.test(sq))
      {
         if (numColoursSet != 1)
         {
            return false;
         }
         if (numWPiecesSet == numBPiecesSet || numWPiecesSet > 1 || numBPiecesSet > 1)
         {
            return false;
         }
      }
      else if (empty_.test(sq))
      {
         if (numColoursSet != 0 || numWPiecesSet != 0 || numBPiecesSet != 0)
         {
            return false;
         }
      }
   }

   return true;
}

//=============================================================================
bool BBoard::isValidPieceCounts() const
{
   int sumColourCounts = 0;
   for (int i = 0; i < kNumColors; ++i)
   {
      const auto c = static_cast<Color>(i);
      const std::array<size_t, kNumPieceTypes> pieceCount =
      {
         pieces_[c][PieceType::Pawn].count(),
         pieces_[c][PieceType::Knight].count(),
         pieces_[c][PieceType::Bishop].count(),
         pieces_[c][PieceType::Rook].count(),
         pieces_[c][PieceType::Queen].count(),
         pieces_[c][PieceType::King].count()
      };

      if (pieceCount[PieceType::Pawn] > 8)
      {
         return false;
      }
      if (pieceCount[PieceType::Knight] > 10)
      {
         return false;
      }
      if (pieceCount[PieceType::Bishop] > 10)
      {
         return false;
      }
      if (pieceCount[PieceType::Rook] > 10)
      {
         return false;
      }
      if (pieceCount[PieceType::Queen] > 9)
      {
         return false;
      }
      if (pieceCount[PieceType::King] != 1)
      {
         return false;
      }

      const int colourCount = colours_[c].count();
      if (colourCount < 1 || colourCount > 16)
      {
         return false;
      }

      const int sumPieceCounts = std::accumulate(pieceCount.begin(), pieceCount.end(), 0);
      if (colourCount != sumPieceCounts)
      {
         return false;
      }

      sumColourCounts += colourCount;
   }

   const int occupiedCount = occupied_.count();
   const int emptyCount    = empty_.count();
   if (occupiedCount != (NUM_SQUARES - emptyCount))
   {
      return false;
   }

   if (occupiedCount != sumColourCounts)
   {
      return false;
   }

   return true;
}

//=============================================================================
Color BBoard::colourAt(Square sq) const
{
   for (int i = 0; i < kNumColors; ++i)
   {
      const auto c = static_cast<Color>(i);
      if (isColourAt(sq, c))
      {
         return c;
      }
   }
   return Color::EmptyColor;
}

//=============================================================================
PieceType BBoard::pieceAt(Square sq) const
{
   for (int i = 0; i < kNumPieceTypes; ++i)
   {
      const auto p = static_cast<PieceType>(i);
      if (isPieceAt(sq, p))
      {
         return p;
      }
   }
   return PieceType::EmptyPiece;
}

//=============================================================================
void BBoard::clear(Square sq, PieceType p, Color c)
{
   assert(isOccupied(sq));
   assert(isPieceAt(sq, p, c));

   pieces_[c][p].reset(sq);
   colours_[c].reset(sq);
   occupied_.reset(sq);
   empty_.set(sq);

   assert(!isOccupied(sq));
   assert(!isPieceAt(sq, p, c));
}

//=============================================================================
void BBoard::set(Square sq, PieceType p, Color c)
{
   assert(!isOccupied(sq));
   assert(!isPieceAt(sq, p, c));

   pieces_[c][p].set(sq);
   colours_[c].set(sq);
   occupied_.set(sq);
   empty_.reset(sq);

   assert(isOccupied(sq));
   assert(isPieceAt(sq, p, c));
}

//=============================================================================
void BBoard::promote(Square sq, PieceType from, PieceType to, Color c)
{
   assert(isOccupied(sq));
   assert(isPieceAt(sq, from, c));
   assert(!isPieceAt(sq, to, c));

   pieces_[c][from].reset(sq);
   pieces_[c][to].set(sq);

   assert(isOccupied(sq));
   assert(!isPieceAt(sq, from, c));
   assert(isPieceAt(sq, to, c));
}

//=============================================================================
void BBoard::capture(Square from, Square to, PieceType p, PieceType pc, Color c, Color cc)
{
   assert(isOccupied(from));
   assert(isPieceAt(from, p, c));
   assert(isOccupied(to));
   assert(isPieceAt(to, pc, cc));

   const Bitboard fromBB   = Bitboard::fromSquare(from);
   const Bitboard toBB     = Bitboard::fromSquare(to);
   const Bitboard fromToBB = fromBB | toBB;

   pieces_[c][p]   ^= fromToBB;
   colours_[c]     ^= fromToBB;
   pieces_[cc][pc] ^= toBB;
   colours_[cc]    ^= toBB;
   occupied_       ^= fromBB;
   empty_          ^= fromBB;

   assert(!isOccupied(from));
   assert(!isPieceAt(from, p, c));
   assert(isOccupied(to));
   assert(isPieceAt(to, p, c));
}

//=============================================================================
void BBoard::move(Square from, Square to, PieceType p, Color c)
{
   assert(isOccupied(from));
   assert(isPieceAt(from, p, c));
   assert(!isOccupied(to));
   assert(!isPieceAt(to, p, c));

   const Bitboard fromToBB = Bitboard::fromSquare(from) | Bitboard::fromSquare(to);

   pieces_[c][p] ^= fromToBB;
   colours_[c]   ^= fromToBB;
   occupied_     ^= fromToBB;
   empty_        ^= fromToBB;

   assert(!isOccupied(from));
   assert(!isPieceAt(from, p, c));
   assert(isOccupied(to));
   assert(isPieceAt(to, p, c));
}


}  // namespace Chess
