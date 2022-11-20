#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H

#include <cstdint>
#include <string>
#include <array>

namespace Chess
{

using Square = uint8_t;
using AN = std::string;

constexpr int NUM_ROWS    = 8;
constexpr int NUM_COLS    = NUM_ROWS;
constexpr int NUM_SQUARES = NUM_ROWS * NUM_COLS;

//=============================================================================
enum Sq : Square {
  a1, b1, c1, d1, e1, f1, g1, h1,
  a2, b2, c2, d2, e2, f2, g2, h2,
  a3, b3, c3, d3, e3, f3, g3, h3,
  a4, b4, c4, d4, e4, f4, g4, h4,
  a5, b5, c5, d5, e5, f5, g5, h5,
  a6, b6, c6, d6, e6, f6, g6, h6,
  a7, b7, c7, d7, e7, f7, g7, h7,
  a8, b8, c8, d8, e8, f8, g8, h8,
  Invalid
};

//=============================================================================
enum Rank : Square {r1, r2, r3, r4, r5, r6, r7, r8};
enum File : Square {a, b, c, d, e, f, g, h};
inline Square rank(Square sq) { return sq / NUM_COLS; }
inline Square file(Square sq) { return sq % NUM_COLS; }

//=============================================================================
Square fromAN(const AN& squareStr);
AN toAN(Square sqr);

//=============================================================================
constexpr int kNumRayDirs  = 8;
constexpr int kNumHookDirs = 8;

enum Ray {NW, N, NE, E, SE, S, SW, W};
enum Hook {WNW, NNW, NNE, ENE, ESE, SSE, SSW, WSW};

constexpr std::array<int, kNumRayDirs> rays   = {7, 8, 9, 1, -7, -8, -9, -1};
constexpr std::array<int, kNumHookDirs> hooks = {6, 15, 17, 10, -6, -15, -17, -10};

//=============================================================================
constexpr bool isValid(Square sq) { return sq < NUM_SQUARES; }

}  // namespace Chess


#endif   // CHESS_SQUARE_H