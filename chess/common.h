#ifndef CHESS_COMMON_H
#define CHESS_COMMON_H

#include <cstdint>

namespace Chess
{

enum class Colour : uint8_t {Empty, White, Black};
enum class PieceType : uint8_t {Empty, King, Queen, Rook, Bishop, Knight, Pawn};
enum class MoveType : uint8_t {
   Invalid, Normal, LongCastle, ShortCastle, EnPassant, DoubleAdvance, 
   KnightPromotion, BishopPromotion, RookPromotion, QueenPromotion
};
enum class GameStatus {Incomplete, WhiteCheckmate, BlackCheckmate, Stalemate, Draw};

}  // namespace Chess


#endif   // CHESS_COMMON_H