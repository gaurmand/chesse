#ifndef CHESS_BITBOARD_H
#define CHESS_BITBOARD_H

#include "square.h"

#include <cstdint>

namespace Chess
{

constexpr uint64_t kEmptyBoard = 0;
constexpr uint64_t kFullBoard  = 0xFFFFFFFFFFFFFFFFull;

class Bitboard
{
public:
   //==========================================================================
   Bitboard(uint64_t b): board_(b) {}

   //==========================================================================
   uint64_t to_uint() const { return board_; }

   //==========================================================================
   bool operator==(const Bitboard& r) const { return board_ == r.board_; }
   bool operator!=(const Bitboard& r) const { return board_ != r.board_; }

   //==========================================================================
   Bitboard operator|(const Bitboard& rhs) const { return board_ | rhs.board_; }
   Bitboard operator&(const Bitboard& rhs) const { return board_ & rhs.board_; }
   Bitboard operator^(const Bitboard& rhs) const { return board_ ^ rhs.board_; }
   Bitboard operator~() const { return ~board_; }

   //==========================================================================
   Bitboard& operator|=(const Bitboard& rhs) { board_ |= rhs.board_; return *this; }
   Bitboard& operator&=(const Bitboard& rhs) { board_ &= rhs.board_; return *this; }
   Bitboard& operator^=(const Bitboard& rhs) { board_ ^= rhs.board_; return *this; }
   Bitboard& flip() { board_ = ~board_; return *this; }

   //==========================================================================
   bool test(Square sq) const;
   std::size_t count() const;

   //==========================================================================
   bool any() const { return board_ != kEmptyBoard; }
   bool none() const { return board_ == kEmptyBoard; }
   bool all() const { return board_ == kFullBoard; }

   //==========================================================================
   void set(Square sq);
   void reset(Square sq);
   void toggle(Square sq);

   //==========================================================================
   class Iterator
   {
   public:
      Iterator(uint64_t init) : state_(init) {}
      Square operator*() const;
      void operator++();
      bool operator==(const Iterator& r) const { return state_ == r.state_; }
      bool operator!=(const Iterator& r) const { return state_ != r.state_; }
   private:
      uint64_t state_;
   };

   //==========================================================================
   Iterator begin() const { return Iterator(board_); }
   Iterator end() const { return Iterator(kEmptyBoard); }

private:
   //==========================================================================
   uint64_t board_;
};

}  // namespace Chess

#endif   // CHESS_BITBOARD_H