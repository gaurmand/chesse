#include <gtest/gtest.h>

#include "chess/attacks.h"

using namespace Chess;

//=============================================================================
TEST(AttacksTest, knightAttacks) 
{
   Bitboard b = Attacks::knight[Sq::a3];
   EXPECT_TRUE(b.test(Sq::b5));
   EXPECT_TRUE(b.test(Sq::c4));
   EXPECT_TRUE(b.test(Sq::c2));
   EXPECT_TRUE(b.test(Sq::b1));

   b = Attacks::knight[Sq::f6];
   EXPECT_TRUE(b.test(Sq::e8));
   EXPECT_TRUE(b.test(Sq::g8));
   EXPECT_TRUE(b.test(Sq::h7));
   EXPECT_TRUE(b.test(Sq::h5));
   EXPECT_TRUE(b.test(Sq::g4));
   EXPECT_TRUE(b.test(Sq::e4));
   EXPECT_TRUE(b.test(Sq::d5));
   EXPECT_TRUE(b.test(Sq::d7));
}

//=============================================================================
TEST(AttacksTest, kingAttacks) 
{
   Bitboard b = Attacks::king[Sq::a8];
   EXPECT_TRUE(b.test(Sq::a7));
   EXPECT_TRUE(b.test(Sq::b7));
   EXPECT_TRUE(b.test(Sq::b8));

   b = Attacks::king[Sq::d2];
   EXPECT_TRUE(b.test(Sq::c3));
   EXPECT_TRUE(b.test(Sq::d3));
   EXPECT_TRUE(b.test(Sq::e3));
   EXPECT_TRUE(b.test(Sq::e2));
   EXPECT_TRUE(b.test(Sq::e1));
   EXPECT_TRUE(b.test(Sq::d1));
   EXPECT_TRUE(b.test(Sq::c1));
   EXPECT_TRUE(b.test(Sq::c2));
}

//=============================================================================
TEST(AttacksTest, pawnAttacks) 
{
   Bitboard b = Attacks::pawn[Color::White][Sq::b7];
   EXPECT_TRUE(b.test(Sq::a8));
   EXPECT_TRUE(b.test(Sq::c8));

   b = Attacks::pawn[Color::Black][Sq::b7];
   EXPECT_TRUE(b.test(Sq::a6));
   EXPECT_TRUE(b.test(Sq::c6));

   b = Attacks::pawn[Color::White][Sq::f4];
   EXPECT_TRUE(b.test(Sq::e5));
   EXPECT_TRUE(b.test(Sq::g5));

   b = Attacks::pawn[Color::Black][Sq::f4];
   EXPECT_TRUE(b.test(Sq::e3));
   EXPECT_TRUE(b.test(Sq::g3));
}

//=============================================================================
TEST(AttacksTest, pawnPushes) 
{
   Bitboard b = Attacks::pawnPush[Color::White][Sq::b7];
   EXPECT_TRUE(b.test(Sq::b8));

   b = Attacks::pawnPush[Color::Black][Sq::b7];
   EXPECT_TRUE(b.test(Sq::b6));

   b = Attacks::pawnPush[Color::White][Sq::f4];
   EXPECT_TRUE(b.test(Sq::f5));

   b = Attacks::pawnPush[Color::Black][Sq::f4];
   EXPECT_TRUE(b.test(Sq::f3));
}

//=============================================================================
TEST(AttacksTest, pawnDoublePushes) 
{
   Bitboard b = Attacks::pawnDPush[Color::White][Sq::b7];
   EXPECT_TRUE(b.none());

   b = Attacks::pawnDPush[Color::Black][Sq::b7];
   EXPECT_TRUE(b.test(Sq::b5));

   b = Attacks::pawnDPush[Color::White][Sq::f4];
   EXPECT_TRUE(b.none());

   b = Attacks::pawnDPush[Color::Black][Sq::f4];
   EXPECT_TRUE(b.none());

   b = Attacks::pawnDPush[Color::White][Sq::c2];
   EXPECT_TRUE(b.test(Sq::c4));
}

//=============================================================================
TEST(AttacksTest, rayAttacks) 
{
   Bitboard b = Attacks::ray[N][Sq::c6];
   EXPECT_FALSE(b.test(Sq::c6));
   EXPECT_TRUE(b.test(Sq::c7));
   EXPECT_TRUE(b.test(Sq::c8));

   b = Attacks::ray[E][Sq::f6];
   EXPECT_FALSE(b.test(Sq::f6));
   EXPECT_TRUE(b.test(Sq::g6));
   EXPECT_TRUE(b.test(Sq::h6));

   b = Attacks::ray[S][Sq::g1];
   EXPECT_TRUE(b.none());

   b = Attacks::ray[W][Sq::h2];
   EXPECT_FALSE(b.test(Sq::h2));
   EXPECT_TRUE(b.test(Sq::g2));
   EXPECT_TRUE(b.test(Sq::f2));
   EXPECT_TRUE(b.test(Sq::e2));
   EXPECT_TRUE(b.test(Sq::d2));
   EXPECT_TRUE(b.test(Sq::c2));
   EXPECT_TRUE(b.test(Sq::b2));
   EXPECT_TRUE(b.test(Sq::a2));

   b = Attacks::ray[NW][Sq::b2];
   EXPECT_FALSE(b.test(Sq::b2));
   EXPECT_TRUE(b.test(Sq::a3));

   b = Attacks::ray[NE][Sq::b4];
   EXPECT_FALSE(b.test(Sq::b4));
   EXPECT_TRUE(b.test(Sq::c5));
   EXPECT_TRUE(b.test(Sq::d6));
   EXPECT_TRUE(b.test(Sq::e7));
   EXPECT_TRUE(b.test(Sq::f8));

   b = Attacks::ray[SE][Sq::e8];
   EXPECT_FALSE(b.test(Sq::e8));
   EXPECT_TRUE(b.test(Sq::f7));
   EXPECT_TRUE(b.test(Sq::g6));
   EXPECT_TRUE(b.test(Sq::h5));

   b = Attacks::ray[SW][Sq::h8];
   EXPECT_FALSE(b.test(Sq::h8));
   EXPECT_TRUE(b.test(Sq::g7));
   EXPECT_TRUE(b.test(Sq::f6));
   EXPECT_TRUE(b.test(Sq::e5));
   EXPECT_TRUE(b.test(Sq::d4));
   EXPECT_TRUE(b.test(Sq::c3));
   EXPECT_TRUE(b.test(Sq::b2));
   EXPECT_TRUE(b.test(Sq::a1));
}
