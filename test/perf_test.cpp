#include <gtest/gtest.h>

//#define NDEBUG 
#include "test_helper.h"
#include "chess/game.h"

using namespace Chess;

//=============================================================================
TEST(PerfTest, perft1) 
{
   Game g;
   ASSERT_EQ(perft(g, 0), 1);
   ASSERT_EQ(perft(g, 1), 20);
   ASSERT_EQ(perft(g, 2), 400);
   ASSERT_EQ(perft(g, 3), 8902);
   ASSERT_EQ(perft(g, 4), 197281);
   // ASSERT_EQ(perft(g, 5), 4865609);  // ~4 s
   // ASSERT_EQ(perft(6), 119060324); // ~80 s
   // ASSERT_EQ(perft(7), 3195901860); // ~40 min
}

//=============================================================================
TEST(PerfTest, perft2) 
{
   Board b;
   State s;
   setBoard1(b, s);
   Game g(b, s);

   ASSERT_EQ(perft(g, 0), 1);
   ASSERT_EQ(perft(g, 1), 33);
   ASSERT_EQ(perft(g, 2), 1239);
   ASSERT_EQ(perft(g, 3), 38045);
   // ASSERT_EQ(perft(g, 4), 1384295); // ~ 1 s
   // ASSERT_EQ(perft(g, 5), 42246350);  // ~30 s
   // ASSERT_EQ(perft(g, 6), 1512653084); // ?
   // ASSERT_EQ(perft(g, 7), ?); // ?
}

//=============================================================================
TEST(PerfTest, perft3) 
{
   Board b;
   State s;
   setBoard2(b, s);
   Game g(b, s);

   ASSERT_EQ(perft(g, 0), 1);
   ASSERT_EQ(perft(g, 1), 15);
   ASSERT_EQ(perft(g, 2), 339);
   ASSERT_EQ(perft(g, 3), 5087);
   ASSERT_EQ(perft(g, 4), 114341);
   // ASSERT_EQ(perft(g, 5), 1711073); // ~2 s
   // ASSERT_EQ(perft(g, 6), 38626459); // ~30 s
   // ASSERT_EQ(perft(g, 7), 573577803); // ?
}

//=============================================================================
TEST(PerfTest, perft4) 
{
   Board b;
   State s;
   setBoard3(b, s);
   Game g(b, s);

   ASSERT_EQ(perft(g, 0), 1);
   ASSERT_EQ(perft(g, 1), 22);
   ASSERT_EQ(perft(g, 2), 428);
   ASSERT_EQ(perft(g, 3), 7913);
   ASSERT_EQ(perft(g, 4), 144166);
   // ASSERT_EQ(perft(g, 5), 2580697); // ~2 s
   // ASSERT_EQ(perft(g, 6), 47740638); // ~42 s
   // ASSERT_EQ(perft(g, 7), 861185017); // ?
}

//=============================================================================
TEST(PerfTest, perft5) 
{
   Board b;
   State s;
   setCastleBoard1(b, s);
   Game g(b, s);

   // ASSERT_EQ(perft(g, 0), 1);
   // ASSERT_EQ(perft(g, 1), 23);
   // ASSERT_EQ(perft(g, 2), 705);
   // ASSERT_EQ(perft(g, 3), 16132);
   // ASSERT_EQ(perft(g, 4), 561747);
   ASSERT_EQ(perft(g, 5), 13957722); // ~13 s
   // ASSERT_EQ(perft(g, 6), 514665849); // ?
   // ASSERT_EQ(perft(g, 7), ?); // ?
}

//=============================================================================
TEST(PerfTest, perft6) 
{
   Board b;
   State s;
   setCastleBoard2(b, s);
   Game g(b, s);

   ASSERT_EQ(perft(g, 0), 1);
   ASSERT_EQ(perft(g, 1), 41);
   ASSERT_EQ(perft(g, 2), 910);
   ASSERT_EQ(perft(g, 3), 31136);
   ASSERT_EQ(perft(g, 4), 663299);
   // ASSERT_EQ(perft(g, 5), 21810932); // ~20 s
   // ASSERT_EQ(perft(g, 6), 467876911); // ?
}


//=============================================================================
TEST(PerfTest, perft7) 
{
   Board b;
   State s;
   setCastleBoard3(b, s);
   Game g(b, s);

   ASSERT_EQ(perft(g, 0), 1);
   ASSERT_EQ(perft(g, 1), 6);
   ASSERT_EQ(perft(g, 2), 106);
   ASSERT_EQ(perft(g, 3), 3124);
   ASSERT_EQ(perft(g, 4), 49202);
   // ASSERT_EQ(perft(g, 5), 1461806); // ~1s
   // ASSERT_EQ(perft(g, 6), 27845638); // ~20 s
   // ASSERT_EQ(perft(g, 7), 813293474); // ?
}

//=============================================================================
TEST(PerfTest, perft8) 
{
   Board b;
   State s;
   setCheckBoard1(b, s);
   Game g(b, s);

   ASSERT_EQ(perft(g, 0), 1);
   ASSERT_EQ(perft(g, 1), 5);
   ASSERT_EQ(perft(g, 2), 27);
   ASSERT_EQ(perft(g, 3), 181);
   ASSERT_EQ(perft(g, 4), 1741);
   ASSERT_EQ(perft(g, 5), 13996);
   ASSERT_EQ(perft(g, 6), 152941);
   // ASSERT_EQ(perft(g, 7), 1369328); // ~2 s
   // ASSERT_EQ(perft(g, 8), 17161061); // ~18 s
}

//=============================================================================
TEST(PerfTest, perft9) 
{
   Board b;
   State s;
   setCheckBoard2(b, s);
   Game g(b, s);

   ASSERT_EQ(perft(g, 0), 1);
   ASSERT_EQ(perft(g, 1), 4);
   ASSERT_EQ(perft(g, 2), 136);
   ASSERT_EQ(perft(g, 3), 1408);
   ASSERT_EQ(perft(g, 4), 38538);
   ASSERT_EQ(perft(g, 5), 448727);
   // ASSERT_EQ(perft(g, 6), 12019454); // ~10 s
   // ASSERT_EQ(perft(g, 7), 149516141); // ?
}
