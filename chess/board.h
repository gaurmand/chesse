#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "common.h"
#include "square.h"

#include <array>

namespace Chess
{

class Board
{
public:
   //==========================================================================
   Board();

   //==========================================================================
   Piece pieceAt(Square sqr) const { return board_[sqr]; }
   bool isPieceAt(Square sqr) const { return board_[sqr] != Piece::Empty; }
   bool isPieceAt(Square sqr, Piece piece) const { return board_[sqr] == piece; }

   //==========================================================================
   Colour colourAt(Square sqr) const { return colour_[sqr]; }
   bool isColourAt(Square sqr, Colour colour) const { return colour_[sqr] == colour; }

   //==========================================================================
   void setEmpty(Square sqr);
   void setPiece(Square sqr, Piece piece, Colour color);
   void move(Square from, Square to);

   //==========================================================================
   void setEmpty();
   void setDefault();

   //==========================================================================
   bool operator==(const Board&) const;
   bool operator!=(const Board&) const;

   //==========================================================================
   Square WKing() const { return WKing_; }
   Square BKing() const { return BKing_; }

private:
   //==========================================================================
   void updateKing(Square to);

   //==========================================================================
   std::array<Piece, NUM_SQUARES> board_;
   std::array<Colour, NUM_SQUARES> colour_;
   Square WKing_ = Sq::e1;
   Square BKing_ = Sq::e8;
};

}  // namespace Chess



#endif   // CHESS_BOARD_H