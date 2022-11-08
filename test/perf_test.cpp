#include <gtest/gtest.h>

//#define NDEBUG 
#include "test_helper.h"
#include "chess/game.h"

using namespace Chess;

//=============================================================================
TEST(PerfTest, perft1) 
{
   ASSERT_EQ(perft(0), 1);
   ASSERT_EQ(perft(1), 20);
   ASSERT_EQ(perft(2), 400);
   ASSERT_EQ(perft(3), 8902);
   ASSERT_EQ(perft(4), 197281);
   // ASSERT_EQ(perft(5), 4865609);  // ~4 s
   // ASSERT_EQ(perft(6), 119060324); // ~80 s
   // ASSERT_EQ(perft(7), 3195901860); // ~40 min
}
