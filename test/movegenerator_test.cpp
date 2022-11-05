#include <gtest/gtest.h>

#include "chess/movegen/movegenerator.h"
#include "test_helper.h"

#include <iterator>
#include <vector>
#include <string>
#include <list>
#include <deque>
#include <sstream>

using namespace Chess;

//=============================================================================
TEST(MoveGeneratorTest, BasicUseCases) 
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