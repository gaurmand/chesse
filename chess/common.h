#ifndef CHESS_COMMON_H
#define CHESS_COMMON_H

#include <cstdint>

namespace Chess
{

constexpr int NUM_ROWS    = 8;
constexpr int NUM_COLS    = NUM_ROWS;
constexpr int NUM_SQUARES = NUM_ROWS * NUM_COLS;

enum class Colour : uint8_t {Empty, White, Black};
enum class Piece : uint8_t {Empty, King, Queen, Rook, Bishop, Knight, Pawn};
enum class MoveType : uint8_t {
   Invalid, Quiet, CapturePawn, CaptureKnight, CaptureBishop, CaptureRook, 
   CaptureQueen, LongCastle, ShortCastle, EnPassant, DoubleAdvance, 
   KnightPromotion, BishopPromotion, RookPromotion, QueenPromotion
};
enum class GameStatus {Incomplete, WhiteCheckmate, BlackCheckmate, Stalemate, Draw};

}  // namespace Chess


#endif   // CHESS_COMMON_H