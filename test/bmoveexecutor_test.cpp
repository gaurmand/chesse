#include <gtest/gtest.h>

#include "test_helper.h"
#include "../chess/bmoveexecutor.h"

using namespace Chess;

static const char* kBoard1 = "r3kb1N/Q1qn2p1/8/1pP4p/3Pp1b1/1P2P3/1P3P2/3RK2R w Kq b6 0 18";
static const char* kBoard2 = "r3kb2/Q1qn2p1/6N1/1pP4p/3Pp1b1/1P2P3/1P3P2/3RK2R b Kq - 1 18";
static const char* kBoard3 = "r3kb1N/Q1qn2p1/8/1pP4p/3Pp1b1/1P2P3/1P3P2/3R1RK1 b q - 1 18";

static const char* kBoard4 = "8/3k4/3b4/3P3p/1p2pP2/1R6/8/4K2R b K f3 0 29";

static const char* kBoard5 = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1";

static const char* kBoard6 = "3k4/p1p3P1/8/4P1n1/8/1P6/1p1K4/R7 b - - 0 318";
static const char* kBoard7 = "3k4/p1p3P1/8/4P1n1/8/1P6/3K4/n7 w - - 0 319";

//=============================================================================
TEST(BMoveExecutorTest, NormalMove) 
{
   BBoard b(kBoard1);
   State s = fromFEN(kBoard1);
   BMoveExecutor exec(b, s);

   BMove m{Sq::h8, Sq::g6, PieceType::Knight, PieceType::EmptyPiece, 
      Color::White, Color::Black, MoveType::Normal};
   EXPECT_TRUE(b.isPieceAt(Sq::h8, PieceType::Knight, Color::White));
   EXPECT_FALSE(b.isOccupied(Sq::g6));
   EXPECT_EQ(s.active_, Colour::White);
   EXPECT_EQ(s.inactive_, Colour::Black);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::b6);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 18);
   exec.move(m);
   EXPECT_FALSE(b.isOccupied(Sq::h8));
   EXPECT_TRUE(b.isPieceAt(Sq::g6, PieceType::Knight, Color::White));
   EXPECT_EQ(s.active_, Colour::Black);
   EXPECT_EQ(s.inactive_, Colour::White);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 1);
   EXPECT_EQ(s.fullMoveClock_, 18);
   exec.unmove(m);
   EXPECT_TRUE(b.isPieceAt(Sq::h8, PieceType::Knight, Color::White));
   EXPECT_FALSE(b.isOccupied(Sq::g6));
   EXPECT_EQ(s.active_, Colour::White);
   EXPECT_EQ(s.inactive_, Colour::Black);

   b.setFEN(kBoard2);
   s = fromFEN(kBoard2);

   m = BMove{Sq::g4, Sq::d1, PieceType::Bishop, PieceType::Rook, 
      Color::Black, Color::White, MoveType::Normal};
   EXPECT_TRUE(b.isPieceAt(Sq::g4, PieceType::Bishop, Color::Black));
   EXPECT_TRUE(b.isPieceAt(Sq::d1, PieceType::Rook, Color::White));
   EXPECT_EQ(s.active_, Colour::Black);
   EXPECT_EQ(s.inactive_, Colour::White);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 1);
   EXPECT_EQ(s.fullMoveClock_, 18);
   exec.move(m);
   EXPECT_FALSE(b.isOccupied(Sq::g4));
   EXPECT_TRUE(b.isPieceAt(Sq::d1, PieceType::Bishop, Color::Black));
   EXPECT_EQ(s.active_, Colour::White);
   EXPECT_EQ(s.inactive_, Colour::Black);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 19);
   exec.unmove(m);
   EXPECT_TRUE(b.isPieceAt(Sq::g4, PieceType::Bishop, Color::Black));
   EXPECT_TRUE(b.isPieceAt(Sq::d1, PieceType::Rook, Color::White));
   EXPECT_EQ(s.active_, Colour::Black);
   EXPECT_EQ(s.inactive_, Colour::White);
}

// ============================================================================
TEST(BMoveExecutorTest, Castle) 
{
   BBoard b(kBoard1);
   State s = fromFEN(kBoard1);
   BMoveExecutor exec(b, s);

   BMove m{Sq::e1, Sq::g1, PieceType::King, PieceType::EmptyPiece, 
      Color::White, Color::Black, MoveType::ShortCastle};

   EXPECT_TRUE(b.isPieceAt(Sq::e1, PieceType::King, Color::White));
   EXPECT_FALSE(b.isOccupied(Sq::g1));
   EXPECT_TRUE(b.isPieceAt(Sq::h1, PieceType::Rook, Color::White));
   EXPECT_FALSE(b.isOccupied(Sq::f1));
   EXPECT_EQ(s.active_, Colour::White);
   EXPECT_EQ(s.inactive_, Colour::Black);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::b6);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 18);
   exec.move(m);
   EXPECT_FALSE(b.isOccupied(Sq::e1));
   EXPECT_TRUE(b.isPieceAt(Sq::g1, PieceType::King, Color::White));
   EXPECT_FALSE(b.isOccupied(Sq::h1));
   EXPECT_TRUE(b.isPieceAt(Sq::f1, PieceType::Rook, Color::White));
   EXPECT_EQ(s.active_, Colour::Black);
   EXPECT_EQ(s.inactive_, Colour::White);
   EXPECT_EQ(s.canWhiteShortCastle_, false);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 1);
   EXPECT_EQ(s.fullMoveClock_, 18);
   exec.unmove(m);
   EXPECT_TRUE(b.isPieceAt(Sq::e1, PieceType::King, Color::White));
   EXPECT_FALSE(b.isOccupied(Sq::g1));
   EXPECT_TRUE(b.isPieceAt(Sq::h1, PieceType::Rook, Color::White));
   EXPECT_FALSE(b.isOccupied(Sq::f1));
   EXPECT_EQ(s.active_, Colour::White);
   EXPECT_EQ(s.inactive_, Colour::Black);

   b.setFEN(kBoard3);
   s = fromFEN(kBoard3);

   m = {Sq::e8, Sq::c8, PieceType::King, PieceType::EmptyPiece, 
      Color::Black, Color::White, MoveType::LongCastle};

   EXPECT_TRUE(b.isPieceAt(Sq::e8, PieceType::King, Color::Black));
   EXPECT_FALSE(b.isOccupied(Sq::c8));
   EXPECT_TRUE(b.isPieceAt(Sq::a8, PieceType::Rook, Color::Black));
   EXPECT_FALSE(b.isOccupied(Sq::d8));
   EXPECT_EQ(s.active_, Colour::Black);
   EXPECT_EQ(s.inactive_, Colour::White);
   EXPECT_EQ(s.canWhiteShortCastle_, false);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 1);
   EXPECT_EQ(s.fullMoveClock_, 18);
   exec.move(m);
   EXPECT_FALSE(b.isOccupied(Sq::e8));
   EXPECT_TRUE(b.isPieceAt(Sq::c8, PieceType::King, Color::Black));
   EXPECT_FALSE(b.isOccupied(Sq::a8));
   EXPECT_TRUE(b.isPieceAt(Sq::d8, PieceType::Rook, Color::Black));
   EXPECT_EQ(s.active_, Colour::White);
   EXPECT_EQ(s.inactive_, Colour::Black);
   EXPECT_EQ(s.canWhiteShortCastle_, false);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, false);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 2);
   EXPECT_EQ(s.fullMoveClock_, 19);
   exec.unmove(m);
   EXPECT_TRUE(b.isPieceAt(Sq::e8, PieceType::King, Color::Black));
   EXPECT_FALSE(b.isOccupied(Sq::c8));
   EXPECT_TRUE(b.isPieceAt(Sq::a8, PieceType::Rook, Color::Black));
   EXPECT_FALSE(b.isOccupied(Sq::d8));
   EXPECT_EQ(s.active_, Colour::Black);
   EXPECT_EQ(s.inactive_, Colour::White);
}

// ============================================================================
TEST(BMoveExecutorTest, EnPassant) 
{
   BBoard b(kBoard1);
   State s = fromFEN(kBoard1);
   BMoveExecutor exec(b, s);

   BMove m{Sq::c5, Sq::b6, PieceType::Pawn, PieceType::EmptyPiece, 
      Color::White, Color::Black, MoveType::EnPassant};

   EXPECT_TRUE(b.isPieceAt(Sq::c5, PieceType::Pawn, Color::White));
   EXPECT_FALSE(b.isOccupied(Sq::b6));
   EXPECT_TRUE(b.isPieceAt(Sq::b5, PieceType::Pawn, Color::Black));
   EXPECT_EQ(s.active_, Colour::White);
   EXPECT_EQ(s.inactive_, Colour::Black);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::b6);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 18);
   exec.move(m);
   EXPECT_FALSE(b.isOccupied(Sq::c5));
   EXPECT_TRUE(b.isPieceAt(Sq::b6, PieceType::Pawn, Color::White));
   EXPECT_FALSE(b.isOccupied(Sq::b5));
   EXPECT_EQ(s.active_, Colour::Black);
   EXPECT_EQ(s.inactive_, Colour::White);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 18);
   exec.unmove(m);
   EXPECT_TRUE(b.isPieceAt(Sq::c5, PieceType::Pawn, Color::White));
   EXPECT_FALSE(b.isOccupied(Sq::b6));
   EXPECT_TRUE(b.isPieceAt(Sq::b5, PieceType::Pawn, Color::Black));
   EXPECT_EQ(s.active_, Colour::White);
   EXPECT_EQ(s.inactive_, Colour::Black);

   b.setFEN(kBoard4);
   s = fromFEN(kBoard4);

   m = {Sq::e4, Sq::f3, PieceType::Pawn, PieceType::EmptyPiece, 
      Color::Black, Color::White, MoveType::EnPassant};

   EXPECT_TRUE(b.isPieceAt(Sq::e4, PieceType::Pawn, Color::Black));
   EXPECT_FALSE(b.isOccupied(Sq::f3));
   EXPECT_TRUE(b.isPieceAt(Sq::f4, PieceType::Pawn, Color::White));
   EXPECT_EQ(s.active_, Colour::Black);
   EXPECT_EQ(s.inactive_, Colour::White);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, false);
   EXPECT_EQ(s.enPassantSquare_, Sq::f3);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 29);
   exec.move(m);
   EXPECT_FALSE(b.isOccupied(Sq::e4));
   EXPECT_TRUE(b.isPieceAt(Sq::f3, PieceType::Pawn, Color::Black));
   EXPECT_FALSE(b.isOccupied(Sq::f4));
   EXPECT_EQ(s.active_, Colour::White);
   EXPECT_EQ(s.inactive_, Colour::Black);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, false);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 30);
   exec.unmove(m);
   EXPECT_TRUE(b.isPieceAt(Sq::e4, PieceType::Pawn, Color::Black));
   EXPECT_FALSE(b.isOccupied(Sq::f3));
   EXPECT_TRUE(b.isPieceAt(Sq::f4, PieceType::Pawn, Color::White));
   EXPECT_EQ(s.active_, Colour::Black);
   EXPECT_EQ(s.inactive_, Colour::White);
}

// ============================================================================
TEST(BMoveExecutorTest, DoubleAdvance) 
{
   BBoard b;
   State s;
   BMoveExecutor exec(b, s);

   BMove m{Sq::e2, Sq::e4, PieceType::Pawn, PieceType::EmptyPiece, 
      Color::White, Color::Black, MoveType::DoubleAdvance};

   EXPECT_TRUE(b.isPieceAt(Sq::e2, PieceType::Pawn, Color::White));
   EXPECT_FALSE(b.isOccupied(Sq::e4));
   EXPECT_EQ(s.active_, Colour::White);
   EXPECT_EQ(s.inactive_, Colour::Black);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, true);
   EXPECT_EQ(s.canBlackShortCastle_, true);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 0);
   exec.move(m);
   EXPECT_FALSE(b.isOccupied(Sq::e2));
   EXPECT_TRUE(b.isPieceAt(Sq::e4, PieceType::Pawn, Color::White));
   EXPECT_EQ(s.active_, Colour::Black);
   EXPECT_EQ(s.inactive_, Colour::White);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, true);
   EXPECT_EQ(s.canBlackShortCastle_, true);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::e3);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 0);
   exec.unmove(m);
   EXPECT_TRUE(b.isPieceAt(Sq::e2, PieceType::Pawn, Color::White));
   EXPECT_FALSE(b.isOccupied(Sq::e4));
   EXPECT_EQ(s.active_, Colour::White);
   EXPECT_EQ(s.inactive_, Colour::Black);

   b.setFEN(kBoard5);
   s = fromFEN(kBoard5);

   m = {Sq::d7, Sq::d5, PieceType::Pawn, PieceType::EmptyPiece, 
      Color::Black, Color::White, MoveType::DoubleAdvance};

   EXPECT_TRUE(b.isPieceAt(Sq::d7, PieceType::Pawn, Color::Black));
   EXPECT_FALSE(b.isOccupied(Sq::d5));
   EXPECT_EQ(s.active_, Colour::Black);
   EXPECT_EQ(s.inactive_, Colour::White);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, true);
   EXPECT_EQ(s.canBlackShortCastle_, true);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::e3);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 1);
   exec.move(m);
   EXPECT_FALSE(b.isOccupied(Sq::d7));
   EXPECT_TRUE(b.isPieceAt(Sq::d5, PieceType::Pawn, Color::Black));
   EXPECT_EQ(s.active_, Colour::White);
   EXPECT_EQ(s.inactive_, Colour::Black);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, true);
   EXPECT_EQ(s.canBlackShortCastle_, true);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::d6);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 2);
   exec.unmove(m);
   EXPECT_TRUE(b.isPieceAt(Sq::d7, PieceType::Pawn, Color::Black));
   EXPECT_FALSE(b.isOccupied(Sq::d5));
   EXPECT_EQ(s.active_, Colour::Black);
   EXPECT_EQ(s.inactive_, Colour::White);
}

// ============================================================================
TEST(BMoveExecutorTest, Promotion) 
{
   BBoard b(kBoard6);
   State s = fromFEN(kBoard6);
   BMoveExecutor exec(b, s);

   BMove m{Sq::b2, Sq::a1, PieceType::Pawn, PieceType::Rook, 
      Color::Black, Color::White, MoveType::KnightPromotion};

   EXPECT_TRUE(b.isPieceAt(Sq::b2, PieceType::Pawn, Color::Black));
   EXPECT_TRUE(b.isPieceAt(Sq::a1, PieceType::Rook, Color::White));
   EXPECT_EQ(s.active_, Colour::Black);
   EXPECT_EQ(s.inactive_, Colour::White);
   EXPECT_EQ(s.canWhiteShortCastle_, false);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, false);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 318);
   exec.move(m);
   EXPECT_FALSE(b.isOccupied(Sq::b2));
   EXPECT_TRUE(b.isPieceAt(Sq::a1, PieceType::Knight, Color::Black));
   EXPECT_EQ(s.inactive_, Colour::Black);
   EXPECT_EQ(s.canWhiteShortCastle_, false);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, false);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 319);
   exec.unmove(m);
   EXPECT_TRUE(b.isPieceAt(Sq::b2, PieceType::Pawn, Color::Black));
   EXPECT_TRUE(b.isPieceAt(Sq::a1, PieceType::Rook, Color::White));
   EXPECT_EQ(s.active_, Colour::Black);
   EXPECT_EQ(s.inactive_, Colour::White);

   b.setFEN(kBoard7);
   s = fromFEN(kBoard7);

   m = {Sq::g7, Sq::g8, PieceType::Pawn, PieceType::EmptyPiece, 
      Color::White, Color::Black, MoveType::QueenPromotion};

   EXPECT_TRUE(b.isPieceAt(Sq::g7, PieceType::Pawn, Color::White));
   EXPECT_FALSE(b.isOccupied(Sq::g8));
   EXPECT_EQ(s.active_, Colour::White);
   EXPECT_EQ(s.inactive_, Colour::Black);
   EXPECT_EQ(s.canWhiteShortCastle_, false);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, false);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 319);
   exec.move(m);
   EXPECT_FALSE(b.isOccupied(Sq::g7));
   EXPECT_TRUE(b.isPieceAt(Sq::g8, PieceType::Queen, Color::White));
   EXPECT_EQ(s.active_, Colour::Black);
   EXPECT_EQ(s.inactive_, Colour::White);
   EXPECT_EQ(s.canWhiteShortCastle_, false);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, false);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 319);
   exec.unmove(m);
   EXPECT_TRUE(b.isPieceAt(Sq::g7, PieceType::Pawn, Color::White));
   EXPECT_FALSE(b.isOccupied(Sq::g8));
   EXPECT_EQ(s.active_, Colour::White);
   EXPECT_EQ(s.inactive_, Colour::Black);
}
