#include "bitboard.h"

#include <array>
#include <cassert>

namespace Chess
{

//=============================================================================
// Sources: 
// https://www.chessprogramming.org/General_Setwise_Operations
// https://www.chessprogramming.org/BitScan
// https://www.chessprogramming.org/Population_Count

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

constexpr std::array<uint64_t, NUM_SQUARES> bitscanIndexes = {
   0,  47, 1,  56, 48, 27, 2,  60,
   57, 49, 41, 37, 28, 16, 3,  61,
   54, 58, 35, 52, 50, 42, 21, 44,
   38, 32, 29, 23, 17, 11, 4,  62,
   46, 55, 26, 59, 40, 36, 15, 53,
   34, 51, 20, 43, 31, 22, 10, 45,
   25, 39, 14, 33, 19, 30, 9,  24,
   13, 18, 8,  12, 7,  6,  5,  63
};

//=============================================================================
bool Bitboard::test(Square sq) const
{
   return board_ & squareMask[sq];
}

//=============================================================================
std::size_t Bitboard::count() const
{
   std::size_t count = 0;
   uint64_t t = board_;
   while (t)
   {
      count++;
      t &= (t - 1); // Reset LS1B
   }
   return count;
}

//=============================================================================
void Bitboard::set(Square sq)
{
   board_ |= squareMask[sq];
}

//=============================================================================
void Bitboard::reset(Square sq)
{
   board_ &= ~squareMask[sq];
}

//=============================================================================
void Bitboard::toggle(Square sq)
{
   board_ ^= squareMask[sq];
}

//=============================================================================
Square Bitboard::Iterator::operator*() const
{  
   assert(state_ != 0);

   // Return position of LS1B using math/magic
   static const uint64_t debruijn64 = 0x03f79d71b4cb0a89ull;
   return bitscanIndexes[((state_ ^ (state_ - 1)) * debruijn64) >> 58];
}

//=============================================================================
void Bitboard::Iterator::operator++()
{  
   assert(state_ != 0);

   state_ &= (state_ - 1); // Reset LS1B
}

}  // namespace Chess
