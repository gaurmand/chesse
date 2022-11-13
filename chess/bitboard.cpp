#include "bitboard.h"   

#include <iostream>

namespace Chess
{

//=============================================================================
Bitboard attackedSquares(const AttackTable& table)
{
   Bitboard attacked;
   for(const auto& board: table)
   {
      attacked |= board;
   }
   return attacked;
}

//=============================================================================
bool isAttackedBy(Square sq, const AttackTable& table)
{
   return attackedSquares(table).test(sq);
}

//=============================================================================
void AttackTableUpdater::initialize(Colour friendly, AttackTable& table)
{
   for (Square i = Sq::a1; i <= Sq::h8; ++i)
   {
      if (board_.isColourAt(i, friendly))
      {
         updateBitboard(i, table[i]);
      }
   }
}

//=============================================================================
void AttackTableUpdater::updateFromMove(const Move& move, AttackTable& friendly, AttackTable& enemy)
{
   friendly[move.from_].reset();
   friendly[move.to_].reset();

   switch(move.type_)
   {
      case MoveType::ShortCastle:
         if (state_.active_ != Colour::White)
         {
            friendly[Sq::f1].reset();
            friendly[Sq::h1].reset();
            updateBitboard(Sq::f1, friendly[Sq::f1]);
            updateAffectedSquares(Sq::f1, Sq::h1, Colour::White, friendly, enemy);
            updateAffectedSquares(Sq::h1, Sq::f1, Colour::White, friendly, enemy);
         }
         else
         {
            friendly[Sq::f8].reset();
            friendly[Sq::h8].reset();
            updateBitboard(Sq::f8, friendly[Sq::f8]);
            updateAffectedSquares(Sq::f8, Sq::h8, Colour::Black, friendly, enemy);
            updateAffectedSquares(Sq::h8, Sq::f8, Colour::Black, friendly, enemy);
         }
         break;
      case MoveType::LongCastle:
         if (state_.active_ != Colour::White)
         {
            friendly[Sq::d1].reset();
            friendly[Sq::a1].reset();
            updateBitboard(Sq::d1, friendly[Sq::d1]);
            updateAffectedSquares(Sq::d1, Sq::a1, Colour::White, friendly, enemy);
            updateAffectedSquares(Sq::a1, Sq::d1, Colour::White, friendly, enemy);
         }
         else
         {
            friendly[Sq::d8].reset();
            friendly[Sq::a8].reset();
            updateBitboard(Sq::d8, friendly[Sq::d8]);
            updateAffectedSquares(Sq::d8, Sq::a8, Colour::Black, friendly, enemy);
            updateAffectedSquares(Sq::a8, Sq::d8, Colour::Black, friendly, enemy);
         }
         break;
      case MoveType::EnPassant:
         if (state_.active_ != Colour::White)
         {
            Square captured = squareAt(move.to_, Direction::D);
            enemy[captured].reset();
            updateAffectedSquares(captured, Sq::Invalid, Colour::White, friendly, enemy);
         }
         else
         {
            Square captured = squareAt(move.to_, Direction::U);
            enemy[captured].reset();
            updateAffectedSquares(captured, Sq::Invalid, Colour::Black, friendly, enemy);
         }
         break;
      default:
         break;
   }
   updateBitboard(move.to_, friendly[move.to_]);

   if (move.capture_ != Piece::Empty && move.type_ != MoveType::EnPassant)
   {
      enemy[move.to_].reset();
   }

   const Colour friendlyC = board_.colourAt(move.to_);
   updateAffectedSquares(move.from_, move.to_, friendlyC, friendly, enemy);
   updateAffectedSquares(move.to_, move.from_, friendlyC, friendly, enemy);
}

//=============================================================================
void AttackTableUpdater::updateFromUnmove(const Move& move, AttackTable& friendly, AttackTable& enemy)
{
   friendly[move.from_].reset();
   friendly[move.to_].reset();

   switch(move.type_)
   {
      case MoveType::ShortCastle:
         if (state_.active_ == Colour::White)
         {
            friendly[Sq::f1].reset();
            friendly[Sq::h1].reset();
            updateBitboard(Sq::h1, friendly[Sq::h1]);
            updateAffectedSquares(Sq::f1, Sq::h1, Colour::White, friendly, enemy);
            updateAffectedSquares(Sq::h1, Sq::f1, Colour::White, friendly, enemy);
         }
         else
         {
            friendly[Sq::f8].reset();
            friendly[Sq::h8].reset();
            updateBitboard(Sq::h8, friendly[Sq::h8]);
            updateAffectedSquares(Sq::f8, Sq::h8, Colour::Black, friendly, enemy);
            updateAffectedSquares(Sq::h8, Sq::f8, Colour::Black, friendly, enemy);
         }
         break;
      case MoveType::LongCastle:
         if (state_.active_ == Colour::White)
         {
            friendly[Sq::d1].reset();
            friendly[Sq::a1].reset();
            updateBitboard(Sq::a1, friendly[Sq::a1]);
            updateAffectedSquares(Sq::d1, Sq::a1, Colour::White, friendly, enemy);
            updateAffectedSquares(Sq::a1, Sq::d1, Colour::White, friendly, enemy);
         }
         else
         {
            friendly[Sq::d8].reset();
            friendly[Sq::a8].reset();
            updateBitboard(Sq::a8, friendly[Sq::a8]);
            updateAffectedSquares(Sq::d8, Sq::a8, Colour::Black, friendly, enemy);
            updateAffectedSquares(Sq::a8, Sq::d8, Colour::Black, friendly, enemy);
         }
         break;
      case MoveType::EnPassant:
         if (state_.active_ == Colour::White)
         {
            Square captured = squareAt(move.to_, Direction::D);
            updateBitboard(captured, enemy[captured]);
            updateAffectedSquares(captured, Sq::Invalid, Colour::White, friendly, enemy);
         }
         else
         {
            Square captured = squareAt(move.to_, Direction::U);
            updateBitboard(captured, enemy[captured]);
            updateAffectedSquares(captured, Sq::Invalid, Colour::Black, friendly, enemy);
         }
         break;
      default:
         break;
   }
   updateBitboard(move.from_, friendly[move.from_]);

   if (move.capture_ != Piece::Empty && move.type_ != MoveType::EnPassant)
   {
      updateBitboard(move.to_, enemy[move.to_]);
   }

   const Colour friendlyC = board_.colourAt(move.from_);
   updateAffectedSquares(move.from_, move.to_, friendlyC, friendly, enemy);
   updateAffectedSquares(move.to_, move.from_, friendlyC, friendly, enemy);
}

//=============================================================================
void AttackTableUpdater::updateAffectedSquares(Square sq, Square stop, Colour friendlyC, AttackTable& friendly, AttackTable& enemy)
{
   for (const Direction dir : Directions::orthogonal)
   {
      for (Square to = squareAt(sq, dir); to != Sq::Invalid && to != stop; to = squareAt(to, dir))
      {
         const Piece toPiece = board_.pieceAt(to);
         if (toPiece != Piece::Empty)
         {  
            if (toPiece == Piece::Rook || toPiece == Piece::Queen)
            {
               if (board_.isColourAt(to, friendlyC))
               {
                  setBitsSlidingPieces(to, friendly[to], opposite(dir));
               }
               else
               {
                  setBitsSlidingPieces(to, enemy[to], opposite(dir));
               }
            }
            break;
         }
      }
   }

   for (const Direction dir : Directions::diagonal)
   {
      for (Square to = squareAt(sq, dir); to != Sq::Invalid; to = squareAt(to, dir))
      {
         const Piece toPiece = board_.pieceAt(to);
         if (toPiece != Piece::Empty)
         {  
            if (toPiece == Piece::Bishop || toPiece == Piece::Queen)
            {
               if (board_.isColourAt(to, friendlyC))
               {
                  setBitsSlidingPieces(to, friendly[to], opposite(dir));
               }
               else
               {
                  setBitsSlidingPieces(to, enemy[to], opposite(dir));
               }
            }
            break;
         }
      }
   }
}

//=============================================================================
void AttackTableUpdater::updateBitboard(Square sq, Bitboard& bboard)
{
   switch(board_.pieceAt(sq))
   {
      case Piece::Pawn:
         if (board_.isColourAt(sq, Colour::White))
         {
            setIfValid(bboard, squareAt(sq, Direction::UL));
            setIfValid(bboard, squareAt(sq, Direction::UR));
         }
         else
         {
            setIfValid(bboard, squareAt(sq, Direction::DL));
            setIfValid(bboard, squareAt(sq, Direction::DR));
         }
         break;
      case Piece::Knight:
         setIfValid(bboard, squareAt(sq, Direction::HUR));
         setIfValid(bboard, squareAt(sq, Direction::HRU));
         setIfValid(bboard, squareAt(sq, Direction::HRD));
         setIfValid(bboard, squareAt(sq, Direction::HDR));
         setIfValid(bboard, squareAt(sq, Direction::HDL));
         setIfValid(bboard, squareAt(sq, Direction::HLD));
         setIfValid(bboard, squareAt(sq, Direction::HLU));
         setIfValid(bboard, squareAt(sq, Direction::HUL));
         break;
      case Piece::King:
         setIfValid(bboard, squareAt(sq, Direction::U));
         setIfValid(bboard, squareAt(sq, Direction::UR));
         setIfValid(bboard, squareAt(sq, Direction::R));
         setIfValid(bboard, squareAt(sq, Direction::DR));
         setIfValid(bboard, squareAt(sq, Direction::D));
         setIfValid(bboard, squareAt(sq, Direction::DL));
         setIfValid(bboard, squareAt(sq, Direction::L));
         setIfValid(bboard, squareAt(sq, Direction::UL));
         break;
      case Piece::Bishop:
         setBitsSlidingPieces(sq, bboard, Directions::diagonal);
         break;
      case Piece::Rook:
         setBitsSlidingPieces(sq, bboard, Directions::orthogonal);
         break;
      case Piece::Queen:
         setBitsSlidingPieces(sq, bboard, Directions::diagonal);
         setBitsSlidingPieces(sq, bboard, Directions::orthogonal);
         break;
      default:
         break;
   }
}

//=============================================================================
void AttackTableUpdater::setBitsSlidingPieces(Square sq, Bitboard& bboard, const HalfCompass& dirs)
{
   for (const Direction dir : dirs)
   {
      for (Square to = squareAt(sq, dir); to != Sq::Invalid; to = squareAt(to, dir))
      {
         bboard.set(to);
         if (board_.isPieceAt(to))
         {
            break;
         }
      }
   }
}

//=============================================================================
void AttackTableUpdater::setBitsSlidingPieces(Square sq, Bitboard& bboard, Direction dir)
{
   bool pieceReached = false;
   for (Square to = squareAt(sq, dir); to != Sq::Invalid; to = squareAt(to, dir))
   {
      bboard.set(to, !pieceReached);
      if (board_.isPieceAt(to))
      {
         pieceReached = true;
      }
   }
}

//=============================================================================
void print(const Bitboard& bboard)
{
   std::string strbits = bboard.to_string();
   for(int i = 0 ; i < 8; ++i)
   {
      std::string sub = strbits.substr(8*i, 8);
      std::string rev(sub.rbegin(), sub.rend());
      std::cout << rev << std::endl;
   }
   std::cout << std::endl;
}

}  // namespace Chess