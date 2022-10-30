#include <gtest/gtest.h>

#include "chess/state.h"

using Chess::StateStruct, Chess::State, Chess::Sq, Chess::toState, Chess::fromState;

//=============================================================================
TEST(StateTest, DefaultConstructor) 
{
   StateStruct s;
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
   StateStruct s;
   EXPECT_EQ(toState(s), 0x1F4000000000);

   s.fullMoveClock_ = 0x1010;
   s.halfMoveClock_ = 0x0F0F;
   s.enPassantSquare_ = 0xAA;
   s.flags_ = 0x1B;
   EXPECT_EQ(toState(s), 0x1BAA0F0F1010);
}

//=============================================================================
TEST(StateTest, fromState) 
{
   StateStruct s;
   StateStruct t;
   fromState(0x1F4000000000, t);
   EXPECT_EQ(t, s);

   s.fullMoveClock_ = 0x1010;
   s.halfMoveClock_ = 0x0F0F;
   s.enPassantSquare_ = 0xAA;
   s.flags_ = 0x1B;
   fromState(0x1BAA0F0F1010, t);
   EXPECT_EQ(t, s);
}