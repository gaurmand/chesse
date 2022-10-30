#include <gtest/gtest.h>

#include "chess/board.h"

using Chess::Board, Chess::Sq, Chess::Piece, Chess::Colour;

//=============================================================================
TEST(BoardTest, Constructor) 
{
   Board b;
   EXPECT_EQ(b.pieceAt(Sq::a1), Piece::Rook);
   EXPECT_EQ(b.colourAt(Sq::a1), Colour::White);

   EXPECT_EQ(b.pieceAt(Sq::f2), Piece::Pawn);
   EXPECT_EQ(b.colourAt(Sq::f2), Colour::White);

   EXPECT_EQ(b.pieceAt(Sq::g5), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::g5), Colour::Empty);

   EXPECT_EQ(b.pieceAt(Sq::e8), Piece::King);
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
   EXPECT_FALSE(b.isPieceAt(Sq::c3));
   b.setPiece(Sq::c3, Piece::Queen, Colour::Black);
   EXPECT_EQ(b.pieceAt(Sq::c3), Piece::Queen);
   EXPECT_EQ(b.colourAt(Sq::c3), Colour::Black);
}

//=============================================================================
TEST(BoardTest, move) 
{
   Board b;
   EXPECT_EQ(b.pieceAt(Sq::b1), Piece::Knight);
   EXPECT_EQ(b.colourAt(Sq::b1), Colour::White);
   EXPECT_FALSE(b.isPieceAt(Sq::c3));
   b.move(Sq::b1, Sq::c3);
   EXPECT_EQ(b.pieceAt(Sq::c3), Piece::Knight);
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
