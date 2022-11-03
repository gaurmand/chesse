#include <gtest/gtest.h>

#include "chess/moveexecutor.h"

using namespace Chess;

// ============================================================================
// FEN: r3kb1N/Q1qn2p1/8/1pP4p/3Pp1b1/1P2P3/1P3P2/3RK2R w Kq b6 0 18
void setBoard1(Board& b, State& s)
{
   b.setEmpty();
   b.setPiece(Sq::d1, Piece::Rook, Colour::White);
   b.setPiece(Sq::e1, Piece::King, Colour::White);
   b.setPiece(Sq::h1, Piece::Rook, Colour::White);
   b.setPiece(Sq::b2, Piece::Pawn, Colour::White);
   b.setPiece(Sq::f2, Piece::Pawn, Colour::White);
   b.setPiece(Sq::b3, Piece::Pawn, Colour::White);
   b.setPiece(Sq::e3, Piece::Pawn, Colour::White);
   b.setPiece(Sq::d4, Piece::Pawn, Colour::White);
   b.setPiece(Sq::c5, Piece::Pawn, Colour::White);
   b.setPiece(Sq::a7, Piece::Queen, Colour::White);
   b.setPiece(Sq::h8, Piece::Knight, Colour::White);

   b.setPiece(Sq::e4, Piece::Pawn, Colour::Black);
   b.setPiece(Sq::g4, Piece::Bishop, Colour::Black);
   b.setPiece(Sq::b5, Piece::Pawn, Colour::Black);
   b.setPiece(Sq::h5, Piece::Pawn, Colour::Black);
   b.setPiece(Sq::c7, Piece::Queen, Colour::Black);
   b.setPiece(Sq::d7, Piece::Knight, Colour::Black);
   b.setPiece(Sq::g7, Piece::Pawn, Colour::Black);
   b.setPiece(Sq::a8, Piece::Rook, Colour::Black);
   b.setPiece(Sq::e8, Piece::King, Colour::Black);
   b.setPiece(Sq::f8, Piece::Bishop, Colour::Black);

   s = {Colour::White, true, false, false, true, Sq::b6, 0, 8};
}

// ============================================================================
// FEN: 8/3k4/3b4/3P3p/1p2pP2/1R6/8/4K2R b K f3 0 29
void setBoard2(Board& b, State& s)
{
   b.setEmpty();
   b.setPiece(Sq::e1, Piece::King, Colour::White);
   b.setPiece(Sq::h1, Piece::Rook, Colour::White);
   b.setPiece(Sq::b3, Piece::Rook, Colour::White);
   b.setPiece(Sq::f4, Piece::Pawn, Colour::White);
   b.setPiece(Sq::d5, Piece::Pawn, Colour::White);

   b.setPiece(Sq::b4, Piece::Pawn, Colour::Black);
   b.setPiece(Sq::e4, Piece::Pawn, Colour::Black);
   b.setPiece(Sq::h5, Piece::Pawn, Colour::Black);
   b.setPiece(Sq::d6, Piece::Bishop, Colour::Black);
   b.setPiece(Sq::d7, Piece::King, Colour::Black);

   s = {Colour::Black, true, false, false, false, Sq::f3, 0, 29};
}

// ============================================================================
// FEN: 3k4/p1p3P1/8/4P1n1/8/1P6/1p1K4/R7 b - - 0 318
void setBoard3(Board& b, State& s)
{
   b.setEmpty();
   b.setPiece(Sq::a1, Piece::Rook, Colour::White);
   b.setPiece(Sq::d2, Piece::King, Colour::White);
   b.setPiece(Sq::b3, Piece::Pawn, Colour::White);
   b.setPiece(Sq::e5, Piece::Pawn, Colour::White);
   b.setPiece(Sq::g7, Piece::Pawn, Colour::White);

   b.setPiece(Sq::b2, Piece::Pawn, Colour::Black);
   b.setPiece(Sq::g5, Piece::Knight, Colour::Black);
   b.setPiece(Sq::a7, Piece::Pawn, Colour::Black);
   b.setPiece(Sq::c7, Piece::Pawn, Colour::Black);
   b.setPiece(Sq::d8, Piece::King, Colour::Black);

   s = {Colour::Black, false, false, false, false, Sq::Invalid, 0, 31};
}

// ============================================================================
TEST(MoveExecutorTest, NormalMove) 
{
   Board b;
   State s;
   setBoard1(b, s);
   MoveExecutor exec(b, s);

   Move m{Sq::h8, Sq::g6, MoveType::Normal};
   EXPECT_EQ(b.pieceAt(Sq::h8), Piece::Knight);
   EXPECT_EQ(b.colourAt(Sq::h8), Colour::White);
   EXPECT_EQ(b.pieceAt(Sq::g6), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::g6), Colour::Empty);
   EXPECT_EQ(s.activeColour_, Colour::White);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::b6);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 8);
   exec.move(m);
   EXPECT_EQ(b.pieceAt(Sq::h8), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::h8), Colour::Empty);
   EXPECT_EQ(b.pieceAt(Sq::g6), Piece::Knight);
   EXPECT_EQ(b.colourAt(Sq::g6), Colour::White);
   EXPECT_EQ(s.activeColour_, Colour::Black);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 1);
   EXPECT_EQ(s.fullMoveClock_, 8);
   exec.undo(m);
   EXPECT_EQ(b.pieceAt(Sq::h8), Piece::Knight);
   EXPECT_EQ(b.colourAt(Sq::h8), Colour::White);
   EXPECT_EQ(b.pieceAt(Sq::g6), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::g6), Colour::Empty);
   EXPECT_EQ(s.activeColour_, Colour::White);

   setBoard1(b, s);
   exec.move(m);

   m = Move{Sq::g4, Sq::d1, MoveType::Normal, Piece::Rook};
   EXPECT_EQ(b.pieceAt(Sq::g4), Piece::Bishop);
   EXPECT_EQ(b.colourAt(Sq::g4), Colour::Black);
   EXPECT_EQ(b.pieceAt(Sq::d1), Piece::Rook);
   EXPECT_EQ(b.colourAt(Sq::d1), Colour::White);
   EXPECT_EQ(s.activeColour_, Colour::Black);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 1);
   EXPECT_EQ(s.fullMoveClock_, 8);
   exec.move(m);
   EXPECT_EQ(b.pieceAt(Sq::g4), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::g4), Colour::Empty);
   EXPECT_EQ(b.pieceAt(Sq::d1), Piece::Bishop);
   EXPECT_EQ(b.colourAt(Sq::d1), Colour::Black);
   EXPECT_EQ(s.activeColour_, Colour::White);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 9);
   exec.undo(m);
   EXPECT_EQ(b.pieceAt(Sq::g4), Piece::Bishop);
   EXPECT_EQ(b.colourAt(Sq::g4), Colour::Black);
   EXPECT_EQ(b.pieceAt(Sq::d1), Piece::Rook);
   EXPECT_EQ(b.colourAt(Sq::d1), Colour::White);
   EXPECT_EQ(s.activeColour_, Colour::Black);
}

// ============================================================================
TEST(MoveExecutorTest, Castle) 
{
   Board b;
   State s;
   setBoard1(b, s);
   MoveExecutor exec(b, s);

   Move m{Sq::e1, Sq::g1, MoveType::ShortCastle};
   EXPECT_EQ(b.pieceAt(Sq::e1), Piece::King);
   EXPECT_EQ(b.colourAt(Sq::e1), Colour::White);
   EXPECT_EQ(b.pieceAt(Sq::g1), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::g1), Colour::Empty);
   EXPECT_EQ(b.pieceAt(Sq::h1), Piece::Rook);
   EXPECT_EQ(b.colourAt(Sq::h1), Colour::White);
   EXPECT_EQ(b.pieceAt(Sq::f1), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::f1), Colour::Empty);
   EXPECT_EQ(s.activeColour_, Colour::White);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::b6);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 8);
   exec.move(m);
   EXPECT_EQ(b.pieceAt(Sq::e1), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::e1), Colour::Empty);
   EXPECT_EQ(b.pieceAt(Sq::g1), Piece::King);
   EXPECT_EQ(b.colourAt(Sq::g1), Colour::White);
   EXPECT_EQ(b.pieceAt(Sq::h1), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::h1), Colour::Empty);
   EXPECT_EQ(b.pieceAt(Sq::f1), Piece::Rook);
   EXPECT_EQ(b.colourAt(Sq::f1), Colour::White);
   EXPECT_EQ(s.activeColour_, Colour::Black);
   EXPECT_EQ(s.canWhiteShortCastle_, false);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 1);
   EXPECT_EQ(s.fullMoveClock_, 8);
   exec.undo(m);
   EXPECT_EQ(b.pieceAt(Sq::e1), Piece::King);
   EXPECT_EQ(b.colourAt(Sq::e1), Colour::White);
   EXPECT_EQ(b.pieceAt(Sq::g1), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::g1), Colour::Empty);
   EXPECT_EQ(b.pieceAt(Sq::h1), Piece::Rook);
   EXPECT_EQ(b.colourAt(Sq::h1), Colour::White);
   EXPECT_EQ(b.pieceAt(Sq::f1), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::f1), Colour::Empty);
   EXPECT_EQ(s.activeColour_, Colour::White);

   setBoard1(b, s);
   exec.move(m);

   m = Move{Sq::e8, Sq::c8, MoveType::LongCastle};
   EXPECT_EQ(b.pieceAt(Sq::e8), Piece::King);
   EXPECT_EQ(b.colourAt(Sq::e8), Colour::Black);
   EXPECT_EQ(b.pieceAt(Sq::c8), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::c8), Colour::Empty);
   EXPECT_EQ(b.pieceAt(Sq::a8), Piece::Rook);
   EXPECT_EQ(b.colourAt(Sq::a8), Colour::Black);
   EXPECT_EQ(b.pieceAt(Sq::d8), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::d8), Colour::Empty);
   EXPECT_EQ(s.activeColour_, Colour::Black);
   EXPECT_EQ(s.canWhiteShortCastle_, false);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 1);
   EXPECT_EQ(s.fullMoveClock_, 8);
   exec.move(m);
   EXPECT_EQ(b.pieceAt(Sq::e8), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::e8), Colour::Empty);
   EXPECT_EQ(b.pieceAt(Sq::c8), Piece::King);
   EXPECT_EQ(b.colourAt(Sq::c8), Colour::Black);
   EXPECT_EQ(b.pieceAt(Sq::a8), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::a8), Colour::Empty);
   EXPECT_EQ(b.pieceAt(Sq::d8), Piece::Rook);
   EXPECT_EQ(b.colourAt(Sq::d8), Colour::Black);
   EXPECT_EQ(s.activeColour_, Colour::White);
   EXPECT_EQ(s.canWhiteShortCastle_, false);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, false);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 2);
   EXPECT_EQ(s.fullMoveClock_, 9);
   exec.undo(m);
   EXPECT_EQ(b.pieceAt(Sq::e8), Piece::King);
   EXPECT_EQ(b.colourAt(Sq::e8), Colour::Black);
   EXPECT_EQ(b.pieceAt(Sq::c8), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::c8), Colour::Empty);
   EXPECT_EQ(b.pieceAt(Sq::a8), Piece::Rook);
   EXPECT_EQ(b.colourAt(Sq::a8), Colour::Black);
   EXPECT_EQ(b.pieceAt(Sq::d8), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::d8), Colour::Empty);
   EXPECT_EQ(s.activeColour_, Colour::Black);
}

// ============================================================================
TEST(MoveExecutorTest, EnPassant) 
{
   Board b;
   State s;
   setBoard1(b, s);
   MoveExecutor exec(b, s);

   Move m{Sq::c5, Sq::b6, MoveType::EnPassant, Piece::Pawn};
   EXPECT_EQ(b.pieceAt(Sq::c5), Piece::Pawn);
   EXPECT_EQ(b.colourAt(Sq::c5), Colour::White);
   EXPECT_EQ(b.pieceAt(Sq::b6), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::b6), Colour::Empty);
   EXPECT_EQ(b.pieceAt(Sq::b5), Piece::Pawn);
   EXPECT_EQ(b.colourAt(Sq::b5), Colour::Black);
   EXPECT_EQ(s.activeColour_, Colour::White);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::b6);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 8);
   exec.move(m);
   EXPECT_EQ(b.pieceAt(Sq::c5), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::c5), Colour::Empty);
   EXPECT_EQ(b.pieceAt(Sq::b6), Piece::Pawn);
   EXPECT_EQ(b.colourAt(Sq::b6), Colour::White);
   EXPECT_EQ(b.pieceAt(Sq::b5), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::b5), Colour::Empty);
   EXPECT_EQ(s.activeColour_, Colour::Black);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 8);
   exec.undo(m);
   EXPECT_EQ(b.pieceAt(Sq::c5), Piece::Pawn);
   EXPECT_EQ(b.colourAt(Sq::c5), Colour::White);
   EXPECT_EQ(b.pieceAt(Sq::b6), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::b6), Colour::Empty);
   EXPECT_EQ(b.pieceAt(Sq::b5), Piece::Pawn);
   EXPECT_EQ(b.colourAt(Sq::b5), Colour::Black);
   EXPECT_EQ(s.activeColour_, Colour::White);

   setBoard2(b, s);

   m = Move{Sq::e4, Sq::f3, MoveType::EnPassant, Piece::Pawn};
   EXPECT_EQ(b.pieceAt(Sq::e4), Piece::Pawn);
   EXPECT_EQ(b.colourAt(Sq::e4), Colour::Black);
   EXPECT_EQ(b.pieceAt(Sq::f3), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::f3), Colour::Empty);
   EXPECT_EQ(b.pieceAt(Sq::f4), Piece::Pawn);
   EXPECT_EQ(b.colourAt(Sq::f4), Colour::White);
   EXPECT_EQ(s.activeColour_, Colour::Black);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, false);
   EXPECT_EQ(s.enPassantSquare_, Sq::f3);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 29);
   exec.move(m);
   EXPECT_EQ(b.pieceAt(Sq::e4), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::e4), Colour::Empty);
   EXPECT_EQ(b.pieceAt(Sq::f3), Piece::Pawn);
   EXPECT_EQ(b.colourAt(Sq::f3), Colour::Black);
   EXPECT_EQ(b.pieceAt(Sq::f4), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::f4), Colour::Empty);
   EXPECT_EQ(s.activeColour_, Colour::White);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, false);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 30);
   exec.undo(m);
   EXPECT_EQ(b.pieceAt(Sq::e4), Piece::Pawn);
   EXPECT_EQ(b.colourAt(Sq::e4), Colour::Black);
   EXPECT_EQ(b.pieceAt(Sq::f3), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::f3), Colour::Empty);
   EXPECT_EQ(b.pieceAt(Sq::f4), Piece::Pawn);
   EXPECT_EQ(b.colourAt(Sq::f4), Colour::White);
   EXPECT_EQ(s.activeColour_, Colour::Black);
}

// ============================================================================
TEST(MoveExecutorTest, DoubleAdvance) 
{
   Board b;
   State s;
   MoveExecutor exec(b, s);

   Move m{Sq::e2, Sq::e4, MoveType::DoubleAdvance};
   EXPECT_EQ(b.pieceAt(Sq::e2), Piece::Pawn);
   EXPECT_EQ(b.colourAt(Sq::e2), Colour::White);
   EXPECT_EQ(b.pieceAt(Sq::e4), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::e4), Colour::Empty);
   EXPECT_EQ(s.activeColour_, Colour::White);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, true);
   EXPECT_EQ(s.canBlackShortCastle_, true);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 0);
   exec.move(m);
   EXPECT_EQ(b.pieceAt(Sq::e2), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::e2), Colour::Empty);
   EXPECT_EQ(b.pieceAt(Sq::e4), Piece::Pawn);
   EXPECT_EQ(b.colourAt(Sq::e4), Colour::White);
   EXPECT_EQ(s.activeColour_, Colour::Black);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, true);
   EXPECT_EQ(s.canBlackShortCastle_, true);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::e3);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 0);
   exec.undo(m);
   EXPECT_EQ(b.pieceAt(Sq::e2), Piece::Pawn);
   EXPECT_EQ(b.colourAt(Sq::e2), Colour::White);
   EXPECT_EQ(b.pieceAt(Sq::e4), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::e4), Colour::Empty);
   EXPECT_EQ(s.activeColour_, Colour::White);

   b.setDefault();
   exec.move(m);

   m = Move{Sq::d7, Sq::d5, MoveType::DoubleAdvance};
   EXPECT_EQ(b.pieceAt(Sq::d7), Piece::Pawn);
   EXPECT_EQ(b.colourAt(Sq::d7), Colour::Black);
   EXPECT_EQ(b.pieceAt(Sq::d5), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::d5), Colour::Empty);
   EXPECT_EQ(s.activeColour_, Colour::Black);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, true);
   EXPECT_EQ(s.canBlackShortCastle_, true);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::e3);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 0);
   exec.move(m);
   EXPECT_EQ(b.pieceAt(Sq::d7), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::d7), Colour::Empty);
   EXPECT_EQ(b.pieceAt(Sq::d5), Piece::Pawn);
   EXPECT_EQ(b.colourAt(Sq::d5), Colour::Black);
   EXPECT_EQ(s.activeColour_, Colour::White);
   EXPECT_EQ(s.canWhiteShortCastle_, true);
   EXPECT_EQ(s.canWhiteLongCastle_, true);
   EXPECT_EQ(s.canBlackShortCastle_, true);
   EXPECT_EQ(s.canBlackLongCastle_, true);
   EXPECT_EQ(s.enPassantSquare_, Sq::d6);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 1);
   exec.undo(m);
   EXPECT_EQ(b.pieceAt(Sq::d7), Piece::Pawn);
   EXPECT_EQ(b.colourAt(Sq::d7), Colour::Black);
   EXPECT_EQ(b.pieceAt(Sq::d5), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::d5), Colour::Empty);
   EXPECT_EQ(s.activeColour_, Colour::Black);
}

// ============================================================================
TEST(MoveExecutorTest, Promotion) 
{
   Board b;
   State s;
   setBoard3(b, s);
   MoveExecutor exec(b, s);

   Move m{Sq::b2, Sq::a1, MoveType::KnightPromotion, Piece::Rook};
   EXPECT_EQ(b.pieceAt(Sq::b2), Piece::Pawn);
   EXPECT_EQ(b.colourAt(Sq::b2), Colour::Black);
   EXPECT_EQ(b.pieceAt(Sq::a1), Piece::Rook);
   EXPECT_EQ(b.colourAt(Sq::a1), Colour::White);
   EXPECT_EQ(s.activeColour_, Colour::Black);
   EXPECT_EQ(s.canWhiteShortCastle_, false);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, false);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 31);
   exec.move(m);
   EXPECT_EQ(b.pieceAt(Sq::b2), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::b2), Colour::Empty);
   EXPECT_EQ(b.pieceAt(Sq::a1), Piece::Knight);
   EXPECT_EQ(b.colourAt(Sq::a1), Colour::Black);
   EXPECT_EQ(s.activeColour_, Colour::White);
   EXPECT_EQ(s.canWhiteShortCastle_, false);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, false);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 32);
   exec.undo(m);
   EXPECT_EQ(b.pieceAt(Sq::b2), Piece::Pawn);
   EXPECT_EQ(b.colourAt(Sq::b2), Colour::Black);
   EXPECT_EQ(b.pieceAt(Sq::a1), Piece::Rook);
   EXPECT_EQ(b.colourAt(Sq::a1), Colour::White);
   EXPECT_EQ(s.activeColour_, Colour::Black);

   setBoard3(b, s);
   exec.move(m);

   m = Move{Sq::g7, Sq::g8, MoveType::QueenPromotion};
   EXPECT_EQ(b.pieceAt(Sq::g7), Piece::Pawn);
   EXPECT_EQ(b.colourAt(Sq::g7), Colour::White);
   EXPECT_EQ(b.pieceAt(Sq::g8), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::g8), Colour::Empty);
   EXPECT_EQ(s.activeColour_, Colour::White);
   EXPECT_EQ(s.canWhiteShortCastle_, false);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, false);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 0);
   EXPECT_EQ(s.fullMoveClock_, 32);
   exec.move(m);
   EXPECT_EQ(b.pieceAt(Sq::g7), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::g7), Colour::Empty);
   EXPECT_EQ(b.pieceAt(Sq::g8), Piece::Queen);
   EXPECT_EQ(b.colourAt(Sq::g8), Colour::White);
   EXPECT_EQ(s.activeColour_, Colour::Black);
   EXPECT_EQ(s.canWhiteShortCastle_, false);
   EXPECT_EQ(s.canWhiteLongCastle_, false);
   EXPECT_EQ(s.canBlackShortCastle_, false);
   EXPECT_EQ(s.canBlackLongCastle_, false);
   EXPECT_EQ(s.enPassantSquare_, Sq::Invalid);
   EXPECT_EQ(s.halfMoveClock_, 1);
   EXPECT_EQ(s.fullMoveClock_, 32);
   exec.undo(m);
   EXPECT_EQ(b.pieceAt(Sq::g7), Piece::Pawn);
   EXPECT_EQ(b.colourAt(Sq::g7), Colour::White);
   EXPECT_EQ(b.pieceAt(Sq::g8), Piece::Empty);
   EXPECT_EQ(b.colourAt(Sq::g8), Colour::Empty);
   EXPECT_EQ(s.activeColour_, Colour::White);
}
