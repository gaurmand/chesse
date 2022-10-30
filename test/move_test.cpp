#include <gtest/gtest.h>

#include "chess/move.h"

using Chess::Move, Chess::MoveInt, Chess::Sq, Chess::MoveType, Chess::toMoveInt, Chess::fromMoveInt;

//=============================================================================
TEST(MoveTest, DefaultConstructor) 
{
   Move m;
   EXPECT_EQ(m.from_, Sq::Invalid);
   EXPECT_EQ(m.to_, Sq::Invalid);
   EXPECT_EQ(m.type_, MoveType::Invalid);
}

//=============================================================================
TEST(MoveTest, toMove) 
{
   Move m;
   EXPECT_EQ(toMoveInt(m), 0x404000);

   m.from_ = 0x0A;
   m.to_ = 0x2F;
   m.type_ = MoveType::CaptureBishop;
   EXPECT_EQ(toMoveInt(m), 0x0A2F04);
}

//=============================================================================
TEST(MoveTest, fromMove) 
{
   Move m;
   Move t;
   fromMoveInt(0x404000, t);
   EXPECT_EQ(t, m);

   m.from_ = 0x0A;
   m.to_ = 0x2F;
   m.type_ = MoveType::CaptureBishop;
   fromMoveInt(0x0A2F04, t);
   EXPECT_EQ(t, m);
}