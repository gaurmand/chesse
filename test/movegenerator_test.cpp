#include <gtest/gtest.h>

#include "chess/movegen/movegenerator.h"
#include "chess/moveexecutor.h"
#include "test_helper.h"

#include <iterator>
#include <vector>
#include <string>
#include <list>
#include <deque>
#include <sstream>

using namespace Chess;

//=============================================================================
TEST(MoveGeneratorTest, CandidateMoves1) 
{
   Board b;
   State s;
   MoveGenerator gen(b,s);
   MoveExecutor exec(b, s);

   std::vector<Move> moves;
   gen(std::back_inserter(moves));
   EXPECT_EQ(moves.size(), 20);
   EXPECT_TRUE(contains(moves, Move{Sq::b1, Sq::c3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::b1, Sq::a3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::g1, Sq::h3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::g1, Sq::f3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a2, Sq::a3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a2, Sq::a4, MoveType::DoubleAdvance}));
   EXPECT_TRUE(contains(moves, Move{Sq::b2, Sq::b3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::b2, Sq::b4, MoveType::DoubleAdvance}));
   EXPECT_TRUE(contains(moves, Move{Sq::c2, Sq::c3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::c2, Sq::c4, MoveType::DoubleAdvance}));
   EXPECT_TRUE(contains(moves, Move{Sq::d2, Sq::d3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d2, Sq::d4, MoveType::DoubleAdvance}));
   EXPECT_TRUE(contains(moves, Move{Sq::e2, Sq::e3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::e2, Sq::e4, MoveType::DoubleAdvance}));
   EXPECT_TRUE(contains(moves, Move{Sq::f2, Sq::f3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::f2, Sq::f4, MoveType::DoubleAdvance}));
   EXPECT_TRUE(contains(moves, Move{Sq::g2, Sq::g3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::g2, Sq::g4, MoveType::DoubleAdvance}));
   EXPECT_TRUE(contains(moves, Move{Sq::h2, Sq::h3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::h2, Sq::h4, MoveType::DoubleAdvance}));

   exec.move(Move{Sq::g1, Sq::h3, MoveType::Normal});

   moves.clear();
   gen(std::back_inserter(moves));
   EXPECT_EQ(moves.size(), 20);
   EXPECT_TRUE(contains(moves, Move{Sq::b8, Sq::c6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::b8, Sq::a6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::g8, Sq::h6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::g8, Sq::f6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a7, Sq::a6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a7, Sq::a5, MoveType::DoubleAdvance}));
   EXPECT_TRUE(contains(moves, Move{Sq::b7, Sq::b6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::b7, Sq::b5, MoveType::DoubleAdvance}));
   EXPECT_TRUE(contains(moves, Move{Sq::c7, Sq::c6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::c7, Sq::c5, MoveType::DoubleAdvance}));
   EXPECT_TRUE(contains(moves, Move{Sq::d7, Sq::d6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d7, Sq::d5, MoveType::DoubleAdvance}));
   EXPECT_TRUE(contains(moves, Move{Sq::e7, Sq::e6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::e7, Sq::e5, MoveType::DoubleAdvance}));
   EXPECT_TRUE(contains(moves, Move{Sq::f7, Sq::f6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::f7, Sq::f5, MoveType::DoubleAdvance}));
   EXPECT_TRUE(contains(moves, Move{Sq::g7, Sq::g6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::g7, Sq::g5, MoveType::DoubleAdvance}));
   EXPECT_TRUE(contains(moves, Move{Sq::h7, Sq::h6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::h7, Sq::h5, MoveType::DoubleAdvance}));
}

//=============================================================================
TEST(MoveGeneratorTest, CandidateMoves2) 
{
   Board b;
   State s;
   setBoard1(b, s);
   MoveGenerator gen(b,s);
   MoveExecutor exec(b, s);

   std::vector<Move> moves;
   gen(std::back_inserter(moves));
   EXPECT_EQ(moves.size(), 34);
   EXPECT_TRUE(contains(moves, Move{Sq::d1, Sq::c1, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d1, Sq::b1, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d1, Sq::a1, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d1, Sq::d2, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d1, Sq::d3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::e1, Sq::d2, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::e1, Sq::e2, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::e1, Sq::f1, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::e1, Sq::g1, MoveType::ShortCastle}));
   EXPECT_TRUE(contains(moves, Move{Sq::h1, Sq::g1, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::h1, Sq::f1, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::h1, Sq::h2, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::h1, Sq::h3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::h1, Sq::h4, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::h1, Sq::h5, MoveType::Normal, Piece::Pawn}));
   EXPECT_TRUE(contains(moves, Move{Sq::f2, Sq::f3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::f2, Sq::f4, MoveType::DoubleAdvance}));
   EXPECT_TRUE(contains(moves, Move{Sq::b3, Sq::b4, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d4, Sq::d5, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::c5, Sq::c6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::c5, Sq::b6, MoveType::EnPassant, Piece::Pawn}));
   EXPECT_TRUE(contains(moves, Move{Sq::a7, Sq::a6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a7, Sq::a5, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a7, Sq::a4, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a7, Sq::a3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a7, Sq::a2, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a7, Sq::a1, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a7, Sq::a8, MoveType::Normal, Piece::Rook}));
   EXPECT_TRUE(contains(moves, Move{Sq::a7, Sq::b8, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a7, Sq::b7, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a7, Sq::b6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a7, Sq::c7, MoveType::Normal, Piece::Queen}));
   EXPECT_TRUE(contains(moves, Move{Sq::h8, Sq::f7, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::h8, Sq::g6, MoveType::Normal}));

   exec.move(Move{Sq::a7, Sq::c7, MoveType::Normal, Piece::Queen});

   moves.clear();
   gen(std::back_inserter(moves));
   EXPECT_EQ(moves.size(), 31);
   EXPECT_TRUE(contains(moves, Move{Sq::g4, Sq::f5, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::g4, Sq::e6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::g4, Sq::h3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::g4, Sq::f3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::g4, Sq::e2, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::g4, Sq::d1, MoveType::Normal, Piece::Rook}));
   EXPECT_TRUE(contains(moves, Move{Sq::b5, Sq::b4, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::h5, Sq::h4, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d7, Sq::b8, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d7, Sq::b6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d7, Sq::c5, MoveType::Normal, Piece::Pawn}));
   EXPECT_TRUE(contains(moves, Move{Sq::d7, Sq::e5, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d7, Sq::f6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::g7, Sq::g6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::g7, Sq::g5, MoveType::DoubleAdvance}));
   EXPECT_TRUE(contains(moves, Move{Sq::a8, Sq::a7, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a8, Sq::a6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a8, Sq::a5, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a8, Sq::a4, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a8, Sq::a3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a8, Sq::a2, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a8, Sq::a1, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a8, Sq::b8, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a8, Sq::c8, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a8, Sq::d8, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::e8, Sq::d8, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::e8, Sq::e7, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::e8, Sq::f7, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::f8, Sq::e7, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::f8, Sq::d6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::f8, Sq::c5, MoveType::Normal, Piece::Pawn}));
}

//=============================================================================
TEST(MoveGeneratorTest, CandidateMoves3) 
{
   Board b;
   State s;
   setBoard2(b, s);
   MoveGenerator gen(b,s);
   MoveExecutor exec(b, s);

   std::vector<Move> moves;
   gen(std::back_inserter(moves));
   EXPECT_EQ(moves.size(), 17);
   EXPECT_TRUE(contains(moves, Move{Sq::d7, Sq::c7, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d7, Sq::c8, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d7, Sq::d8, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d7, Sq::e8, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d7, Sq::e7, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d7, Sq::e6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d7, Sq::c6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d6, Sq::c5, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d6, Sq::c7, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d6, Sq::b8, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d6, Sq::e7, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d6, Sq::f8, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d6, Sq::e5, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d6, Sq::f4, MoveType::Normal, Piece::Pawn}));
   EXPECT_TRUE(contains(moves, Move{Sq::h5, Sq::h4, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::e4, Sq::e3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::e4, Sq::f3, MoveType::EnPassant, Piece::Pawn}));

   exec.move(Move{Sq::e4, Sq::f3, MoveType::EnPassant, Piece::Pawn});

   moves.clear();
   gen(std::back_inserter(moves));
   EXPECT_EQ(moves.size(), 20);
   EXPECT_TRUE(contains(moves, Move{Sq::b3, Sq::c3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::b3, Sq::d3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::b3, Sq::e3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::b3, Sq::f3, MoveType::Normal, Piece::Pawn}));
   EXPECT_TRUE(contains(moves, Move{Sq::b3, Sq::b2, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::b3, Sq::b1, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::b3, Sq::a3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::b3, Sq::b4, MoveType::Normal, Piece::Pawn}));
   EXPECT_TRUE(contains(moves, Move{Sq::h1, Sq::h2, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::h1, Sq::h3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::h1, Sq::h4, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::h1, Sq::h5, MoveType::Normal, Piece::Pawn}));
   EXPECT_TRUE(contains(moves, Move{Sq::h1, Sq::g1, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::h1, Sq::f1, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::e1, Sq::d1, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::e1, Sq::d2, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::e1, Sq::e2, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::e1, Sq::f2, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::e1, Sq::f1, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::e1, Sq::g1, MoveType::ShortCastle}));
}

//=============================================================================
TEST(MoveGeneratorTest, CandidateMoves4) 
{
   Board b;
   State s;
   setBoard3(b, s);
   MoveGenerator gen(b,s);
   MoveExecutor exec(b, s);

   std::vector<Move> moves;
   gen(std::back_inserter(moves));
   EXPECT_EQ(moves.size(), 22);
   EXPECT_TRUE(contains(moves, Move{Sq::d8, Sq::e8, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d8, Sq::e7, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d8, Sq::d7, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d8, Sq::c8, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::c7, Sq::c6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::c7, Sq::c5, MoveType::DoubleAdvance}));
   EXPECT_TRUE(contains(moves, Move{Sq::a7, Sq::a6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::a7, Sq::a5, MoveType::DoubleAdvance}));
   EXPECT_TRUE(contains(moves, Move{Sq::g5, Sq::h3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::g5, Sq::f3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::g5, Sq::e4, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::g5, Sq::e6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::g5, Sq::f7, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::g5, Sq::h7, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::b2, Sq::b1, MoveType::KnightPromotion}));
   EXPECT_TRUE(contains(moves, Move{Sq::b2, Sq::b1, MoveType::BishopPromotion}));
   EXPECT_TRUE(contains(moves, Move{Sq::b2, Sq::b1, MoveType::RookPromotion}));
   EXPECT_TRUE(contains(moves, Move{Sq::b2, Sq::b1, MoveType::QueenPromotion}));
   EXPECT_TRUE(contains(moves, Move{Sq::b2, Sq::a1, MoveType::KnightPromotion, Piece::Rook}));
   EXPECT_TRUE(contains(moves, Move{Sq::b2, Sq::a1, MoveType::BishopPromotion, Piece::Rook}));
   EXPECT_TRUE(contains(moves, Move{Sq::b2, Sq::a1, MoveType::RookPromotion, Piece::Rook}));
   EXPECT_TRUE(contains(moves, Move{Sq::b2, Sq::a1, MoveType::QueenPromotion, Piece::Rook}));

   exec.move(Move{Sq::b2, Sq::a1, MoveType::KnightPromotion, Piece::Rook});

   moves.clear();
   gen(std::back_inserter(moves));
   EXPECT_EQ(moves.size(), 14);
   EXPECT_TRUE(contains(moves, Move{Sq::g7, Sq::g8, MoveType::KnightPromotion}));
   EXPECT_TRUE(contains(moves, Move{Sq::g7, Sq::g8, MoveType::BishopPromotion}));
   EXPECT_TRUE(contains(moves, Move{Sq::g7, Sq::g8, MoveType::RookPromotion}));
   EXPECT_TRUE(contains(moves, Move{Sq::g7, Sq::g8, MoveType::QueenPromotion}));
   EXPECT_TRUE(contains(moves, Move{Sq::e5, Sq::e6, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::b3, Sq::b4, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d2, Sq::c1, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d2, Sq::c2, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d2, Sq::c3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d2, Sq::d1, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d2, Sq::d3, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d2, Sq::e1, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d2, Sq::e2, MoveType::Normal}));
   EXPECT_TRUE(contains(moves, Move{Sq::d2, Sq::e3, MoveType::Normal}));
}

//=============================================================================
TEST(MoveGeneratorTest, BlockedCastles1) 
{
   Board b;
   State s;
   setCastleBoard1(b, s);
   MoveGenerator gen(b,s);
   MoveExecutor exec(b, s);

   std::vector<Move> moves;
   gen(std::back_inserter(moves));
   EXPECT_FALSE(contains(moves, Move{Sq::e8, Sq::g8, MoveType::ShortCastle}));
   EXPECT_FALSE(contains(moves, Move{Sq::e8, Sq::c8, MoveType::LongCastle}));

   exec.move(Move{Sq::a8, Sq::a4, MoveType::Normal});
   moves.clear();
   gen(std::back_inserter(moves));
   EXPECT_FALSE(contains(moves, Move{Sq::e1, Sq::g1, MoveType::ShortCastle}));
   EXPECT_FALSE(contains(moves, Move{Sq::e1, Sq::c1, MoveType::LongCastle}));
}

//=============================================================================
TEST(MoveGeneratorTest, BlockedCastles2) 
{
   Board b;
   State s;
   setCastleBoard2(b, s);
   MoveGenerator gen(b,s);
   MoveExecutor exec(b, s);

   std::vector<Move> moves;
   gen(std::back_inserter(moves));
   EXPECT_FALSE(contains(moves, Move{Sq::e1, Sq::g1, MoveType::ShortCastle}));
   EXPECT_TRUE(contains(moves, Move{Sq::e1, Sq::c1, MoveType::LongCastle}));

   exec.move(Move{Sq::f4, Sq::g3, MoveType::Normal});
   moves.clear();
   gen(std::back_inserter(moves));
   EXPECT_FALSE(contains(moves, Move{Sq::e8, Sq::g8, MoveType::ShortCastle}));
   EXPECT_TRUE(contains(moves, Move{Sq::e8, Sq::c8, MoveType::LongCastle}));
}

//=============================================================================
TEST(MoveGeneratorTest, BlockedCastles3) 
{
   Board b;
   State s;
   setCastleBoard3(b, s);
   MoveGenerator gen(b,s);
   MoveExecutor exec(b, s);

   std::vector<Move> moves;
   gen(std::back_inserter(moves));
   EXPECT_FALSE(gen.isInCheck(Colour::White));
   EXPECT_TRUE(gen.isInCheck(Colour::Black));
   EXPECT_FALSE(contains(moves, Move{Sq::e1, Sq::g1, MoveType::ShortCastle}));
   EXPECT_FALSE(contains(moves, Move{Sq::e1, Sq::c1, MoveType::LongCastle}));

   exec.move(Move{Sq::d2, Sq::d7, MoveType::Normal, Piece::Pawn});
   moves.clear();
   gen(std::back_inserter(moves));
   EXPECT_TRUE(gen.isInCheck(Colour::White));
   EXPECT_FALSE(gen.isInCheck(Colour::Black));
   EXPECT_FALSE(contains(moves, Move{Sq::e8, Sq::g8, MoveType::ShortCastle}));
   EXPECT_FALSE(contains(moves, Move{Sq::e8, Sq::c8, MoveType::LongCastle}));
}

//=============================================================================
TEST(MoveGeneratorTest, InCheck1) 
{
   Board b;
   State s;
   setCheckBoard1(b, s);
   MoveGenerator gen(b,s);

   EXPECT_TRUE(gen.isInCheck(Colour::Black));
   EXPECT_FALSE(gen.isInCheck(Colour::White));
}

//=============================================================================
TEST(MoveGeneratorTest, InCheck2) 
{
   Board b;
   State s;
   setCheckBoard2(b, s);
   MoveGenerator gen(b,s);

   EXPECT_TRUE(gen.isInCheck(Colour::Black));
   EXPECT_FALSE(gen.isInCheck(Colour::White));
}

//=============================================================================
TEST(MoveGeneratorTest, InCheck3) 
{
   Board b;
   State s;
   setCheckBoard3(b, s);
   MoveGenerator gen(b,s);

   EXPECT_TRUE(gen.isInCheck(Colour::Black));
   EXPECT_TRUE(gen.isInCheck(Colour::White));
}

//=============================================================================
TEST(MoveGeneratorTest, InCheck4) 
{
   Board b;
   State s;
   setCheckBoard4(b, s);
   MoveGenerator gen(b,s);

   EXPECT_TRUE(gen.isInCheck(Colour::Black));
   EXPECT_TRUE(gen.isInCheck(Colour::White));
}

//=============================================================================
TEST(MoveGeneratorTest, Outputting) 
{
   Board b;
   State s;

   MoveGenerator gen1(b,s);
   MoveIntGenerator gen2(b,s);
   MoveANGenerator gen3(b,s);

   std::vector<Move> moves;
   gen1(std::back_inserter(moves));
   EXPECT_EQ(moves.size(), 20);

   std::vector<Move> moves2(20);
   gen1(moves2.begin());
   EXPECT_EQ(moves2, moves);

   std::list<MoveInt> moveints;
   gen2(std::front_inserter(moveints));
   EXPECT_EQ(moveints.size(), 20);

   MoveInt movearr[20];
   gen2(movearr);
   EXPECT_EQ(movearr[19], moveints.front());

   std::deque<MoveAN> movestrs;
   gen3(std::insert_iterator(movestrs, movestrs.begin()));
   EXPECT_EQ(movestrs.size(), 20);

   std::ostringstream movestream;
   gen3(std::ostream_iterator<MoveAN>(movestream));
   EXPECT_EQ(movestream.str().size(), 5*20);
}