#ifndef CHESS_BITBOARD_H
#define CHESS_BITBOARD_H

#include "square.h"

#include <cstdint>
#include <array>

namespace Chess
{

constexpr uint64_t kEmptyBoard = 0;
constexpr uint64_t kFullBoard  = 0xFFFFFFFFFFFFFFFFull;

constexpr std::array<uint64_t, NUM_SQUARES> squareMask = {
   1ull << 0,  1ull << 1,  1ull << 2,  1ull << 3,  1ull << 4,  1ull << 5,  1ull << 6,  1ull << 7,
   1ull << 8,  1ull << 9,  1ull << 10, 1ull << 11, 1ull << 12, 1ull << 13, 1ull << 14, 1ull << 15, 
   1ull << 16, 1ull << 17, 1ull << 18, 1ull << 19, 1ull << 20, 1ull << 21, 1ull << 22, 1ull << 23, 
   1ull << 24, 1ull << 25, 1ull << 26, 1ull << 27, 1ull << 28, 1ull << 29, 1ull << 30, 1ull << 31, 
   1ull << 32, 1ull << 33, 1ull << 34, 1ull << 35, 1ull << 36, 1ull << 37, 1ull << 38, 1ull << 39, 
   1ull << 40, 1ull << 41, 1ull << 42, 1ull << 43, 1ull << 44, 1ull << 45, 1ull << 46, 1ull << 47, 
   1ull << 48, 1ull << 49, 1ull << 50, 1ull << 51, 1ull << 52, 1ull << 53, 1ull << 54, 1ull << 55, 
   1ull << 56, 1ull << 57, 1ull << 58, 1ull << 59, 1ull << 60, 1ull << 61, 1ull << 62, 1ull << 63
};

class Bitboard
{
public:
   //==========================================================================
   constexpr Bitboard(): board_(kEmptyBoard) {}
   constexpr Bitboard(uint64_t b): board_(b) {}

   //==========================================================================
   static Bitboard fromSquare(Square sq) { return Bitboard(squareMask[sq]); }

   //==========================================================================
   constexpr uint64_t to_uint() const { return board_; }

   //==========================================================================
   constexpr bool operator==(const Bitboard& r) const { return board_ == r.board_; }
   constexpr bool operator!=(const Bitboard& r) const { return board_ != r.board_; }

   //==========================================================================
   constexpr Bitboard operator|(const Bitboard& rhs) const { return board_ | rhs.board_; }
   constexpr Bitboard operator&(const Bitboard& rhs) const { return board_ & rhs.board_; }
   constexpr Bitboard operator^(const Bitboard& rhs) const { return board_ ^ rhs.board_; }
   constexpr Bitboard operator~() const { return ~board_; }

   //==========================================================================
   constexpr Bitboard& operator|=(const Bitboard& rhs) { board_ |= rhs.board_; return *this; }
   constexpr Bitboard& operator&=(const Bitboard& rhs) { board_ &= rhs.board_; return *this; }
   constexpr Bitboard& operator^=(const Bitboard& rhs) { board_ ^= rhs.board_; return *this; }
   constexpr Bitboard& flip() { board_ = ~board_; return *this; }

   //==========================================================================
   constexpr bool test(Square sq) const { return board_ & squareMask[sq]; }
   std::size_t count() const;

   //==========================================================================
   constexpr bool any() const { return board_ != kEmptyBoard; }
   constexpr bool none() const { return board_ == kEmptyBoard; }
   constexpr bool all() const { return board_ == kFullBoard; }

   //==========================================================================
   constexpr void set(Square sq) { board_ |= squareMask[sq]; }
   constexpr void reset(Square sq) { board_ &= ~squareMask[sq]; }
   constexpr void toggle(Square sq) { board_ ^= squareMask[sq]; }

   //==========================================================================
   constexpr void clear() { board_ = kEmptyBoard; }
   constexpr void fill() { board_  = kFullBoard; }

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