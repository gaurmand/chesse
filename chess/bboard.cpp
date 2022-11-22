#include "bboard.h"

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
   empty_.clear();
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


}  // namespace Chess
