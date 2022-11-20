#include <gtest/gtest.h>

#include "chess/board.h"

using namespace Chess;

//=============================================================================
TEST(BoardTest, Constructor) 
{
   Board b;
   EXPECT_EQ(b.pieceAt(Sq::a1), PieceType::Rook);
   EXPECT_EQ(b.colourAt(Sq::a1), Colour::White);

   EXPECT_EQ(b.pieceAt(Sq::f2), PieceType::Pawn);
   EXPECT_EQ(b.colourAt(Sq::f2), Colour::White);

   EXPECT_EQ(b.pieceAt(Sq::g5), PieceType::Empty);
   EXPECT_EQ(b.colourAt(Sq::g5), Colour::Empty);

   EXPECT_EQ(b.pieceAt(Sq::e8), PieceType::King);
   EXPECT_EQ(b.colourAt(Sq::e8), Colour::Black);
}

//=============================================================================
TEST(BoardTest, isPieceAt) 
{
   Board b;
   EXPECT_TRUE(b.isPieceAt(Sq::d1));
   EXPECT_TRUE(b.isPieceAt(Sq::h2));
   EXPECT_TRUE(b.isPieceAt(Sq::b7));
   EXPECT_TRUE(b.isPieceAt(Sq::f8));

   EXPECT_FALSE(b.isPieceAt(Sq::c3));
   EXPECT_FALSE(b.isPieceAt(Sq::e6));
}

//=============================================================================
TEST(BoardTest, setEmpty) 
{
   Board b;
   EXPECT_TRUE(b.isPieceAt(Sq::d1));
   b.setEmpty(Sq::d1);
   EXPECT_FALSE(b.isPieceAt(Sq::d1));
}

//=============================================================================
TEST(BoardTest, setPiece) 
{
   Board b;
   b.setEmpty();
   EXPECT_FALSE(b.isPieceAt(Sq::c3));
   b.setPiece(Sq::c3, PieceType::Queen, Colour::Black);
   EXPECT_EQ(b.pieceAt(Sq::c3), PieceType::Queen);
   EXPECT_EQ(b.colourAt(Sq::c3), Colour::Black);
}

//=============================================================================
TEST(BoardTest, move) 
{
   Board b;
   EXPECT_EQ(b.pieceAt(Sq::b1), PieceType::Knight);
   EXPECT_EQ(b.colourAt(Sq::b1), Colour::White);
   EXPECT_FALSE(b.isPieceAt(Sq::c3));
   b.move(Sq::b1, Sq::c3);
   EXPECT_EQ(b.pieceAt(Sq::c3), PieceType::Knight);
   EXPECT_EQ(b.colourAt(Sq::c3), Colour::White);
   EXPECT_FALSE(b.isPieceAt(Sq::b1));
}

//=============================================================================
TEST(BoardTest, setEmptyAll) 
{
   Board b;
   EXPECT_TRUE(b.isPieceAt(Sq::d1));
   EXPECT_TRUE(b.isPieceAt(Sq::h8));
   b.setEmpty();
   EXPECT_FALSE(b.isPieceAt(Sq::d1));
   EXPECT_FALSE(b.isPieceAt(Sq::h8));
}

//=============================================================================
TEST(BoardTest, king) 
{
   Board b;
   EXPECT_EQ(b.WKing(), Sq::e1);
   EXPECT_EQ(b.BKing(), Sq::e8);

   b.move(Sq::e1, Sq::h2);
   b.move(Sq::h2, Sq::h1);
   b.move(Sq::e8, Sq::a8);
   b.move(Sq::a7, Sq::a6);
   EXPECT_EQ(b.WKing(), Sq::h1);
   EXPECT_EQ(b.BKing(), Sq::a8);

   b.setEmpty();
   EXPECT_EQ(b.WKing(), Sq::Invalid);
   EXPECT_EQ(b.BKing(), Sq::Invalid);
}
