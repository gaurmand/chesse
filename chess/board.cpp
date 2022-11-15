#include "board.h"

namespace Chess
{

//=============================================================================
Board::Board()
{
   setDefault();
}

//=============================================================================
void Board::setEmpty(Square sqr)
{
   board_[sqr] = PieceType::Empty;
   colour_[sqr] = Colour::Empty;
}

//=============================================================================
void Board::setPiece(Square sqr, PieceType piece, Colour color)
{
   board_[sqr] = piece;
   colour_[sqr] = color;
}

//=============================================================================
void Board::move(Square from, Square to)
{
   board_[to] = board_[from];
   colour_[to] = colour_[from];
   setEmpty(from);
   updateKing(to);
}

//=============================================================================
void Board::setEmpty()
{
   board_.fill(PieceType::Empty);
   colour_.fill(Colour::Empty);
   WKing_ = Sq::Invalid;
   BKing_ = Sq::Invalid;
}

//=============================================================================
void Board::setDefault()
{
   using P = PieceType;
   using C = Colour;

   board_ = {
      P::Rook,  P::Knight, P::Bishop, P::Queen, P::King,  P::Bishop, P::Knight, P::Rook,
      P::Pawn,  P::Pawn,   P::Pawn,   P::Pawn,  P::Pawn,  P::Pawn,   P::Pawn,   P::Pawn,
      P::Empty, P::Empty,  P::Empty,  P::Empty, P::Empty, P::Empty,  P::Empty,  P::Empty,
      P::Empty, P::Empty,  P::Empty,  P::Empty, P::Empty, P::Empty,  P::Empty,  P::Empty,
      P::Empty, P::Empty,  P::Empty,  P::Empty, P::Empty, P::Empty,  P::Empty,  P::Empty,
      P::Empty, P::Empty,  P::Empty,  P::Empty, P::Empty, P::Empty,  P::Empty,  P::Empty,
      P::Pawn,  P::Pawn,   P::Pawn,   P::Pawn,  P::Pawn,  P::Pawn,   P::Pawn,   P::Pawn,
      P::Rook,  P::Knight, P::Bishop, P::Queen, P::King,  P::Bishop, P::Knight, P::Rook
   };

   colour_ = {
      C::White, C::White, C::White, C::White, C::White, C::White, C::White, C::White,
      C::White, C::White, C::White, C::White, C::White, C::White, C::White, C::White,
      C::Empty, C::Empty, C::Empty, C::Empty, C::Empty, C::Empty, C::Empty, C::Empty,
      C::Empty, C::Empty, C::Empty, C::Empty, C::Empty, C::Empty, C::Empty, C::Empty,
      C::Empty, C::Empty, C::Empty, C::Empty, C::Empty, C::Empty, C::Empty, C::Empty,
      C::Empty, C::Empty, C::Empty, C::Empty, C::Empty, C::Empty, C::Empty, C::Empty,
      C::Black, C::Black, C::Black, C::Black, C::Black, C::Black, C::Black, C::Black,
      C::Black, C::Black, C::Black, C::Black, C::Black, C::Black, C::Black, C::Black
   };
}

//=============================================================================
bool Board::operator==(const Board& rhs) const
{
   return board_ == rhs.board_ && colour_ == rhs.colour_;
}

//=============================================================================
bool Board::operator!=(const Board& rhs) const
{
   return !(*this == rhs);
}

//=============================================================================
void Board::updateKings()
{
   for (Square i = Sq::a1; i <= Sq::h8; ++i)
   {
      updateKing(i);
   }
}

//=============================================================================
void Board::updateKing(Square to)
{
   if (board_[to] == PieceType::King)
   {
      colour_[to] == Colour::White ? WKing_ = to : BKing_ = to;
   }
}

}  // namespace Chess

