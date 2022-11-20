#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "common.h"
#include "square.h"

#include <array>
#include <cassert>

namespace Chess
{

constexpr int NUM_PIECES_PER_SIDE    = 16;
constexpr int NUM_PIECES   = 2 * NUM_PIECES_PER_SIDE;

using PieceIndex = int8_t ;
constexpr PieceIndex kInvalidIndex = -1;

//=============================================================================
class PieceSet
{
public:
   class Iterator
   {
   public:
      Iterator(const PieceSet& set, PieceIndex curr): set_(set), curr_(curr) {}
      Square operator*() const { return set_[curr_]; }
      void operator++() { curr_++; }
      bool operator==(const Iterator& rhs) const { return curr_ == rhs.curr_; }
      bool operator!=(const Iterator& rhs) const { return !(*this == rhs); }
   private:
      const PieceSet& set_;
      PieceIndex curr_; 
   };

   //==========================================================================
   PieceSet(Colour c) { c == Colour::White ? setWDefault() : setBDefault(); };

   //==========================================================================
   Square operator[](size_t idx) const { return pieces_[idx]; }

   //==========================================================================
   void setEmpty()
   {
      indexes_.fill(kInvalidIndex);
      pieces_.fill(Sq::Invalid);
      numPieces_ = 0;
   }

   //==========================================================================
   void setWDefault()
   {
      const PieceIndex I = kInvalidIndex;
      indexes_ = {
         0,  1,  2,  3,  4,  5,  6,  7,
         8,  9,  10, 11, 12, 13, 14, 15,
         I,  I,  I,  I,  I,  I,  I,  I,
         I,  I,  I,  I,  I,  I,  I,  I,
         I,  I,  I,  I,  I,  I,  I,  I,
         I,  I,  I,  I,  I,  I,  I,  I,
         I,  I,  I,  I,  I,  I,  I,  I,
         I,  I,  I,  I,  I,  I,  I,  I
      };

      pieces_ = {
         Sq::a1, Sq::b1, Sq::c1, Sq::d1, Sq::e1, Sq::f1, Sq::g1, Sq::h1,
         Sq::a2, Sq::b2, Sq::c2, Sq::d2, Sq::e2, Sq::f2, Sq::g2, Sq::h2
      };
   }

   //==========================================================================
   void setBDefault()
   {
      const PieceIndex I = kInvalidIndex;
      indexes_ = {
         I,  I,  I,  I,  I,  I,  I,  I,
         I,  I,  I,  I,  I,  I,  I,  I,
         I,  I,  I,  I,  I,  I,  I,  I,
         I,  I,  I,  I,  I,  I,  I,  I,
         I,  I,  I,  I,  I,  I,  I,  I,
         I,  I,  I,  I,  I,  I,  I,  I,
         0,  1,  2,  3,  4,  5,  6,  7,
         8,  9,  10, 11, 12, 13, 14, 15
      };
      
      pieces_ = {
         Sq::a7, Sq::b7, Sq::c7, Sq::d7, Sq::e7, Sq::f7, Sq::g7, Sq::h7,
         Sq::a8, Sq::b8, Sq::c8, Sq::d8, Sq::e8, Sq::f8, Sq::g8, Sq::h8
      };
   }

   //==========================================================================
   bool contains(Square sq)
   {
      return indexes_[sq] != kInvalidIndex;
   }

   //==========================================================================
   void insert(Square sq)
   {
      assert(numPieces_ >= 0 && numPieces_ < NUM_PIECES_PER_SIDE);

      PieceIndex newIdx = last() + 1;
      pieces_[newIdx]   = sq;
      indexes_[sq]      = newIdx;
      numPieces_++;
   }

   //==========================================================================
   void replace(Square from, Square to)
   {
      assert(numPieces_ >= 0 && numPieces_ <= NUM_PIECES_PER_SIDE);

      const PieceIndex idx = indexes_[from];
      pieces_[idx]         = to;
      indexes_[to]         = idx;
      indexes_[from]       = kInvalidIndex;
   }

   //==========================================================================
   void remove(Square sq)
   {
      assert(numPieces_ > 0 && numPieces_ <= NUM_PIECES_PER_SIDE);

      const PieceIndex idx     = indexes_[sq];
      const PieceIndex lastIdx = last();
      const Square lastSq      = pieces_[lastIdx];
      std::swap(pieces_[idx], pieces_[lastIdx]);
      indexes_[sq]     = kInvalidIndex;
      indexes_[lastSq] = idx;
      numPieces_--;
   }

   //==========================================================================
   Iterator begin() const { return Iterator(*this, 0); }
   Iterator end() const { return Iterator(*this, numPieces_); }

private:
   //==========================================================================
   PieceIndex first() const { return 0; }
   PieceIndex last() const { return numPieces_ - 1; }

   //==========================================================================
   int numPieces_ = NUM_PIECES_PER_SIDE;
   std::array<PieceIndex, NUM_SQUARES> indexes_;
   std::array<Square, NUM_PIECES_PER_SIDE> pieces_;
};

//=============================================================================
class Board
{
public:
   //==========================================================================
   Board();

   //==========================================================================
   PieceType pieceAt(Square sqr) const { return board_[sqr]; }
   bool isPieceAt(Square sqr) const { return board_[sqr] != PieceType::Empty; }
   bool isPieceAt(Square sqr, PieceType piece) const { return board_[sqr] == piece; }

   //==========================================================================
   Colour colourAt(Square sqr) const { return colour_[sqr]; }
   bool isColourAt(Square sqr, Colour colour) const { return colour_[sqr] == colour; }

   //==========================================================================
   void setEmpty(Square sqr);
   void setPiece(Square sqr, PieceType piece, Colour color);
   void promote(Square sqr, PieceType piece);
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

   //==========================================================================
   PieceSet::Iterator piecesBegin(Colour c) const { return c == Colour::White ? wPieces_.begin() : bPieces_.begin(); }
   PieceSet::Iterator piecesEnd(Colour c) const { return c == Colour::White ? wPieces_.end() : bPieces_.end(); }

   //==========================================================================
   void updateKings();

private:
   //==========================================================================
   void updateKing(Square to);

   //==========================================================================
   std::array<PieceType, NUM_SQUARES> board_;
   std::array<Colour, NUM_SQUARES> colour_;
   Square WKing_ = Sq::e1;
   Square BKing_ = Sq::e8;
   PieceSet wPieces_ = PieceSet(Colour::White);
   PieceSet bPieces_ = PieceSet(Colour::Black);
};

}  // namespace Chess



#endif   // CHESS_BOARD_H