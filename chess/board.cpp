#include "board.h"

namespace Chess
{

//=============================================================================
Board::Board()
{
   setDefault();
}

//=============================================================================
void Board::setEmpty(Square sq)
{
   colour_[sq] == Colour::White ? wPieces_.remove(sq) : bPieces_.remove(sq);
   board_[sq]  = PieceType::Empty;
   colour_[sq] = Colour::Empty;
}

//=============================================================================
void Board::setPiece(Square sq, PieceType piece, Colour color)
{
   color == Colour::White ? wPieces_.insert(sq) : bPieces_.insert(sq);
   board_[sq]  = piece;
   colour_[sq] = color;
}

//=============================================================================
void Board::promote(Square sq, PieceType piece)
{
   board_[sq]  = piece;
}

//=============================================================================
void Board::move(Square from, Square to)
{
   if (colour_[to] != Colour::Empty)
   {
      colour_[to] == Colour::White ? wPieces_.remove(to) : bPieces_.remove(to);
   }
   colour_[from] == Colour::White ? wPieces_.replace(from, to) : bPieces_.replace(from, to);

   board_[to]    = board_[from];
   colour_[to]   = colour_[from];
   board_[from]  = PieceType::Empty;
   colour_[from] = Colour::Empty;


   updateKing(to);
}

//=============================================================================
void Board::setEmpty()
{
   board_.fill(PieceType::Empty);
   colour_.fill(Colour::Empty);
   WKing_ = Sq::Invalid;
   BKing_ = Sq::Invalid;
   wPieces_.setEmpty();
   bPieces_.setEmpty();
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

   WKing_ = Sq::e1;
   BKing_ = Sq::e8;
   wPieces_.setWDefault();
   bPieces_.setBDefault();
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

