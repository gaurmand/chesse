#ifndef CHESS_MAILBOX_H
#define CHESS_MAILBOX_H

#include "square.h"

namespace Chess
{

constexpr int MAILBOX_SIZE = 120;

// Maps mailbox num to a value x such that x > 0 == valid square
constexpr int mailbox[MAILBOX_SIZE] = 
{
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
   -1, 56, 57, 58, 59, 60, 61, 62, 63, -1,
   -1, 48, 49, 50, 51, 52, 53, 54, 55, -1,
   -1, 40, 41, 42, 43, 44, 45, 46, 47, -1,
   -1, 32, 33, 34, 35, 36, 37, 38, 39, -1,
   -1, 24, 25, 26, 27, 28, 29, 30, 31, -1,
   -1, 16, 17, 18, 19, 20, 21, 22, 23, -1,
   -1,  8,  9, 10, 11, 12, 13, 14, 15, -1,
   -1,  0,  1,  2,  3,  4,  5,  6,  7, -1,
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

// Maps square to mailbox num
constexpr int mailboxNum[NUM_SQUARES] = 
{
   91, 92, 93, 94, 95, 96, 97, 98,
   81, 82, 83, 84, 85, 86, 87, 88,
   71, 72, 73, 74, 75, 76, 77, 78,
   61, 62, 63, 64, 65, 66, 67, 68,
   51, 52, 53, 54, 55, 56, 57, 58,
   41, 42, 43, 44, 45, 46, 47, 48,
   31, 32, 33, 34, 35, 36, 37, 38,
   21, 22, 23, 24, 25, 26, 27, 28,
};

// Directions corresponding to 12x10 mailbox board
enum Direction
{
   U   = -10,  // UP
   D   = 10,   // DOWN
   L   = -1,   // LEFT
   R   = 1,    // RIGHT
   UL  = -11,  // UP LEFT
   UR  = -9,   // UP RIGHT
   DR  = 11,   // DOWN RIGHT
   DL  = 9,    // DOWN LEFT
   HUL = -21,  // HOOK UP LEFT
   HUR = -19,  // HOOK UP RIGHT
   HRU = -8,   // HOOK RIGHT UP
   HRD = 12,   // HOOK RIGHT DOWN
   HDR = 21,   // HOOK DOWN RIGHT
   HDL = 19,   // HOOK DOWN LEFT
   HLD = 8,    // HOOK LEFT DOWN
   HLU = -12   // HOOK LEFT UP
};

// Assumes 0 <= sq < 64
// Assumes 0 <= mailboxIndex[sq] + offset < 120 
// Returns square relative to sq in direction of offset or -1 if it's not a valid square.
inline int squareAt(Square sq, Direction offset)
{
   return mailbox[mailboxNum[sq] + offset];
}

// Returns true if sq is a valid square
inline bool isValid(Square sq) { return sq < NUM_SQUARES; }

// Returns true if square relative to sq in direction of offset is a valid square
inline bool isValid(Square sq, Direction offset)
{
   return squareAt(sq, offset) != Sq::Invalid;
}

}  // namespace Chess

#endif   // CHESS_MAILBOX_H