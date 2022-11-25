#ifndef CHESS_COMMON_H
#define CHESS_COMMON_H

#include <cstdint>
#include <string>

namespace Chess
{

constexpr int kNumPieceTypes = 6;
constexpr int kNumColors     = 2;

enum class Colour : uint8_t {Empty, White, Black};
enum Color {White, Black, EmptyColor};
enum class Piece : uint8_t {Empty, King, Queen, Rook, Bishop, Knight, Pawn};
enum PieceType : uint8_t {Pawn, Knight, Bishop, Rook, Queen, King, EmptyPiece};
enum class MoveType : uint8_t {
   Invalid, Normal, LongCastle, ShortCastle, EnPassant, DoubleAdvance, 
   KnightPromotion, BishopPromotion, RookPromotion, QueenPromotion
};
enum class GameStatus {Incomplete, WhiteCheckmate, BlackCheckmate, Stalemate, Draw};

using FEN = std::string;


inline Color opposite(Color c) { return c == Color::White ? Color::Black : Color::White; }

}  // namespace Chess


#endif   // CHESS_COMMON_H