#ifndef CHESS_COMMON_H
#define CHESS_COMMON_H

#include <cstdint>

namespace Chess
{

enum class Colour : uint8_t {Empty, White, Black};
enum class Piece : uint8_t {Empty, King, Queen, Rook, Bishop, Knight, Pawn};
enum class MoveType : uint8_t {
   Invalid, Normal, LongCastle, ShortCastle, EnPassant, DoubleAdvance, 
   KnightPromotion, BishopPromotion, RookPromotion, QueenPromotion
};
enum class GameStatus {Incomplete, WhiteCheckmate, BlackCheckmate, Stalemate, Draw};

inline Colour enemy(Colour c) { return c == Colour::White ? Colour::Black : Colour::White; }

}  // namespace Chess


#endif   // CHESS_COMMON_H