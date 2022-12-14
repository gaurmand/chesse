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
   board_[sqr] = Piece::Empty;
   colour_[sqr] = Colour::Empty;
}

//=============================================================================
void Board::setPiece(Square sqr, Piece piece, Colour color)
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
   board_.fill(Piece::Empty);
   colour_.fill(Colour::Empty);
   WKing_ = Sq::Invalid;
   BKing_ = Sq::Invalid;
}

//=============================================================================
void Board::setDefault()
{
   board_ = {
      Piece::Rook,  Piece::Knight, Piece::Bishop, Piece::Queen, Piece::King,  Piece::Bishop, Piece::Knight, Piece::Rook,
      Piece::Pawn,  Piece::Pawn,   Piece::Pawn,   Piece::Pawn,  Piece::Pawn,  Piece::Pawn,   Piece::Pawn,   Piece::Pawn,
      Piece::Empty, Piece::Empty,  Piece::Empty,  Piece::Empty, Piece::Empty, Piece::Empty,  Piece::Empty,  Piece::Empty,
      Piece::Empty, Piece::Empty,  Piece::Empty,  Piece::Empty, Piece::Empty, Piece::Empty,  Piece::Empty,  Piece::Empty,
      Piece::Empty, Piece::Empty,  Piece::Empty,  Piece::Empty, Piece::Empty, Piece::Empty,  Piece::Empty,  Piece::Empty,
      Piece::Empty, Piece::Empty,  Piece::Empty,  Piece::Empty, Piece::Empty, Piece::Empty,  Piece::Empty,  Piece::Empty,
      Piece::Pawn,  Piece::Pawn,   Piece::Pawn,   Piece::Pawn,  Piece::Pawn,  Piece::Pawn,   Piece::Pawn,   Piece::Pawn,
      Piece::Rook,  Piece::Knight, Piece::Bishop, Piece::Queen, Piece::King,  Piece::Bishop, Piece::Knight, Piece::Rook
   };

   colour_ = {
      Colour::White, Colour::White, Colour::White, Colour::White, Colour::White, Colour::White, Colour::White, Colour::White,
      Colour::White, Colour::White, Colour::White, Colour::White, Colour::White, Colour::White, Colour::White, Colour::White,
      Colour::Empty, Colour::Empty, Colour::Empty, Colour::Empty, Colour::Empty, Colour::Empty, Colour::Empty, Colour::Empty,
      Colour::Empty, Colour::Empty, Colour::Empty, Colour::Empty, Colour::Empty, Colour::Empty, Colour::Empty, Colour::Empty,
      Colour::Empty, Colour::Empty, Colour::Empty, Colour::Empty, Colour::Empty, Colour::Empty, Colour::Empty, Colour::Empty,
      Colour::Empty, Colour::Empty, Colour::Empty, Colour::Empty, Colour::Empty, Colour::Empty, Colour::Empty, Colour::Empty,
      Colour::Black, Colour::Black, Colour::Black, Colour::Black, Colour::Black, Colour::Black, Colour::Black, Colour::Black,
      Colour::Black, Colour::Black, Colour::Black, Colour::Black, Colour::Black, Colour::Black, Colour::Black, Colour::Black
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
   if (board_[to] == Piece::King)
   {
      colour_[to] == Colour::White ? WKing_ = to : BKing_ = to;
   }
}

}  // namespace Chess

