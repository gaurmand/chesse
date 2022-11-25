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

//=============================================================================
TEST(BBoardTest, fen1) 
{
   BBoard b("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
   BBoard c;

   EXPECT_EQ(b.occupied(), c.occupied());
   EXPECT_EQ(b.empty(), c.empty());

   EXPECT_EQ(b.colours(Color::White), c.colours(Color::White));
   EXPECT_EQ(b.colours(Color::Black), c.colours(Color::Black));

   EXPECT_EQ(b.pieces(Color::White, PieceType::Pawn), c.pieces(Color::White, PieceType::Pawn));
   EXPECT_EQ(b.pieces(Color::White, PieceType::Knight), c.pieces(Color::White, PieceType::Knight));
   EXPECT_EQ(b.pieces(Color::White, PieceType::Bishop), c.pieces(Color::White, PieceType::Bishop));
   EXPECT_EQ(b.pieces(Color::White, PieceType::Rook), c.pieces(Color::White, PieceType::Rook));
   EXPECT_EQ(b.pieces(Color::White, PieceType::Queen), c.pieces(Color::White, PieceType::Queen));
   EXPECT_EQ(b.pieces(Color::White, PieceType::King), c.pieces(Color::White, PieceType::King));

   EXPECT_EQ(b.pieces(Color::Black, PieceType::Pawn), c.pieces(Color::Black, PieceType::Pawn));
   EXPECT_EQ(b.pieces(Color::Black, PieceType::Knight), c.pieces(Color::Black, PieceType::Knight));
   EXPECT_EQ(b.pieces(Color::Black, PieceType::Bishop), c.pieces(Color::Black, PieceType::Bishop));
   EXPECT_EQ(b.pieces(Color::Black, PieceType::Rook), c.pieces(Color::Black, PieceType::Rook));
   EXPECT_EQ(b.pieces(Color::Black, PieceType::Queen), c.pieces(Color::Black, PieceType::Queen));
   EXPECT_EQ(b.pieces(Color::Black, PieceType::King), c.pieces(Color::Black, PieceType::King));
}

//=============================================================================
TEST(BBoardTest, fen2) 
{
   BBoard b("r3kb1N/Q1qn2p1/8/1pP4p/3Pp1b1/1P2P3/1P3P2/3RK2R w Kq b6 0 18");

   EXPECT_EQ(b.occupied(), 0b10110001'01001101'00000000'10000110'01011000'00010010'00100010'10011000);
   EXPECT_EQ(b.empty(),    0b01001110'10110010'11111111'01111001'10100111'11101101'11011101'01100111);

   EXPECT_EQ(b.colours(Color::White), 0b10000000'00000001'00000000'00000100'00001000'00010010'00100010'10011000);
   EXPECT_EQ(b.colours(Color::Black), 0b00110001'01001100'00000000'10000010'01010000'00000000'00000000'00000000);

   EXPECT_EQ(b.pieces(Color::White, PieceType::Pawn), 0b00000000'00000000'00000000'00000100'00001000'00010010'00100010'00000000);
   EXPECT_EQ(b.pieces(Color::White, PieceType::Knight), 0b10000000'00000000'00000000'00000000'00000000'00000000'00000000'00000000);
   EXPECT_EQ(b.pieces(Color::White, PieceType::Bishop), 0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'00000000);
   EXPECT_EQ(b.pieces(Color::White, PieceType::Rook), 0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'10001000);
   EXPECT_EQ(b.pieces(Color::White, PieceType::Queen), 0b00000000'00000001'00000000'00000000'00000000'00000000'00000000'00000000);
   EXPECT_EQ(b.pieces(Color::White, PieceType::King), 0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'0010000);

   EXPECT_EQ(b.pieces(Color::Black, PieceType::Pawn), 0b00000000'01000000'00000000'10000010'00010000'00000000'00000000'00000000);
   EXPECT_EQ(b.pieces(Color::Black, PieceType::Knight), 0b00000000'00001000'00000000'00000000'00000000'00000000'00000000'00000000);
   EXPECT_EQ(b.pieces(Color::Black, PieceType::Bishop), 0b00100000'00000000'00000000'00000000'01000000'00000000'00000000'00000000);
   EXPECT_EQ(b.pieces(Color::Black, PieceType::Rook), 0b00000001'00000000'00000000'00000000'00000000'00000000'00000000'00000000);
   EXPECT_EQ(b.pieces(Color::Black, PieceType::Queen), 0b00000000'00000100'00000000'00000000'00000000'00000000'00000000'00000000);
   EXPECT_EQ(b.pieces(Color::Black, PieceType::King), 0b00010000'00000000'00000000'00000000'00000000'00000000'00000000'00000000);
}

//=============================================================================
TEST(BBoardTest, fen3) 
{
   BBoard b("r3k2r/2P5/7b/8/8/Q7/7n/R3K2R b KQkq - 2 35");

   EXPECT_EQ(b.occupied(), 0b10010001'00000100'10000000'00000000'00000000'00000001'10000000'10010001);
   EXPECT_EQ(b.empty(),    0b01101110'11111011'01111111'11111111'11111111'11111110'01111111'01101110);

   EXPECT_EQ(b.colours(Color::White), 0b00000000'00000100'00000000'00000000'00000000'00000001'00000000'10010001);
   EXPECT_EQ(b.colours(Color::Black), 0b10010001'00000000'10000000'00000000'00000000'00000000'10000000'00000000);

   EXPECT_EQ(b.pieces(Color::White, PieceType::Pawn), 0b00000000'00000100'00000000'00000000'00000000'00000000'00000000'00000000);
   EXPECT_EQ(b.pieces(Color::White, PieceType::Knight), 0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'00000000);
   EXPECT_EQ(b.pieces(Color::White, PieceType::Bishop), 0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'00000000);
   EXPECT_EQ(b.pieces(Color::White, PieceType::Rook), 0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'10000001);
   EXPECT_EQ(b.pieces(Color::White, PieceType::Queen), 0b00000000'00000000'00000000'00000000'00000000'00000001'00000000'00000000);
   EXPECT_EQ(b.pieces(Color::White, PieceType::King), 0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'00010000);

   EXPECT_EQ(b.pieces(Color::Black, PieceType::Pawn), 0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'00000000);
   EXPECT_EQ(b.pieces(Color::Black, PieceType::Knight), 0b00000000'00000000'00000000'00000000'00000000'00000000'10000000'00000000);
   EXPECT_EQ(b.pieces(Color::Black, PieceType::Bishop), 0b00000000'00000000'10000000'00000000'00000000'00000000'00000000'00000000);
   EXPECT_EQ(b.pieces(Color::Black, PieceType::Rook), 0b10000001'00000000'00000000'00000000'00000000'00000000'00000000'00000000);
   EXPECT_EQ(b.pieces(Color::Black, PieceType::Queen), 0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'00000000);
   EXPECT_EQ(b.pieces(Color::Black, PieceType::King), 0b00010000'00000000'00000000'00000000'00000000'00000000'00000000'00000000);
}
