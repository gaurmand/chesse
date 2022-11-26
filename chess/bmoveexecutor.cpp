#include "bmoveexecutor.h"
#include "mailbox.h"

#include <cassert>

namespace Chess
{

//=============================================================================
void BMoveExecutor::move(const BMove& mv)
{
   //assertMove(mv);
   updateBoard(mv);
   updateEnPassant(mv);
   updateCastling(mv);
   updateHalfMoveClock(mv);
   updateFullMoveClock(mv);
   toggleColour(state_);
}

//=============================================================================
void BMoveExecutor::unmove(const BMove& move)
{
   toggleColour(state_);
   // assertUnmove(move);
   updateBoardUnmove(move);
}

//=============================================================================
void BMoveExecutor::updateBoard(const BMove& mv)
{  
   if (mv.captured_ == PieceType::EmptyPiece || mv.type_ == MoveType::EnPassant)
   {
      board_.move(mv.from_, mv.to_, mv.moved_, mv.movedColour_);
   }
   else
   {
      board_.capture(mv.from_, mv.to_, mv.moved_, mv.captured_, mv.movedColour_, mv.capColour_);
   }

   switch (mv.type_)
   {
      case MoveType::ShortCastle:
         if (mv.movedColour_ == Color::White)
         {
            board_.move(Sq::h1, Sq::f1, PieceType::Rook, Color::White);
         }
         else
         {
            board_.move(Sq::h8, Sq::f8, PieceType::Rook, Color::Black);
         }
         break;
      case MoveType::LongCastle:
         if (mv.movedColour_ == Color::White)
         {
            board_.move(Sq::a1, Sq::d1, PieceType::Rook, Color::White);
         }
         else
         {
            board_.move(Sq::a8, Sq::d8, PieceType::Rook, Color::Black);
         }
         break;
      case MoveType::EnPassant:
         if (mv.movedColour_ == Color::White)
         {
            board_.clear(squareAt(mv.to_, Direction::D), PieceType::Pawn, Color::Black);
         }
         else
         {
            board_.clear(squareAt(mv.to_, Direction::U), PieceType::Pawn, Color::White);
         }
         break;
      case MoveType::KnightPromotion:
         board_.promote(mv.to_, PieceType::Pawn, PieceType::Knight, mv.movedColour_);
         break;
      case MoveType::BishopPromotion:
         board_.promote(mv.to_, PieceType::Pawn, PieceType::Bishop, mv.movedColour_);
         break;
      case MoveType::RookPromotion:
         board_.promote(mv.to_, PieceType::Pawn, PieceType::Rook, mv.movedColour_);
         break;
      case MoveType::QueenPromotion:
         board_.promote(mv.to_, PieceType::Pawn, PieceType::Queen, mv.movedColour_);
         break;
      default:
         break;
   }
}

//=============================================================================
void BMoveExecutor::updateBoardUnmove(const BMove& mv)
{  
   switch (mv.type_)
   {
      case MoveType::KnightPromotion:
         board_.move(mv.to_, mv.from_, PieceType::Knight, mv.movedColour_);
         break;
      case MoveType::BishopPromotion:
         board_.move(mv.to_, mv.from_, PieceType::Bishop, mv.movedColour_);
         break;
      case MoveType::RookPromotion:
         board_.move(mv.to_, mv.from_, PieceType::Rook, mv.movedColour_);
         break;
      case MoveType::QueenPromotion:
         board_.move(mv.to_, mv.from_, PieceType::Queen, mv.movedColour_);
         break;
      default:
         board_.move(mv.to_, mv.from_, mv.moved_, mv.movedColour_);
         break;
   }

   switch (mv.type_)
   {
      case MoveType::ShortCastle:
         if (mv.movedColour_ == Color::White)
         {
            board_.move(Sq::f1, Sq::h1, PieceType::Rook, Color::White);
         }
         else
         {
            board_.move(Sq::f8, Sq::h8, PieceType::Rook, Color::Black);
         }
         break;
      case MoveType::LongCastle:
         if (mv.movedColour_ == Color::White)
         {
            board_.move(Sq::d1, Sq::a1, PieceType::Rook, Color::White);
         }
         else
         {
            board_.move(Sq::d8, Sq::a8, PieceType::Rook, Color::Black);
         }
         break;
      case MoveType::EnPassant:
         if (mv.movedColour_ == Color::White)
         {
            board_.set(squareAt(mv.to_, Direction::D), PieceType::Pawn, Color::Black);
         }
         else
         {
            board_.set(squareAt(mv.to_, Direction::U), PieceType::Pawn, Color::White);
         }
         break;
      case MoveType::KnightPromotion:
         board_.promote(mv.from_, PieceType::Knight, PieceType::Pawn, mv.movedColour_);
         break;
      case MoveType::BishopPromotion:
         board_.promote(mv.from_, PieceType::Bishop, PieceType::Pawn, mv.movedColour_);
         break;
      case MoveType::RookPromotion:
         board_.promote(mv.from_, PieceType::Rook, PieceType::Pawn, mv.movedColour_);
         break;
      case MoveType::QueenPromotion:
         board_.promote(mv.from_, PieceType::Queen, PieceType::Pawn, mv.movedColour_);
         break;
      default:
         break;
   }

   if (mv.captured_ != PieceType::EmptyPiece && mv.type_ != MoveType::EnPassant)
   {
      board_.set(mv.to_, mv.captured_, mv.capColour_);
   }
}

//=============================================================================
void BMoveExecutor::updateEnPassant(const BMove& mv)
{
   // NOTE: We record en passant square regardless of whether there is a 
   // pawn in position to capture it.
   switch (mv.type_)
   {
      case MoveType::DoubleAdvance:
      
         if (mv.movedColour_ == Color::White)
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

//=============================================================================
void BMoveExecutor::updateCastling(const BMove& mv)
{
   switch (mv.type_)
   {
      case MoveType::ShortCastle:
      case MoveType::LongCastle:
         if (mv.movedColour_ == Color::White)
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
         if (mv.moved_ == PieceType::Rook)
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
         else if (mv.moved_ == PieceType::King)
         {
            switch (mv.from_)
            {
               case Sq::e1:
                  state_.canWhiteShortCastle_ = false;
                  state_.canWhiteLongCastle_ = false;
                  break;
               case Sq::e8:
                  state_.canBlackShortCastle_ = false;
                  state_.canBlackLongCastle_ = false;                 
                  break;
            }
         }
         // fall through
      case MoveType::KnightPromotion:
      case MoveType::BishopPromotion:
      case MoveType::RookPromotion:
      case MoveType::QueenPromotion:
         if (mv.captured_ == PieceType::Rook)
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

//=============================================================================
void BMoveExecutor::updateHalfMoveClock(const BMove& mv)
{
   if (mv.moved_ == PieceType::Pawn || mv.captured_ != PieceType::EmptyPiece)
   {
      state_.halfMoveClock_ = 0;
   }
   else
   {
      state_.halfMoveClock_ += 1;
   }
}

//=============================================================================
void BMoveExecutor::updateFullMoveClock(const BMove& mv)
{
   if (mv.movedColour_ == Color::Black)
   {
      state_.fullMoveClock_ += 1;
   }
}

}  // namespace Chess
