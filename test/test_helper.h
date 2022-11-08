#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include <algorithm>
#include <iterator>
#include <iostream>

namespace Chess
{
   class Board;
   class State;
}

// ============================================================================
// FEN: r3kb1N/Q1qn2p1/8/1pP4p/3Pp1b1/1P2P3/1P3P2/3RK2R w Kq b6 0 18
void setBoard1(Chess::Board& b, Chess::State& s);

// ============================================================================
// FEN: 8/3k4/3b4/3P3p/1p2pP2/1R6/8/4K2R b K f3 0 29
void setBoard2(Chess::Board& b, Chess::State& s);

// ============================================================================
// FEN: 3k4/p1p3P1/8/4P1n1/8/1P6/1p1K4/R7 b - - 0 318
void setBoard3(Chess::Board& b, Chess::State& s);

// ============================================================================
// FEN: r3k2r/2P5/7b/8/8/Q7/7n/R3K2R b KQkq - 2 35
void setCastleBoard1(Chess::Board& b, Chess::State& s);

// ============================================================================
// FEN: r3k3/8/1r6/8/5Q2/8/8/R3K3 w Qq - 0 41
void setCastleBoard2(Chess::Board& b, Chess::State& s);

// ============================================================================
// FEN: 4k2r/3P4/8/b7/8/8/3r4/R3K2R b KQk - 0 36
void setCastleBoard3(Chess::Board& b, Chess::State& s);

// ============================================================================
// FEN: 4k3/3P4/8/8/8/8/4p3/4K3 b - - 0 1
void setCheckBoard1(Chess::Board& b, Chess::State& s);

// ============================================================================
// FEN: 4k3/8/8/4Q3/8/8/3P2N1/2n1Kb2 b - - 0 1
void setCheckBoard2(Chess::Board& b, Chess::State& s);

// ============================================================================
// FEN: 4k3/8/8/7B/8/8/2n5/4K3 w - - 0 0
void setCheckBoard3(Chess::Board& b, Chess::State& s);

// ============================================================================
// FEN: 8/8/8/8/8/8/3k4/2K5 w - - 0 1
void setCheckBoard4(Chess::Board& b, Chess::State& s);

// ============================================================================
uint64_t perft(int depth);

// ============================================================================
template <typename Container>
bool contains(const Container& c, typename Container::const_reference v)
{
   return std::find(c.begin(), c.end(), v) != c.end();
}

// ============================================================================
template <typename Container>
void print(const Container& c)
{
   auto out = std::ostream_iterator<typename Container::value_type>(std::cout, "\n");
   std::copy(c.begin(), c.end(), out);
}

#endif   // TEST_HELPER_H