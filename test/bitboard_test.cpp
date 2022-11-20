#include <gtest/gtest.h>

#include "chess/bitboard.h"

using namespace Chess;

//=============================================================================
TEST(BitboardTest, Constructor) 
{
   Bitboard b(0xF0F0F0F0F0F0F0F0ull);
   EXPECT_EQ(b.to_uint(), 0xF0F0F0F0F0F0F0F0ull);
}

//=============================================================================
TEST(BitboardTest, BitwiseOperators) 
{
   Bitboard b1(0xF0F0F0F0F0F0F0F0ull);
   Bitboard b2(0x0F0F0F0F0F0F0F0Full);
   EXPECT_EQ(b1 | b2, Bitboard(kFullBoard));
   EXPECT_EQ(b1 & b2, Bitboard(kEmptyBoard));
   EXPECT_EQ(~b1, b2);

   Bitboard c1(0xF0F0F0F0F0F0F0F0ull);
   Bitboard c2(0xF0F0F0F00F0F0F0Full);
   EXPECT_EQ(c1 ^ c2, Bitboard(0x00000000FFFFFFFFull));
}

//=============================================================================
TEST(BitboardTest, Test) 
{
   Bitboard b = kFullBoard;
   for (Square sq = Sq::a1; sq <= Sq::h8; sq++)
   {
      EXPECT_TRUE(b.test(sq));
   }

   b = kEmptyBoard;
   for (Square sq = Sq::a1; sq <= Sq::h8; sq++)
   {
      EXPECT_FALSE(b.test(sq));
   }

   b = 0b10000000'01000000'00100000'00010000'00001000'00000100'00000010'00000001;
   EXPECT_TRUE(b.test(Sq::h8));
   EXPECT_TRUE(b.test(Sq::g7));
   EXPECT_TRUE(b.test(Sq::f6));
   EXPECT_TRUE(b.test(Sq::e5));
   EXPECT_TRUE(b.test(Sq::d4));
   EXPECT_TRUE(b.test(Sq::c3));
   EXPECT_TRUE(b.test(Sq::b2));
   EXPECT_TRUE(b.test(Sq::a1));
   EXPECT_FALSE(b.test(Sq::h1));
   EXPECT_FALSE(b.test(Sq::g2));
   EXPECT_FALSE(b.test(Sq::f3));
   EXPECT_FALSE(b.test(Sq::e4));
   EXPECT_FALSE(b.test(Sq::d5));
   EXPECT_FALSE(b.test(Sq::c6));
   EXPECT_FALSE(b.test(Sq::b7));
   EXPECT_FALSE(b.test(Sq::a8));
}

//=============================================================================
TEST(BitboardTest, Count) 
{
   Bitboard b = kFullBoard;
   EXPECT_EQ(b.count(), 64);

   b = kEmptyBoard;
   EXPECT_EQ(b.count(), 0);

   b = 0b10000000'01000000'00100000'00010000'00001000'00000100'00000010'00000001ull;
   EXPECT_EQ(b.count(), 8);

   b = 0x8421842184218421ull;
   EXPECT_EQ(b.count(), 16);
}

//=============================================================================
TEST(BitboardTest, AnyNoneAll) 
{
   Bitboard b = kFullBoard;
   EXPECT_TRUE(b.any());
   EXPECT_FALSE(b.none());
   EXPECT_TRUE(b.all());

   b = kEmptyBoard;
   EXPECT_FALSE(b.any());
   EXPECT_TRUE(b.none());
   EXPECT_FALSE(b.all());

   b = 0x8421842184218421ull;
   EXPECT_TRUE(b.any());
   EXPECT_FALSE(b.none());
   EXPECT_FALSE(b.all());

   b = 0x1000000;
   EXPECT_TRUE(b.any());
   EXPECT_FALSE(b.none());
   EXPECT_FALSE(b.all());
}

//=============================================================================
TEST(BitboardTest, SetResetToggle) 
{
   Bitboard b1 = kEmptyBoard;
   Bitboard b2 = kEmptyBoard;
   for (Square sq = Sq::a1; sq <= Sq::h8; sq++)
   {
      b1.set(sq);
      b2.toggle(sq);
   }
   EXPECT_EQ(b1, 0xFFFFFFFFFFFFFFFFull);
   EXPECT_EQ(b2, 0xFFFFFFFFFFFFFFFFull);

   for (Square sq = Sq::a1; sq <= Sq::h8; sq++)
   {
      b1.reset(sq);
      b2.toggle(sq);
   }
   EXPECT_EQ(b1, 0);
   EXPECT_EQ(b2, 0);

   b1 = 0x80000000;
   b1.toggle(Sq::h4);
   b1.toggle(Sq::a1);
   EXPECT_EQ(b1, 1);

   b2 = 0x80000000;
   b2.reset(Sq::h4);
   b2.set(Sq::a1);
   EXPECT_EQ(b2, 1);
}

//=============================================================================
TEST(BitboardTest, Iterator) 
{
   Bitboard b = kFullBoard;
   auto i = b.begin();
   auto end = b.end();
   EXPECT_NE(i, end);
   for (Square sq = Sq::a1; sq <= Sq::h8; sq++)
   {
      EXPECT_EQ(*i, sq);
      ++i;
   }
   EXPECT_EQ(i, end);

   b = kEmptyBoard;
   i = b.begin();
   end = b.end();
   EXPECT_EQ(i, end);

   b = 0b10000000'01000000'00100000'00010000'00001000'00000100'00000010'00000001ull;
   i = b.begin();
   end = b.end();
   EXPECT_NE(i, end);
   EXPECT_EQ(*i, Sq::a1);
   ++i;
   EXPECT_EQ(*i, Sq::b2);
   ++i;
   EXPECT_EQ(*i, Sq::c3);
   ++i;
   EXPECT_EQ(*i, Sq::d4);
   ++i;
   EXPECT_EQ(*i, Sq::e5);
   ++i;
   EXPECT_EQ(*i, Sq::f6);
   ++i;
   EXPECT_EQ(*i, Sq::g7);
   ++i;
   EXPECT_EQ(*i, Sq::h8);
   ++i;
   EXPECT_EQ(i, end);
}

//=============================================================================
TEST(BitboardTest, ForLoops) 
{
   Bitboard b = kFullBoard;
   int count = 0;
   for (auto i = b.begin(); i != b.end(); ++i)
   {
      count++;
   }
   EXPECT_EQ(count, 64);

   b = kEmptyBoard;
   count = 0;
   for (auto i = b.begin(); i != b.end(); ++i)
   {
      count++;
   }
   EXPECT_EQ(count, 0);

   b = 0b10000000'01000000'00100000'00010000'00001000'00000100'00000010'00000001ull;
   count = 0;
   for (auto i = b.begin(); i != b.end(); ++i)
   {
      count++;
   }
   EXPECT_EQ(count, 8);
}

//=============================================================================
TEST(BitboardTest, RangeBasedForLoop) 
{
   Bitboard b = kFullBoard;
   int count = 0;
   for (const Square sq : b)
   {
      EXPECT_EQ(count, sq);
      count++;
   }
   EXPECT_EQ(count, 64);

   b = kEmptyBoard;
   count = 0;
   for (const Square sq : b)
   {
      EXPECT_EQ(sq, 1);
      count++;
   }
   EXPECT_EQ(count, 0);

   b = 0b10000000'01000000'00100000'00010000'00001000'00000100'00000010'00000001ull;
   count = 0;
   static const std::array<Square, 8> expected = {
      Sq::a1, Sq::b2, Sq::c3, Sq::d4, Sq::e5, Sq::f6, Sq::g7, Sq::h8
   };
   for (const Square sq : b)
   {
      EXPECT_EQ(expected[count], sq);
      count++;
   }
   EXPECT_EQ(count, 8);
}
