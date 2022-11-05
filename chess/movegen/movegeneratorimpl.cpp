#include "movegeneratorimpl.h"

namespace Chess::Internal
{

//=============================================================================
template<typename MoveFormat, typename OutputIt> 
int MoveGenerator<MoveFormat, OutputIt>::exec()
{
   for (int i = 0; i < NUM_SQUARES; ++i)
   {
      if (board_.colourAt(i) != state_.activeColour_)
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
   return out_.numOutputted();
}

// //=============================================================================
template<typename MoveFormat, typename OutputIt> 
void MoveGenerator<MoveFormat, OutputIt>::genPawnMoves(Square from)
{
   if (state_.activeColour_ == Colour::White)
   {
      genWPawnMoves(from);
   }
   else
   {
      genBPawnMoves(from);
   }
}

//=============================================================================
template<typename MoveFormat, typename OutputIt> 
void MoveGenerator<MoveFormat, OutputIt>::genWPawnMoves(Square from)
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
            pushMove(Move{from, upup, MoveType::Normal});
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
      else if (to != Sq::Invalid && board_.colourAt(to) == enemy(state_.activeColour_))
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
template<typename MoveFormat, typename OutputIt> 
void MoveGenerator<MoveFormat, OutputIt>::genBPawnMoves(Square from)
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
            pushMove(Move{from, downdown, MoveType::Normal});
         }
      }
   }

   // Check normal captures and en passant
   static const std::array<Direction, 2> captureDirections = {DL, DR};
   for (const Direction dir : captureDirections)
   {
      const Square to = squareAt(from, dir);
      if (to == state_.enPassantSquare_)
      {
         pushMove(Move{from, to, MoveType::EnPassant, Piece::Pawn});
      }
      else if (to != Sq::Invalid && board_.colourAt(to) == enemy(state_.activeColour_))
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
template<typename MoveFormat, typename OutputIt> 
void MoveGenerator<MoveFormat, OutputIt>::genKnightMoves(Square from)
{
   static const std::vector<Direction> directions = {HUL, HUR, HRU, HRD, HDR, HDL, HLD, HLU};
   genSingleMoves(from, directions);
}

//=============================================================================
template<typename MoveFormat, typename OutputIt> 
void MoveGenerator<MoveFormat, OutputIt>::genKingMoves(Square from)
{
   // Normal moves
   static const std::vector<Direction> directions = {U, UR, R, DR, D, DL, L, UL};
   genSingleMoves(from, directions);

   // Castles
   if (state_.activeColour_ == Colour::White)
   {
      genWCastles();
   }
   else
   {
      genBCastles();
   }
}

//=============================================================================
template<typename MoveFormat, typename OutputIt> 
void MoveGenerator<MoveFormat, OutputIt>::genSingleMoves(
   Square from, const std::vector<Direction>& directions)
{
   for (const Direction dir : directions)
   {
      const Square to = squareAt(from, dir);
      if (to != Sq::Invalid && board_.colourAt(to) != state_.activeColour_)
      {
         pushMove(Move{from, to, MoveType::Normal, board_.pieceAt(to)});
      }
   }
}

//=============================================================================
template<typename MoveFormat, typename OutputIt> 
void MoveGenerator<MoveFormat, OutputIt>::genWCastles()
{
   // TODO: Check if castles are blocked
   if (state_.canWhiteShortCastle_ && 
      !board_.isPieceAt(Sq::f1) &&
      !board_.isPieceAt(Sq::g1))
   {
      pushMove(Move{Sq::e1, Sq::g1 ,MoveType::ShortCastle});
   }
   else if(state_.canWhiteLongCastle_&& 
      !board_.isPieceAt(Sq::d1) &&
      !board_.isPieceAt(Sq::c1)&&
      !board_.isPieceAt(Sq::b1))
   {
      pushMove(Move{Sq::e1, Sq::c1 ,MoveType::LongCastle});
   }
}

//=============================================================================
template<typename MoveFormat, typename OutputIt> 
void MoveGenerator<MoveFormat, OutputIt>::genBCastles()
{
   // TODO: Check if castles are blocked
   if (state_.canBlackShortCastle_ && 
      !board_.isPieceAt(Sq::f8) &&
      !board_.isPieceAt(Sq::g8))
   {
      pushMove(Move{Sq::e8, Sq::g8 ,MoveType::ShortCastle});
   }
   else if(state_.canBlackLongCastle_&& 
      !board_.isPieceAt(Sq::d8) &&
      !board_.isPieceAt(Sq::c8)&&
      !board_.isPieceAt(Sq::b8))
   {
      pushMove(Move{Sq::e8, Sq::c8 ,MoveType::LongCastle});
   }
}

//=============================================================================
template<typename MoveFormat, typename OutputIt> 
void MoveGenerator<MoveFormat, OutputIt>::genBishopMoves(Square from)
{
   static const std::vector<Direction> directions = {UR, DR, DL, UL};
   genSlidingMoves(from, directions);
}

//=============================================================================
template<typename MoveFormat, typename OutputIt> 
void MoveGenerator<MoveFormat, OutputIt>::genRookMoves(Square from)
{
   static const std::vector<Direction> directions = {U, R, D, L};
   genSlidingMoves(from, directions);
}

//=============================================================================
template<typename MoveFormat, typename OutputIt> 
void MoveGenerator<MoveFormat, OutputIt>::genQueenMoves(Square from)
{
   static const std::vector<Direction> directions = {U, UR, R, DR, D, DL, L, UL};
   genSlidingMoves(from, directions);
}

//=============================================================================
template<typename MoveFormat, typename OutputIt> 
void MoveGenerator<MoveFormat, OutputIt>::genSlidingMoves(
   Square from, const std::vector<Direction>& directions)
{
   for (const Direction dir : directions)
   {
      for (Square to = squareAt(from, dir); to != Sq::Invalid; to = squareAt(to, dir))
      {
         const Colour toColour = board_.colourAt(to);
         if (toColour != state_.activeColour_)
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
template<typename MoveFormat, typename OutputIt> 
void MoveGenerator<MoveFormat, OutputIt>::pushMove(const Move& mv)
{
   if (!checkLegal_ || isLegal(mv))
   {
      out_ << mv;
   }
}

}  // namespace Chess::Internal
