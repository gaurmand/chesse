#include <gtest/gtest.h>

#include "chess/state.h"

using Chess::State, Chess::State, Chess::Sq, Chess::toStateInt, Chess::fromStateInt;

//=============================================================================
TEST(StateTest, DefaultConstructor) 
{
   State s;
   EXPECT_TRUE(s.flags_.test(0));
   EXPECT_TRUE(s.flags_.test(1));
   EXPECT_TRUE(s.flags_.test(2));
   EXPECT_TRUE(s.flags_.test(3));
   EXPECT_TRUE(s.flags_.test(4));
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 0);
}

//=============================================================================
TEST(StateTest, toState) 
{
   State s;
   EXPECT_EQ(toStateInt(s), 0x1F4000000000);

   s.fullMoveClock_ = 0x1010;
   s.halfMoveClock_ = 0x0F0F;
   s.enPassantSquare_ = 0xAA;
   s.flags_ = 0x1B;
   EXPECT_EQ(toStateInt(s), 0x1BAA0F0F1010);
}

//=============================================================================
TEST(StateTest, fromState) 
{
   State s;
   State t;
   fromStateInt(0x1F4000000000, t);
   EXPECT_EQ(t, s);

   s.fullMoveClock_ = 0x1010;
   s.halfMoveClock_ = 0x0F0F;
   s.enPassantSquare_ = 0xAA;
   s.flags_ = 0x1B;
   fromStateInt(0x1BAA0F0F1010, t);
   EXPECT_EQ(t, s);
}