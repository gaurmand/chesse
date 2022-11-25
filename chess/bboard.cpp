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
