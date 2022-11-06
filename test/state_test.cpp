#include <gtest/gtest.h>

#include "chess/state.h"

using Chess::State, Chess::State, Chess::Colour, Chess::Sq, Chess::toStateInt, Chess::fromStateInt;

//=============================================================================
TEST(StateTest, DefaultConstructor) 
{
   State s;
   EXPECT_EQ(s.active_, Colour::White);
   EXPECT_EQ(s.inactive_, Colour::Black);
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
   EXPECT_EQ(toStateInt(s), 0xFA000000);

   s.fullMoveClock_ = 0x61;
   s.halfMoveClock_ = 0xA8;
   s.enPassantSquare_ = 0x2B;
   s.canBlackShortCastle_ = false;
   s.canWhiteLongCastle_ = false;
   EXPECT_EQ(toStateInt(s), 0xC95AA061);
}

//=============================================================================
TEST(StateTest, fromState) 
{
   State s;
   State t;
   fromStateInt(0xFA000000, t);
   EXPECT_EQ(t, s);

   s.fullMoveClock_ = 0x61;
   s.halfMoveClock_ = 0xA8;
   s.enPassantSquare_ = 0x2B;
   s.canBlackShortCastle_ = false;
   s.canWhiteLongCastle_ = false;
   fromStateInt(0xC95AA061, t);
   EXPECT_EQ(t, s);
}