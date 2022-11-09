#include "movegeneratorimpl.h"

#include <cassert>

namespace Chess::Internal
{

//=============================================================================
template<typename OutputIt> 
int MoveGenerator<OutputIt>::exec()
{
   numOutputted_ = 0;

   for (Square i = Sq::a1; i <= Sq::h8; ++i)
   {
      if (board_.colourAt(i) != state_.active_)
      {
         continue;
      }

      switch(board_.pieceAt(i))
      {
         case Piece::Pawn:
            genPawnMoves(i);
            break;
         case Piece::Knight:
            genKnightMoves(i);
            break;
         case Piece::Bishop:
            genBishopMoves(i);
            break;
         case Piece::Rook:
            genRookMoves(i);
            break;
         case Piece::Queen:
            genQueenMoves(i);
            break;
         case Piece::King:
            genKingMoves(i);
            break;
         default:
            break;
      }
   }
   return numOutputted_;
}

// //=============================================================================
template<typename OutputIt> 
void MoveGenerator<OutputIt>::genPawnMoves(Square from)
{
   if (state_.active_ == Colour::White)
   {
      genWPawnMoves(from);
   }
   else
   {
      genBPawnMoves(from);
   }
}

//=============================================================================
template<typename OutputIt> 
void MoveGenerator<OutputIt>::genWPawnMoves(Square from)
{
   // Check normal move and double advance
   const Square up = squareAt(from, Direction::U);
   if (!board_.isPieceAt(up)) // up is valid
   {
      if (rank(from) == Rank::r7)
      {
         pushMove(Move{from, up, MoveType::KnightPromotion});
         pushMove(Move{from, up, MoveType::BishopPromotion});
         pushMove(Move{from, up, MoveType::RookPromotion});
         pushMove(Move{from, up, MoveType::QueenPromotion});
      }
      else
      {
         pushMove(Move{from, up, MoveType::Normal});

         const Square upup = squareAt(up, Direction::U);
         if (rank(from) == Rank::r2 && !board_.isPieceAt(upup)) // upup is valid
         {
            pushMove(Move{from, upup, MoveType::DoubleAdvance});
         }
      }
   }

   // Check normal captures and en passant
   static const std::array<Direction, 2> captureDirections = {UL, UR};
   for (const Direction dir : captureDirections)
   {
      const Square to = squareAt(from, dir);
      if (to != Sq::Invalid && to == state_.enPassantSquare_)
      {
         pushMove(Move{from, to, MoveType::EnPassant, Piece::Pawn});
      }
      else if (to != Sq::Invalid && board_.colourAt(to) == state_.inactive_)
      {
         const Piece enemyPiece = board_.pieceAt(to);
         if (rank(from) == Rank::r7)
         {
            pushMove(Move{from, to, MoveType::KnightPromotion, enemyPiece});
            pushMove(Move{from, to, MoveType::BishopPromotion, enemyPiece});
            pushMove(Move{from, to, MoveType::RookPromotion, enemyPiece});
            pushMove(Move{from, to, MoveType::QueenPromotion, enemyPiece});
         }
         else
         {
            pushMove(Move{from, to, MoveType::Normal, enemyPiece});
         }
      }
   }
}

//=============================================================================
template<typename OutputIt> 
void MoveGenerator<OutputIt>::genBPawnMoves(Square from)
{
   // Check normal move and double advance
   const Square down = squareAt(from, Direction::D);
   if (!board_.isPieceAt(down)) // down is valid
   {
      if (rank(from) == Rank::r2)
      {
         pushMove(Move{from, down, MoveType::KnightPromotion});
         pushMove(Move{from, down, MoveType::BishopPromotion});
         pushMove(Move{from, down, MoveType::RookPromotion});
         pushMove(Move{from, down, MoveType::QueenPromotion});
      }
      else
      {
         pushMove(Move{from, down, MoveType::Normal});

         const Square downdown = squareAt(down, Direction::D);
         if (rank(from) == Rank::r7 && !board_.isPieceAt(downdown)) // downdown is valid
         {
            pushMove(Move{from, downdown, MoveType::DoubleAdvance});
         }
      }
   }

   // Check normal captures and en passant
   static const std::array<Direction, 2> captureDirections = {DL, DR};
   for (const Direction dir : captureDirections)
   {
      const Square to = squareAt(from, dir);
      if (to != Sq::Invalid && to == state_.enPassantSquare_)
      {
         pushMove(Move{from, to, MoveType::EnPassant, Piece::Pawn});
      }
      else if (to != Sq::Invalid && board_.colourAt(to) == state_.inactive_)
      {
         const Piece enemyPiece = board_.pieceAt(to);
         if (rank(from) == Rank::r2)
         {
            pushMove(Move{from, to, MoveType::KnightPromotion, enemyPiece});
            pushMove(Move{from, to, MoveType::BishopPromotion, enemyPiece});
            pushMove(Move{from, to, MoveType::RookPromotion, enemyPiece});
            pushMove(Move{from, to, MoveType::QueenPromotion, enemyPiece});
         }
         else
         {
            pushMove(Move{from, to, MoveType::Normal, enemyPiece});
         }
      }
   }
}

//=============================================================================
template<typename OutputIt> 
void MoveGenerator<OutputIt>::genKnightMoves(Square from)
{
   static const std::vector<Direction> directions = {HUR, HRU, HRD, HDR, HDL, HLD, HLU, HUL};
   genSingleMoves(from, directions);
}

//=============================================================================
template<typename OutputIt> 
void MoveGenerator<OutputIt>::genKingMoves(Square from)
{
   // Normal moves
   static const std::vector<Direction> directions = {U, UR, R, DR, D, DL, L, UL};
   genSingleMoves(from, directions);

   // Castles
   if (!isInCheck_)
   {
      state_.active_ == Colour::White ? genWCastles() : genBCastles();
   }
}

//=============================================================================
template<typename OutputIt> 
void MoveGenerator<OutputIt>::genSingleMoves(
   Square from, const std::vector<Direction>& directions)
{
   for (const Direction dir : directions)
   {
      const Square to = squareAt(from, dir);
      if (to != Sq::Invalid && board_.colourAt(to) != state_.active_)
      {
         pushMove(Move{from, to, MoveType::Normal, board_.pieceAt(to)});
      }
   }
}

//=============================================================================
template<typename OutputIt> 
void MoveGenerator<OutputIt>::genWCastles()
{
   if (state_.canWhiteShortCastle_ && 
      !board_.isPieceAt(Sq::f1) &&
      !board_.isPieceAt(Sq::g1) &&
      !isAttacked(Sq::f1) &&
      !isAttacked(Sq::g1))
   {
      pushMove(Move{Sq::e1, Sq::g1 ,MoveType::ShortCastle});
   }
   else if(state_.canWhiteLongCastle_&& 
      !board_.isPieceAt(Sq::d1) &&
      !board_.isPieceAt(Sq::c1)&&
      !board_.isPieceAt(Sq::b1) &&
      !isAttacked(Sq::d1) &&
      !isAttacked(Sq::c1))
   {
      // NOTE: b1 need not be safe, just empty
      pushMove(Move{Sq::e1, Sq::c1 ,MoveType::LongCastle});
   }
}

//=============================================================================
template<typename OutputIt> 
void MoveGenerator<OutputIt>::genBCastles()
{
   if (state_.canBlackShortCastle_ && 
      !board_.isPieceAt(Sq::f8) &&
      !board_.isPieceAt(Sq::g8) &&
      !isAttacked(Sq::f8) &&
      !isAttacked(Sq::g8))
   {
      pushMove(Move{Sq::e8, Sq::g8 ,MoveType::ShortCastle});
   }
   else if(state_.canBlackLongCastle_&& 
      !board_.isPieceAt(Sq::d8) &&
      !board_.isPieceAt(Sq::c8)&&
      !board_.isPieceAt(Sq::b8) &&
      !isAttacked(Sq::d8) &&
      !isAttacked(Sq::c8))
   {
      // NOTE: b8 need not be safe, just empty
      pushMove(Move{Sq::e8, Sq::c8 ,MoveType::LongCastle});
   }
}

//=============================================================================
template<typename OutputIt> 
void MoveGenerator<OutputIt>::genBishopMoves(Square from)
{
   static const std::vector<Direction> directions = {UR, DR, DL, UL};
   genSlidingMoves(from, directions);
}

//=============================================================================
template<typename OutputIt> 
void MoveGenerator<OutputIt>::genRookMoves(Square from)
{
   static const std::vector<Direction> directions = {U, R, D, L};
   genSlidingMoves(from, directions);
}

//=============================================================================
template<typename OutputIt> 
void MoveGenerator<OutputIt>::genQueenMoves(Square from)
{
   static const std::vector<Direction> directions = {U, UR, R, DR, D, DL, L, UL};
   genSlidingMoves(from, directions);
}

//=============================================================================
template<typename OutputIt> 
void MoveGenerator<OutputIt>::genSlidingMoves(
   Square from, const std::vector<Direction>& directions)
{
   for (const Direction dir : directions)
   {
      for (Square to = squareAt(from, dir); to != Sq::Invalid; to = squareAt(to, dir))
      {
         const Colour toColour = board_.colourAt(to);
         if (toColour != state_.active_)
         {
            pushMove(Move{from, to, MoveType::Normal, board_.pieceAt(to)});
            if (toColour != Colour::Empty)
            {
               break; // Enemy piece reached -> exit
            }
            // Empty square -> continue
         }
         else
         {
            break; // Friendly piece reached -> exit
         }
      }
   }
}

//=============================================================================
template<typename OutputIt> 
void MoveGenerator<OutputIt>::pushMove(const Move& mv)
{
   *out_ = mv;
   out_++;
   numOutputted_++;
}

}  // namespace Chess::Internal
