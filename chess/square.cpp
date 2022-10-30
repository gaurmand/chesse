#include "square.h"
#include "common.h"

#include <map>
#include <array>
#include <stdexcept>

namespace Chess
{

Square fromAN(const AN& squareStr)
{
   static const std::map<char, int> rankToRow = {{'1', 0}, {'2', 1}, {'3', 2}, {'4', 3}, {'5', 4}, {'6', 5}, {'7', 6}, {'8', 7}};
   static const std::map<char, int> fileToCol = {{'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}};

   const char rank = squareStr.at(1);
   const char file = squareStr.at(0);
   const int row   = rankToRow.at(rank);
   const int col   = fileToCol.at(file);

   return row * NUM_COLS + col;
}

AN toAN(Square sqr)
{
   static const std::array<char, 8> rowToRank = {'1', '2', '3', '4', '5', '6', '7', '8'};
   static const std::array<char, 8> colToFile = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

   if (sqr >= NUM_SQUARES)
   {
      throw std::invalid_argument("sqr is outside the valid range");
   }
   const int row   = sqr / NUM_COLS;
   const int col   = sqr % NUM_COLS;
   const char rank = rowToRank.at(row);
   const char file = colToFile.at(col);

   return AN{file, rank};
}


} // namespace Chess
