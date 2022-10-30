#include <gtest/gtest.h>

#include "chess/square.h"

//=============================================================================
TEST(SquareTest, toAN) 
{
   EXPECT_EQ(Chess::toAN(0), Chess::AN("a1"));
   EXPECT_EQ(Chess::toAN(12), Chess::AN("e2"));
   EXPECT_EQ(Chess::toAN(37), Chess::AN("f5"));
   EXPECT_EQ(Chess::toAN(63), Chess::AN("h8"));
}

//=============================================================================
TEST(SquareTest, fromAN) 
{
   EXPECT_EQ(Chess::fromAN("a1"), Chess::Square(0));
   EXPECT_EQ(Chess::fromAN("e2"), Chess::Square(12));
   EXPECT_EQ(Chess::fromAN("f5"), Chess::Square(37));
   EXPECT_EQ(Chess::fromAN("h8"), Chess::Square(63));
}
