#include <gtest/gtest.h>

#include "chess/state.h"

using Chess::State, Chess::State, Chess::Colour, Chess::Sq, Chess::toStateInt, Chess::fromStateInt;

//=============================================================================
TEST(StateTest, DefaultConstructor) 
{
   State s;
   EXPECT_EQ(s.activeColour_, Colour::White);
   EXPECT_TRUE(s.canWhiteShortCastle_);
   EXPECT_TRUE(s.canWhiteLongCastle_);
   EXPECT_TRUE(s.canBlackShortCastle_);
   EXPECT_TRUE(s.canBlackLongCastle_);
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
   s.canWhiteLongCastle_ = false;
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
   s.canWhiteLongCastle_ = false;
   fromStateInt(0x1BAA0F0F1010, t);
   EXPECT_EQ(t, s);
}