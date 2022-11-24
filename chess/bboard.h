#ifndef CHESS_BBOARD_H
#define CHESS_BBOARD_H

#include "bitboard.h"
#include "common.h"

#include <array>

namespace Chess
{

class BBoard
{
public:
   //==========================================================================
   BBoard() { setDefault(); }

   //==========================================================================
   void setEmpty();
   void setDefault();

   //==========================================================================
   bool isOccupied(Square sq) const { return occupied_.test(sq); }
   bool isColourAt(Square sq, Color c) const { return colours_[c].test(sq); }
   bool isPieceAt(Square sq, PieceType p) const { 
      return pieces_[Color::White][p].test(sq) || 
             pieces_[Color::Black][p].test(sq); 
   }
   bool isPieceAt(Square sq, PieceType p, Color c) const { 
      return pieces_[c][p].test(sq); 
   }

   //==========================================================================
   Color colourAt(Square sq) const;
   PieceType pieceAt(Square sq) const;

   //==========================================================================
   Bitboard pieces(Color c, PieceType p) const { return pieces_[c][p]; }
   Bitboard pieces(Color c) const { return colours_[c]; }
   Bitboard pieces(PieceType p) const { 
      return pieces_[Color::White][p] | 
             pieces_[Color::Black][p]; 
   }

   //==========================================================================
   void clear(Square sq, PieceType p, Color c);
   void set(Square sq, PieceType p, Color c);
   void promote(Square sq, PieceType from, PieceType to, Color c);
   void move(Square from, Square to, PieceType p, Color c);
   void capture(Square from, Square to, PieceType p, PieceType pc, Color c, Color cc);

protected:
   //==========================================================================
   std::array<std::array<Bitboard, kNumPieceTypes>, kNumColors> pieces_;
   std::array<Bitboard, kNumColors> colours_;
   Bitboard occupied_;
   Bitboard empty_;
};

}  // namespace Chess

#endif   // CHESS_BBOARD_H