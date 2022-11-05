#include <gtest/gtest.h>

#include "test_helper.h"
#include "chess/board.h"
#include "chess/state.h"
#include "chess/game.h"

#include <vector>
#include <iterator>

using namespace Chess;

//=============================================================================
TEST(GameTest, DefaultConstructor) 
{
   Game g;
   EXPECT_EQ(g.board(), Board());
   EXPECT_EQ(g.state(), State());
}

//=============================================================================
TEST(GameTest, NormalConstructor) 
{
   Board b;
   State s;
   setBoard1(b, s);
   Game g(b, s);
   EXPECT_EQ(g.board(), b);
   EXPECT_EQ(g.state(), s);
}

//=============================================================================
TEST(GameTest, MoveAndUndo) 
{
   Board b;
   State s;
   setBoard1(b, s);
   Game g(b, s);

   Move m{Sq::c5, Sq::b6, MoveType::EnPassant, Piece::Pawn};
   g.move(m);
   EXPECT_NE(b, g.board());
   EXPECT_NE(s, g.state());

   g.undo(m, s);
   EXPECT_EQ(b, g.board());
   EXPECT_EQ(s, g.state());

   m = Move{Sq::e1, Sq::g1, MoveType::ShortCastle};
   g.move(m);
   EXPECT_NE(b, g.board());
   EXPECT_NE(s, g.state());

   g.undo(m, s);
   EXPECT_EQ(b, g.board());
   EXPECT_EQ(s, g.state());

   m = Move{Sq::a7, Sq::c7, MoveType::Normal, Piece::Queen};
   g.move(m);
   EXPECT_NE(b, g.board());
   EXPECT_NE(s, g.state());

   g.undo(m, s);
   EXPECT_EQ(b, g.board());
   EXPECT_EQ(s, g.state());
}

//=============================================================================
TEST(GameTest, GetMoves) 
{
   std::vector<MoveInt> moves;
   Game g;
   Board b;
   State s;

   g.moves(std::back_inserter(moves));
   EXPECT_EQ(moves.size(), 20);

   setBoard1(b, s);
   g.set(b, s);
   moves.clear();
   g.moves(std::back_inserter(moves));
   EXPECT_EQ(moves.size(), 34);

   setBoard2(b, s);
   g.set(b, s);
   moves.clear();
   g.moves(std::back_inserter(moves));
   EXPECT_EQ(moves.size(), 17);

   setBoard2(b, s);
   g.set(b, s);
   moves.clear();
   g.moves(std::back_inserter(moves));
   EXPECT_EQ(moves.size(), 17);

   setBoard3(b, s);
   g.set(b, s);
   moves.clear();
   g.moves(std::back_inserter(moves));
   EXPECT_EQ(moves.size(), 22);
}
