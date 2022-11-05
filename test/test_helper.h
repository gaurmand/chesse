#ifndef TEST_HELPER_H
#define TEST_HELPER_H

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

#endif   // TEST_HELPER_H