#include "moveexecutor.h"
#include "mailbox.h"

#include <cassert>

namespace Chess
{

void MoveExecutor::doMove(MoveInt move)
{
   Move mv;
   fromMoveInt(move, mv);

   updateBoard(mv);
   updateEnPassant(mv);
   updateCastling(mv);
   toggleColour();
}

/* 
NOTE: We cannot undo the state since we do not know:
- En passant state before any move
- Castling state before king/rook move/capture
- Half move clock before capture/double advance
*/
void MoveExecutor::undoMove(MoveInt move)
{
   Move mv;
   fromMoveInt(move, mv);

   toggleColour();
   updateBoardUndo(mv);
}

void MoveExecutor::updateBoard(const Move& mv)
{
   board_.move(mv.from_, mv.to_);
   switch (mv.type_)
   {
      case MoveType::ShortCastle:
         if (state_.activeColour_ == Colour::White)
         {
            board_.move(Sq::h1, Sq::f1);
         }
         else
         {
            board_.move(Sq::h8, Sq::f8);
         }
         break;
      case MoveType::LongCastle:
         if (state_.activeColour_ == Colour::White)
         {
            board_.move(Sq::a1, Sq::d1);
         }
         else
         {
            board_.move(Sq::a8, Sq::d8);
         }
         break;
      case MoveType::EnPassant:
         if (state_.activeColour_ == Colour::White)
         {
            board_.setEmpty(squareAt(mv.to_, Direction::D));
         }
         else
         {
            board_.setEmpty(squareAt(mv.to_, Direction::U));
         }
         break;
      case MoveType::KnightPromotion:
         board_.setPiece(mv.to_, Piece::Knight, state_.activeColour_);
         break;
      case MoveType::BishopPromotion:
         board_.setPiece(mv.to_, Piece::Bishop, state_.activeColour_);
         break;
      case MoveType::RookPromotion:
         board_.setPiece(mv.to_, Piece::Rook, state_.activeColour_);
         break;
      case MoveType::QueenPromotion:
         board_.setPiece(mv.to_, Piece::Queen, state_.activeColour_);
         break;
      default:
         break;
   }
}

void MoveExecutor::updateBoardUndo(const Move& mv)
{
   board_.move(mv.to_, mv.from_);
   switch (mv.type_)
   {
      case MoveType::ShortCastle:
         if (state_.activeColour_ == Colour::White)
         {
            board_.move(Sq::f1, Sq::h1);
         }
         else
         {
            board_.move(Sq::f8, Sq::h8);
         }
         break;
      case MoveType::LongCastle:
         if (state_.activeColour_ == Colour::White)
         {
            board_.move(Sq::d1, Sq::a1);
         }
         else
         {
            board_.move(Sq::d8, Sq::a8);
         }
         break;
      case MoveType::EnPassant:
         if (state_.activeColour_ == Colour::White)
         {
            board_.setPiece(squareAt(mv.to_, Direction::D), Piece::Pawn, Colour::Black);
         }
         else
         {
            board_.setPiece(squareAt(mv.to_, Direction::U), Piece::Pawn, Colour::White);
         }
         break;
      case MoveType::KnightPromotion:
         board_.setPiece(mv.from_, Piece::Pawn, state_.activeColour_);
         break;
      case MoveType::BishopPromotion:
         board_.setPiece(mv.from_, Piece::Pawn, state_.activeColour_);
         break;
      case MoveType::RookPromotion:
         board_.setPiece(mv.from_, Piece::Pawn, state_.activeColour_);
         break;
      case MoveType::QueenPromotion:
         board_.setPiece(mv.from_, Piece::Pawn, state_.activeColour_);
         break;
      default:
         break;
   }

   const Colour inactive = state_.activeColour_ == Colour::White ? Colour::Black : Colour::White;
   if (mv.capture_ != Piece::Empty && mv.type_ != MoveType::EnPassant)
   {
      board_.setPiece(mv.to_, mv.capture_, inactive);
   }
}

void MoveExecutor::updateEnPassant(const Move& mv)
{
   switch (mv.type_)
   {
      case MoveType::DoubleAdvance:
         if (state_.activeColour_ == Colour::White)
         {
            state_.enPassantSquare_ = squareAt(mv.to_, Direction::D);
         }
         else
         {
            state_.enPassantSquare_ = squareAt(mv.to_, Direction::U);
         }
         break;
      default:
         state_.enPassantSquare_ = Sq::Invalid;
         break;
   }
}

void MoveExecutor::updateCastling(const Move& mv)
{
   switch (mv.type_)
   {
      case MoveType::ShortCastle:
      case MoveType::LongCastle:
         if (state_.activeColour_ == Colour::White)
         {
            state_.canWhiteShortCastle_ = false;
            state_.canWhiteLongCastle_ = false;
         }
         else
         {
            state_.canBlackShortCastle_ = false;
            state_.canBlackLongCastle_ = false;
         }
         break;
      case MoveType::Normal:
         if (board_.pieceAt(mv.from_) == Piece::Rook)
         {
            switch (mv.from_)
            {
               case Sq::a1:
                  state_.canWhiteLongCastle_ = false;
                  break;
               case Sq::h1:
                  state_.canWhiteShortCastle_ = false;
                  break;
               case Sq::a8:
                  state_.canBlackLongCastle_ = false;
                  break;
               case Sq::h8:
                  state_.canBlackShortCastle_ = false;
                  break;
            }
         }
         else if (board_.pieceAt(mv.from_) == Piece::King)
         {
            if (state_.activeColour_ == Colour::White)
            {
               state_.canWhiteShortCastle_ = false;
               state_.canWhiteLongCastle_ = false;
            }
            else
            {
               state_.canBlackShortCastle_ = false;
               state_.canBlackLongCastle_ = false;
            }
         }
         // fall through
      case MoveType::KnightPromotion:
      case MoveType::BishopPromotion:
      case MoveType::RookPromotion:
      case MoveType::QueenPromotion:
         if (mv.capture_ == Piece::Rook)
         {
            switch (mv.to_)
            {
               case Sq::a1:
                  state_.canWhiteLongCastle_ = false;
                  break;
               case Sq::h1:
                  state_.canWhiteShortCastle_ = false;
                  break;
               case Sq::a8:
                  state_.canBlackLongCastle_ = false;
                  break;
               case Sq::h8:
                  state_.canBlackShortCastle_ = false;
                  break;
            }
         }
         break;
      default:
         break;
   }
}

void MoveExecutor::updateHalfMoveClock(const Move& mv)
{
   switch (mv.type_)
   {
      case MoveType::DoubleAdvance:
         state_.halfMoveClock_ = 0;
         break;
      default:
         if (mv.capture_ != Piece::Empty)
         {
            state_.halfMoveClock_ = 0;
         }
         else
         {
            state_.halfMoveClock_ += 1;
         }
         break;
   }
}

void MoveExecutor::updateFullMoveClock()
{
   if (state_.activeColour_ == Colour::Black)
   {
      state_.fullMoveClock_ += 1;
   }
}

void MoveExecutor::toggleColour()
{
   if (state_.activeColour_ == Colour::White)
   {
      state_.activeColour_ = Colour::Black;
   }
   else
   {
      state_.activeColour_ = Colour::White;
   }
}

}  // namespace Chess