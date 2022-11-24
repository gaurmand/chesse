#include <gtest/gtest.h>

#include "chess/bboard.h"

using namespace Chess;

//=============================================================================
TEST(BBoardTest, Constructor) 
{
   BBoard b;
   EXPECT_EQ(b.pieces(Color::White, PieceType::Pawn), 0x000000000000FF00);
   EXPECT_EQ(b.pieces(Color::Black, PieceType::Queen), 0x0800000000000000);

   b.setEmpty();
   EXPECT_EQ(b.pieces(Color::White, PieceType::Pawn), 0x0);
   EXPECT_EQ(b.pieces(Color::Black, PieceType::Queen), 0x0);
}

//=============================================================================
TEST(BBoardTest, isOccupied) 
{
   BBoard b;
   for (Square sq = Sq::a1; sq <= Sq::h2; ++sq)
   {
      EXPECT_TRUE(b.isOccupied(sq));
   }
   for (Square sq = Sq::a3; sq <= Sq::h6; ++sq)
   {
      EXPECT_FALSE(b.isOccupied(sq));
   }
   for (Square sq = Sq::a7; sq <= Sq::h8; ++sq)
   {
      EXPECT_TRUE(b.isOccupied(sq));
   }
}

//=============================================================================
TEST(BBoardTest, isColourAt) 
{
   BBoard b;
   for (Square sq = Sq::a1; sq <= Sq::h2; ++sq)
   {
      EXPECT_TRUE(b.isColourAt(sq, Color::White));
   }
   for (Square sq = Sq::a3; sq <= Sq::h6; ++sq)
   {
      EXPECT_FALSE(b.isColourAt(sq, Color::White));
      EXPECT_FALSE(b.isColourAt(sq, Color::Black));
   }
   for (Square sq = Sq::a7; sq <= Sq::h8; ++sq)
   {
      EXPECT_TRUE(b.isColourAt(sq, Color::Black));
   }
}

//=============================================================================
TEST(BBoardTest, isPieceAt) 
{
   BBoard b;
   for (Square sq = Sq::a2; sq <= Sq::h2; ++sq)
   {
      EXPECT_TRUE(b.isPieceAt(sq, PieceType::Pawn));
   }
   for (Square sq = Sq::a7; sq <= Sq::h7; ++sq)
   {
      EXPECT_TRUE(b.isPieceAt(sq, PieceType::Pawn));
   }

   EXPECT_TRUE(b.isPieceAt(Sq::a1, PieceType::Rook));
   EXPECT_TRUE(b.isPieceAt(Sq::b1, PieceType::Knight));
   EXPECT_TRUE(b.isPieceAt(Sq::c1, PieceType::Bishop));
   EXPECT_TRUE(b.isPieceAt(Sq::d1, PieceType::Queen));
   EXPECT_TRUE(b.isPieceAt(Sq::e1, PieceType::King));
   EXPECT_TRUE(b.isPieceAt(Sq::f1, PieceType::Bishop));
   EXPECT_TRUE(b.isPieceAt(Sq::g1, PieceType::Knight));
   EXPECT_TRUE(b.isPieceAt(Sq::h1, PieceType::Rook));

   EXPECT_TRUE(b.isPieceAt(Sq::a8, PieceType::Rook));
   EXPECT_TRUE(b.isPieceAt(Sq::b8, PieceType::Knight));
   EXPECT_TRUE(b.isPieceAt(Sq::c8, PieceType::Bishop));
   EXPECT_TRUE(b.isPieceAt(Sq::d8, PieceType::Queen));
   EXPECT_TRUE(b.isPieceAt(Sq::e8, PieceType::King));
   EXPECT_TRUE(b.isPieceAt(Sq::f8, PieceType::Bishop));
   EXPECT_TRUE(b.isPieceAt(Sq::g8, PieceType::Knight));
   EXPECT_TRUE(b.isPieceAt(Sq::h8, PieceType::Rook));

   for (Square sq = Sq::a3; sq <= Sq::h6; ++sq)
   {
      EXPECT_FALSE(b.isPieceAt(sq, PieceType::Pawn));
      EXPECT_FALSE(b.isPieceAt(sq, PieceType::Knight));
      EXPECT_FALSE(b.isPieceAt(sq, PieceType::Bishop));
      EXPECT_FALSE(b.isPieceAt(sq, PieceType::Rook));
      EXPECT_FALSE(b.isPieceAt(sq, PieceType::Queen));
      EXPECT_FALSE(b.isPieceAt(sq, PieceType::King));
   }
}

//=============================================================================
TEST(BBoardTest, colourAt) 
{
   BBoard b;
   for (Square sq = Sq::a1; sq <= Sq::h2; ++sq)
   {
      EXPECT_EQ(b.colourAt(sq), Color::White);
   }
   for (Square sq = Sq::a3; sq <= Sq::h6; ++sq)
   {
      EXPECT_EQ(b.colourAt(sq), Color::EmptyColor);
      EXPECT_EQ(b.colourAt(sq), Color::EmptyColor);
   }
   for (Square sq = Sq::a7; sq <= Sq::h8; ++sq)
   {
      EXPECT_EQ(b.colourAt(sq), Color::Black);
   }
}

//=============================================================================
TEST(BBoardTest, pieceAt) 
{
   BBoard b;
   for (Square sq = Sq::a2; sq <= Sq::h2; ++sq)
   {
      EXPECT_EQ(b.pieceAt(sq), PieceType::Pawn);
   }
   for (Square sq = Sq::a7; sq <= Sq::h7; ++sq)
   {
      EXPECT_EQ(b.pieceAt(sq), PieceType::Pawn);
   }

   EXPECT_EQ(b.pieceAt(Sq::a1), PieceType::Rook);
   EXPECT_EQ(b.pieceAt(Sq::b1), PieceType::Knight);
   EXPECT_EQ(b.pieceAt(Sq::c1), PieceType::Bishop);
   EXPECT_EQ(b.pieceAt(Sq::d1), PieceType::Queen);
   EXPECT_EQ(b.pieceAt(Sq::e1), PieceType::King);
   EXPECT_EQ(b.pieceAt(Sq::f1), PieceType::Bishop);
   EXPECT_EQ(b.pieceAt(Sq::g1), PieceType::Knight);
   EXPECT_EQ(b.pieceAt(Sq::h1), PieceType::Rook);

   EXPECT_EQ(b.pieceAt(Sq::a8), PieceType::Rook);
   EXPECT_EQ(b.pieceAt(Sq::b8), PieceType::Knight);
   EXPECT_EQ(b.pieceAt(Sq::c8), PieceType::Bishop);
   EXPECT_EQ(b.pieceAt(Sq::d8), PieceType::Queen);
   EXPECT_EQ(b.pieceAt(Sq::e8), PieceType::King);
   EXPECT_EQ(b.pieceAt(Sq::f8), PieceType::Bishop);
   EXPECT_EQ(b.pieceAt(Sq::g8), PieceType::Knight);
   EXPECT_EQ(b.pieceAt(Sq::h8), PieceType::Rook);

   for (Square sq = Sq::a3; sq <= Sq::h6; ++sq)
   {
      EXPECT_EQ(b.pieceAt(sq), PieceType::EmptyPiece);
   }
}

//=============================================================================
TEST(BBoardTest, clear) 
{
   BBoard b;

   EXPECT_TRUE(b.isOccupied(Sq::a2));
   EXPECT_EQ(b.pieceAt(Sq::a2), PieceType::Pawn);
   EXPECT_EQ(b.colourAt(Sq::a2), Color::White);
   b.clear(Sq::a2, PieceType::Pawn, Color::White);
   EXPECT_FALSE(b.isOccupied(Sq::a2));
   EXPECT_EQ(b.pieceAt(Sq::a2), PieceType::EmptyPiece);
   EXPECT_EQ(b.colourAt(Sq::a2), Color::EmptyColor);
}

//=============================================================================
TEST(BBoardTest, set) 
{
   BBoard b;

   EXPECT_FALSE(b.isOccupied(Sq::c3));
   EXPECT_EQ(b.pieceAt(Sq::c3), PieceType::EmptyPiece);
   EXPECT_EQ(b.colourAt(Sq::c3), Color::EmptyColor);
   b.set(Sq::c3, PieceType::Rook, Color::Black);
   EXPECT_TRUE(b.isOccupied(Sq::c3));
   EXPECT_EQ(b.pieceAt(Sq::c3), PieceType::Rook);
   EXPECT_EQ(b.colourAt(Sq::c3), Color::Black);
}

//=============================================================================
TEST(BBoardTest, promote) 
{
   BBoard b;

   EXPECT_TRUE(b.isOccupied(Sq::d8));
   EXPECT_EQ(b.pieceAt(Sq::d8), PieceType::Queen);
   EXPECT_EQ(b.colourAt(Sq::d8), Color::Black);
   b.promote(Sq::d8, PieceType::Queen, PieceType::Pawn, Color::Black);
   EXPECT_TRUE(b.isOccupied(Sq::d8));
   EXPECT_EQ(b.pieceAt(Sq::d8), PieceType::Pawn);
   EXPECT_EQ(b.colourAt(Sq::d8), Color::Black);
}

//=============================================================================
TEST(BBoardTest, move) 
{
   BBoard b;

   EXPECT_TRUE(b.isOccupied(Sq::c1));
   EXPECT_EQ(b.pieceAt(Sq::c1), PieceType::Bishop);
   EXPECT_EQ(b.colourAt(Sq::c1), Color::White);
   EXPECT_FALSE(b.isOccupied(Sq::h5));
   EXPECT_EQ(b.pieceAt(Sq::h5), PieceType::EmptyPiece);
   EXPECT_EQ(b.colourAt(Sq::h5), Color::EmptyColor);
   b.move(Sq::c1, Sq::h5, PieceType::Bishop, Color::White);
   EXPECT_FALSE(b.isOccupied(Sq::c1));
   EXPECT_EQ(b.pieceAt(Sq::c1), PieceType::EmptyPiece);
   EXPECT_EQ(b.colourAt(Sq::c1), Color::EmptyColor);
   EXPECT_TRUE(b.isOccupied(Sq::h5));
   EXPECT_EQ(b.pieceAt(Sq::h5), PieceType::Bishop);
   EXPECT_EQ(b.colourAt(Sq::h5), Color::White);
}

//=============================================================================
TEST(BBoardTest, capture) 
{
   BBoard b;

   EXPECT_TRUE(b.isOccupied(Sq::g8));
   EXPECT_EQ(b.pieceAt(Sq::g8), PieceType::Knight);
   EXPECT_EQ(b.colourAt(Sq::g8), Color::Black);
   EXPECT_TRUE(b.isOccupied(Sq::e1));
   EXPECT_EQ(b.pieceAt(Sq::e1), PieceType::King);
   EXPECT_EQ(b.colourAt(Sq::e1), Color::White);
   b.capture(Sq::g8, Sq::e1, PieceType::Knight, PieceType::King, Color::Black, Color::White);
   EXPECT_FALSE(b.isOccupied(Sq::g8));
   EXPECT_EQ(b.pieceAt(Sq::g8), PieceType::EmptyPiece);
   EXPECT_EQ(b.colourAt(Sq::g8), Color::EmptyColor);
   EXPECT_TRUE(b.isOccupied(Sq::e1));
   EXPECT_EQ(b.pieceAt(Sq::e1), PieceType::Knight);
   EXPECT_EQ(b.colourAt(Sq::e1), Color::Black);
}
