#include "bitboard.h"

#include <cassert>

namespace Chess
{

//=============================================================================
// Sources: 
// https://www.chessprogramming.org/General_Setwise_Operations
// https://www.chessprogramming.org/BitScan
// https://www.chessprogramming.org/Population_Count

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
