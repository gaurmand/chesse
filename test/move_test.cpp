#include <gtest/gtest.h>

#include "chess/move.h"

using Chess::Move, Chess::MoveInt, Chess::Sq, Chess::Piece, Chess::MoveType, Chess::toMoveInt, Chess::fromMoveInt;

//=============================================================================
TEST(MoveTest, DefaultConstructor) 
{
   Move m;
   EXPECT_EQ(m.from_, Sq::Invalid);
   EXPECT_EQ(m.to_, Sq::Invalid);
   EXPECT_EQ(m.type_, MoveType::Invalid);
   EXPECT_EQ(m.capture_, Piece::Empty);
}

//=============================================================================
TEST(MoveTest, toMove) 
{
   Move m;
   EXPECT_EQ(toMoveInt(m), 0x40400000);

   m.from_ = 0x0A;
   m.to_ = 0x2F;
   m.type_ = MoveType::QueenPromotion;
   m.capture_ = Piece::Rook;
   EXPECT_EQ(toMoveInt(m), 0x0A2F0903);
}

//=============================================================================
TEST(MoveTest, fromMove) 
{
   Move m;
   Move t;
   fromMoveInt(0x40400000, t);
   EXPECT_EQ(t, m);

   m.from_ = 0x0A;
   m.to_ = 0x2F;
   m.type_ = MoveType::QueenPromotion;
   m.capture_ = Piece::Rook;
   fromMoveInt(0x0A2F0903, t);
   EXPECT_EQ(t, m);
}