#include "moveexecutor.h"
#include "mailbox.h"

#include <cassert>

namespace Chess
{

// ============================================================================
void MoveExecutor::move(MoveInt move)
{
   Move mv;
   fromMoveInt(move, mv);

   assertMove(mv);
   updateBoard(mv);
   updateEnPassant(mv);
   updateCastling(mv);
   toggleColour();
}

// ============================================================================
/* 
NOTE: We cannot undo the state since we do not know:
- En passant state before any move
- Castling state before king/rook move/capture
- Half move clock before capture/double advance
*/
void MoveExecutor::undo(MoveInt move)
{
   Move mv;
   fromMoveInt(move, mv);

   toggleColour();
   assertUndo(mv);
   updateBoardUndo(mv);
}

// ============================================================================
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

// ============================================================================
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
            board_.setPiece(squareAt(mv.to_, Direction::D), 
               Piece::Pawn, Colour::Black);
         }
         else
         {
            board_.setPiece(squareAt(mv.to_, Direction::U), 
               Piece::Pawn, Colour::White);
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

   if (mv.capture_ != Piece::Empty && mv.type_ != MoveType::EnPassant)
   {
      board_.setPiece(mv.to_, mv.capture_, enemy(state_.activeColour_));
   }
}

// ============================================================================
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

// ============================================================================
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

// ============================================================================
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

// ============================================================================
void MoveExecutor::updateFullMoveClock()
{
   if (state_.activeColour_ == Colour::Black)
   {
      state_.fullMoveClock_ += 1;
   }
}

// ============================================================================
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

// ============================================================================
void MoveExecutor::assertMove(const Move& mv) const
{
   #ifndef NDEBUG

   assert(state_.activeColour_ == Colour::White || 
      state_.activeColour_ == Colour::Black);
   assert(isValid(mv.from_));
   assert(isValid(mv.to_));
   assert(board_.isPieceAt(mv.from_));
   assert(board_.isPieceAt(mv.to_, mv.capture_));
   assert(board_.isColourAt(mv.from_, state_.activeColour_));
   if (mv.capture_ == Piece::Empty || mv.type_ == MoveType::EnPassant)
   {
      board_.colourAt(mv.to_) == Colour::Empty;
   }
   else
   {
      board_.colourAt(mv.to_) == enemy(state_.activeColour_);
   }

   switch (mv.type_)
   {
      case MoveType::ShortCastle:
         assert(board_.isPieceAt(mv.from_, Piece::King));
         assert(!board_.isPieceAt(mv.to_));
         if (state_.activeColour_ == Colour::White)
         {
            assert(state_.canWhiteShortCastle_);
            assert(board_.isPieceAt(Sq::h1, Piece::Rook));
            assert(!board_.isPieceAt(Sq::f1));
            assert(!board_.isPieceAt(Sq::g1));
         }
         else
         {
            assert(state_.canBlackShortCastle_);
            assert(board_.isPieceAt(Sq::h8, Piece::Rook));
            assert(!board_.isPieceAt(Sq::f8));
            assert(!board_.isPieceAt(Sq::g8));
         }
         break;
      case MoveType::LongCastle:
         assert(board_.isPieceAt(mv.from_, Piece::King));
         assert(!board_.isPieceAt(mv.to_));
         if (state_.activeColour_ == Colour::White)
         {
            assert(state_.canWhiteLongCastle_);
            assert(board_.isPieceAt(Sq::a1, Piece::Rook));
            assert(!board_.isPieceAt(Sq::d1));
            assert(!board_.isPieceAt(Sq::c1));
            assert(!board_.isPieceAt(Sq::b1));
         }
         else
         {
            assert(state_.canBlackLongCastle_);
            assert(board_.isPieceAt(Sq::a8, Piece::Rook));
            assert(!board_.isPieceAt(Sq::d8));
            assert(!board_.isPieceAt(Sq::c8));
            assert(!board_.isPieceAt(Sq::b8));
         }
         break;
      case MoveType::EnPassant:
         assert(board_.isPieceAt(mv.from_, Piece::Pawn));
         assert(mv.capture_ == Piece::Pawn);
         assert(state_.enPassantSquare_ == mv.to_);
         const Square pawnSquare = squareAt(mv.to_, 
            state_.activeColour_  == Colour::White ? 
            Direction::D : Direction::U);
         assert(pawnSquare != Sq::Invalid);
         assert(board_.isPieceAt(pawnSquare, Piece::Pawn));
         break;
      case MoveType::KnightPromotion:
      case MoveType::BishopPromotion:
      case MoveType::RookPromotion:
      case MoveType::QueenPromotion:
         assert(board_.isPieceAt(mv.from_, Piece::Pawn));
         assert(state_.activeColour_ == Colour::White ? 
            rank(mv.to_) == r8 : rank(mv.to_) == r1);
         break;
      case MoveType::DoubleAdvance:
         assert(board_.isPieceAt(mv.from_, Piece::Pawn));
         if (state_.activeColour_ == Colour::White)
         {
            assert(rank(mv.from_) == r2);
            assert(rank(mv.to_) == r4);
            assert(!board_.isPieceAt(squareAt(mv.to_, Direction::D)));
         }
         else
         {
            assert(rank(mv.from_) == r7);
            assert(rank(mv.to_) == r5);
            assert(!board_.isPieceAt(squareAt(mv.to_, Direction::U)));
         }
         break;
      case MoveType::Invalid:
         assert(false);
      default:
         break;
   }

   #endif
}

// ============================================================================
void MoveExecutor::assertUndo(const Move& mv) const
{
   #ifndef NDEBUG

   assert(state_.activeColour_ == Colour::White || 
      state_.activeColour_ == Colour::Black);
   assert(isValid(mv.from_));
   assert(isValid(mv.to_));
   assert(board_.isPieceAt(mv.to_));
   assert(!board_.isPieceAt(mv.from_));
   assert(board_.isColourAt(mv.to_, Colour::Empty));
   assert(board_.isColourAt(mv.from_, state_.activeColour_));

   switch (mv.type_)
   {
      case MoveType::ShortCastle:
         assert(board_.isPieceAt(mv.to_, Piece::King));
         assert(!board_.isPieceAt(mv.from_));
         if (state_.activeColour_ == Colour::White)
         {
            assert(!state_.canWhiteShortCastle_);
            assert(board_.isPieceAt(Sq::f1, Piece::Rook));
            assert(!board_.isPieceAt(Sq::h1));
            assert(!board_.isPieceAt(Sq::e1));
         }
         else
         {
            assert(!state_.canWhiteLongCastle_);
            assert(board_.isPieceAt(Sq::f8, Piece::Rook));
            assert(!board_.isPieceAt(Sq::h8));
            assert(!board_.isPieceAt(Sq::e8));
         }
         break;
      case MoveType::LongCastle:
         assert(board_.isPieceAt(mv.to_, Piece::King));
         assert(!board_.isPieceAt(mv.from_));
         if (state_.activeColour_ == Colour::White)
         {
            assert(!state_.canBlackLongCastle_);
            assert(board_.isPieceAt(Sq::d1, Piece::Rook));
            assert(!board_.isPieceAt(Sq::a1));
            assert(!board_.isPieceAt(Sq::e1));
            assert(!board_.isPieceAt(Sq::b1));
         }
         else
         {
            assert(!state_.canBlackLongCastle_);
            assert(board_.isPieceAt(Sq::d8, Piece::Rook));
            assert(!board_.isPieceAt(Sq::a8));
            assert(!board_.isPieceAt(Sq::e8));
            assert(!board_.isPieceAt(Sq::b8));
         }
         break;
      case MoveType::EnPassant:
         assert(board_.isPieceAt(mv.to_, Piece::Pawn));
         assert(mv.capture_ == Piece::Pawn);
         assert(state_.enPassantSquare_ == Sq::Invalid);
         const Square pawnSquare = squareAt(mv.to_, 
            state_.activeColour_  == Colour::White ? 
            Direction::D : Direction::U);
         assert(pawnSquare != Sq::Invalid);
         assert(!board_.isPieceAt(pawnSquare));
         break;
      case MoveType::KnightPromotion:
         assert(board_.isPieceAt(mv.to_, Piece::Knight));
         assert(state_.activeColour_ == Colour::White ? 
            rank(mv.to_) == r8 : rank(mv.to_) == r1);
         break;
      case MoveType::BishopPromotion:
         assert(board_.isPieceAt(mv.to_, Piece::Bishop));
         assert(state_.activeColour_ == Colour::White ? 
            rank(mv.to_) == r8 : rank(mv.to_) == r1);
         break;
      case MoveType::RookPromotion:
         assert(board_.isPieceAt(mv.to_, Piece::Rook));
         assert(state_.activeColour_ == Colour::White ? 
            rank(mv.to_) == r8 : rank(mv.to_) == r1);
         break;
      case MoveType::QueenPromotion:
         assert(board_.isPieceAt(mv.to_, Piece::Queen));
         assert(state_.activeColour_ == Colour::White ? 
            rank(mv.to_) == r8 : rank(mv.to_) == r1);
         break;
      case MoveType::DoubleAdvance:
         if (state_.activeColour_ == Colour::White)
         {
            assert(rank(mv.from_) == r2);
            assert(rank(mv.to_) == r4);
            assert(!board_.isPieceAt(squareAt(mv.to_, Direction::D)));
         }
         else
         {
            assert(rank(mv.from_) == r7);
            assert(rank(mv.to_) == r5);
            assert(!board_.isPieceAt(squareAt(mv.to_, Direction::U)));
         }
         break;
      case MoveType::Invalid:
         assert(false);
      default:
         break;
   }
   #endif
}

}  // namespace Chess
