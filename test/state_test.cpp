#include <gtest/gtest.h>

#include "chess/state.h"

using namespace Chess;

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

//=============================================================================
TEST(StateTest, fen1) 
{
   State s = fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
   EXPECT_EQ(s.active_, Colour::White);
   EXPECT_EQ(s.inactive_, Colour::Black);
   EXPECT_TRUE(s.canWhiteShortCastle_);
   EXPECT_TRUE(s.canWhiteLongCastle_);
   EXPECT_TRUE(s.canBlackShortCastle_);
   EXPECT_TRUE(s.canBlackLongCastle_);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 1);
}

//=============================================================================
TEST(StateTest, fen2) 
{
   State s = fromFEN("r3kb1N/Q1qn2p1/8/1pP4p/3Pp1b1/1P2P3/1P3P2/3RK2R w Kq b6 0 18");
   EXPECT_EQ(s.active_, Colour::White);
   EXPECT_EQ(s.inactive_, Colour::Black);
   EXPECT_TRUE(s.canWhiteShortCastle_);
   EXPECT_FALSE(s.canWhiteLongCastle_);
   EXPECT_FALSE(s.canBlackShortCastle_);
   EXPECT_TRUE(s.canBlackLongCastle_);
   EXPECT_EQ(s.enPassantSquare_, Sq::b6);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 18);
}

//=============================================================================
TEST(StateTest, fen3) 
{
   State s = fromFEN("r3k2r/2P5/7b/8/8/Q7/7n/R3K2R b KQkq - 2 35");
   EXPECT_EQ(s.active_, Colour::Black);
   EXPECT_EQ(s.inactive_, Colour::White);
   EXPECT_TRUE(s.canWhiteShortCastle_);
   EXPECT_TRUE(s.canWhiteLongCastle_);
   EXPECT_TRUE(s.canBlackShortCastle_);
   EXPECT_TRUE(s.canBlackLongCastle_);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 2);
   EXPECT_EQ(s.fullMoveClock_, 35);
}