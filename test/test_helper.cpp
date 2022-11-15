#include "test_helper.h"

#include "../chess/board.h"
#include "../chess/state.h"
#include "../chess/move.h"
#include "../chess/game.h"

#include <array>

// ============================================================================
// FEN: r3kb1N/Q1qn2p1/8/1pP4p/3Pp1b1/1P2P3/1P3P2/3RK2R w Kq b6 0 18
void setBoard1(Chess::Board& b, Chess::State& s)
{
   using namespace Chess;

   b.setEmpty();
   b.setPiece(Sq::d1, PieceType::Rook, Colour::White);
   b.setPiece(Sq::e1, PieceType::King, Colour::White);
   b.setPiece(Sq::h1, PieceType::Rook, Colour::White);
   b.setPiece(Sq::b2, PieceType::Pawn, Colour::White);
   b.setPiece(Sq::f2, PieceType::Pawn, Colour::White);
   b.setPiece(Sq::b3, PieceType::Pawn, Colour::White);
   b.setPiece(Sq::e3, PieceType::Pawn, Colour::White);
   b.setPiece(Sq::d4, PieceType::Pawn, Colour::White);
   b.setPiece(Sq::c5, PieceType::Pawn, Colour::White);
   b.setPiece(Sq::a7, PieceType::Queen, Colour::White);
   b.setPiece(Sq::h8, PieceType::Knight, Colour::White);

   b.setPiece(Sq::e4, PieceType::Pawn, Colour::Black);
   b.setPiece(Sq::g4, PieceType::Bishop, Colour::Black);
   b.setPiece(Sq::b5, PieceType::Pawn, Colour::Black);
   b.setPiece(Sq::h5, PieceType::Pawn, Colour::Black);
   b.setPiece(Sq::c7, PieceType::Queen, Colour::Black);
   b.setPiece(Sq::d7, PieceType::Knight, Colour::Black);
   b.setPiece(Sq::g7, PieceType::Pawn, Colour::Black);
   b.setPiece(Sq::a8, PieceType::Rook, Colour::Black);
   b.setPiece(Sq::e8, PieceType::King, Colour::Black);
   b.setPiece(Sq::f8, PieceType::Bishop, Colour::Black);

   b.updateKings();

   s = {Colour::White, Colour::Black, true, false, false, true, Sq::b6, 0, 8};
}

// ============================================================================
// FEN: 8/3k4/3b4/3P3p/1p2pP2/1R6/8/4K2R b K f3 0 29
void setBoard2(Chess::Board& b, Chess::State& s)
{
   using namespace Chess;

   b.setEmpty();
   b.setPiece(Sq::e1, PieceType::King, Colour::White);
   b.setPiece(Sq::h1, PieceType::Rook, Colour::White);
   b.setPiece(Sq::b3, PieceType::Rook, Colour::White);
   b.setPiece(Sq::f4, PieceType::Pawn, Colour::White);
   b.setPiece(Sq::d5, PieceType::Pawn, Colour::White);

   b.setPiece(Sq::b4, PieceType::Pawn, Colour::Black);
   b.setPiece(Sq::e4, PieceType::Pawn, Colour::Black);
   b.setPiece(Sq::h5, PieceType::Pawn, Colour::Black);
   b.setPiece(Sq::d6, PieceType::Bishop, Colour::Black);
   b.setPiece(Sq::d7, PieceType::King, Colour::Black);

   b.updateKings();

   s = {Colour::Black, Colour::White, true, false, false, false, Sq::f3, 0, 29};
}

// ============================================================================
// FEN: 3k4/p1p3P1/8/4P1n1/8/1P6/1p1K4/R7 b - - 0 318
void setBoard3(Chess::Board& b, Chess::State& s)
{
   using namespace Chess;

   b.setEmpty();
   b.setPiece(Sq::a1, PieceType::Rook, Colour::White);
   b.setPiece(Sq::d2, PieceType::King, Colour::White);
   b.setPiece(Sq::b3, PieceType::Pawn, Colour::White);
   b.setPiece(Sq::e5, PieceType::Pawn, Colour::White);
   b.setPiece(Sq::g7, PieceType::Pawn, Colour::White);

   b.setPiece(Sq::b2, PieceType::Pawn, Colour::Black);
   b.setPiece(Sq::g5, PieceType::Knight, Colour::Black);
   b.setPiece(Sq::a7, PieceType::Pawn, Colour::Black);
   b.setPiece(Sq::c7, PieceType::Pawn, Colour::Black);
   b.setPiece(Sq::d8, PieceType::King, Colour::Black);

   b.updateKings();

   s = {Colour::Black, Colour::White, false, false, false, false, Sq::Invalid, 0, 31};
}

// ============================================================================
void setCastleBoard1(Chess::Board& b, Chess::State& s)
{
   using namespace Chess;

   b.setEmpty();
   b.setPiece(Sq::a1, PieceType::Rook, Colour::White);
   b.setPiece(Sq::e1, PieceType::King, Colour::White);
   b.setPiece(Sq::h1, PieceType::Rook, Colour::White);
   b.setPiece(Sq::a3, PieceType::Queen, Colour::White);
   b.setPiece(Sq::c7, PieceType::Pawn, Colour::White);

   b.setPiece(Sq::a8, PieceType::Rook, Colour::Black);
   b.setPiece(Sq::e8, PieceType::King, Colour::Black);
   b.setPiece(Sq::h8, PieceType::Rook, Colour::Black);
   b.setPiece(Sq::h6, PieceType::Bishop, Colour::Black);
   b.setPiece(Sq::h2, PieceType::Knight, Colour::Black);

   b.updateKings();

   s = {Colour::Black, Colour::White, true, true, true, true, Sq::Invalid, 2, 35};
}

// ============================================================================
void setCastleBoard2(Chess::Board& b, Chess::State& s)
{
   using namespace Chess;

   b.setEmpty();
   b.setPiece(Sq::a1, PieceType::Rook, Colour::White);
   b.setPiece(Sq::e1, PieceType::King, Colour::White);
   b.setPiece(Sq::f4, PieceType::Queen, Colour::White);

   b.setPiece(Sq::a8, PieceType::Rook, Colour::Black);
   b.setPiece(Sq::e8, PieceType::King, Colour::Black);
   b.setPiece(Sq::b6, PieceType::Rook, Colour::Black);

   b.updateKings();

   s = {Colour::White, Colour::Black, false, true, false, true, Sq::Invalid, 0, 41};
}

// ============================================================================
void setCastleBoard3(Chess::Board& b, Chess::State& s)
{
   using namespace Chess;

   b.setEmpty();
   b.setPiece(Sq::a1, PieceType::Rook, Colour::White);
   b.setPiece(Sq::e1, PieceType::King, Colour::White);
   b.setPiece(Sq::h1, PieceType::Rook, Colour::White);
   b.setPiece(Sq::d7, PieceType::Pawn, Colour::White);

   b.setPiece(Sq::e8, PieceType::King, Colour::Black);
   b.setPiece(Sq::h8, PieceType::Rook, Colour::Black);
   b.setPiece(Sq::a5, PieceType::Bishop, Colour::Black);
   b.setPiece(Sq::d2, PieceType::Rook, Colour::Black);

   b.updateKings();

   s = {Colour::Black, Colour::White, true, true, true, false, Sq::Invalid, 0, 36};
}

// ============================================================================
void setCheckBoard1(Chess::Board& b, Chess::State& s)
{
   using namespace Chess;

   b.setEmpty();
   b.setPiece(Sq::e1, PieceType::King, Colour::White);
   b.setPiece(Sq::d7, PieceType::Pawn, Colour::White);

   b.setPiece(Sq::e8, PieceType::King, Colour::Black);
   b.setPiece(Sq::e2, PieceType::Pawn, Colour::Black);

   b.updateKings();

   s = {Colour::Black, Colour::White, false, false, false, false, Sq::Invalid, 0, 1};
}

// ============================================================================
void setCheckBoard2(Chess::Board& b, Chess::State& s)
{
   using namespace Chess;

   b.setEmpty();
   b.setPiece(Sq::e1, PieceType::King, Colour::White);
   b.setPiece(Sq::g2, PieceType::Knight, Colour::White);
   b.setPiece(Sq::d2, PieceType::Pawn, Colour::White);
   b.setPiece(Sq::e5, PieceType::Queen, Colour::White);

   b.setPiece(Sq::e8, PieceType::King, Colour::Black);
   b.setPiece(Sq::f1, PieceType::Bishop, Colour::Black);
   b.setPiece(Sq::c1, PieceType::Knight, Colour::Black);

   b.updateKings();

   s = {Colour::Black, Colour::White, false, false, false, false, Sq::Invalid, 0, 1};
}

// ============================================================================
void setCheckBoard3(Chess::Board& b, Chess::State& s)
{
   using namespace Chess;

   b.setEmpty();
   b.setPiece(Sq::e1, PieceType::King, Colour::White);
   b.setPiece(Sq::h5, PieceType::Bishop, Colour::White);

   b.setPiece(Sq::e8, PieceType::King, Colour::Black);
   b.setPiece(Sq::c2, PieceType::Knight, Colour::Black);

   b.updateKings();

   s = {Colour::White, Colour::Black, false, false, false, false, Sq::Invalid, 0, 1};
}

// ============================================================================
void setCheckBoard4(Chess::Board& b, Chess::State& s)
{
   using namespace Chess;

   b.setEmpty();
   b.setPiece(Sq::c1, PieceType::King, Colour::White);
   b.setPiece(Sq::d2, PieceType::King, Colour::Black);

   b.updateKings();

   s = {Colour::White, Colour::Black, false, false, false, false, Sq::Invalid, 0, 1};
}

// ============================================================================
uint64_t perft(Chess::Game& g, int depth)
{   
   using namespace Chess;

   if (depth == 0)
   {
      return 1;
   }

   std::array<MoveInt, 256> moves;
   uint64_t numNodes = 0;
   State currState = g.state();

   int numMoves = g.moves(moves.begin());
   for (int i = 0; i < numMoves; ++i)
   {
      if (g.move(moves[i]))
      {
         uint64_t res = perft(g, depth - 1);
         // if (depth == 1)
         // {
         //    Move mv;
         //    fromMoveInt(moves[i], mv);
         //    std::cout << toMoveAN(mv) << ": " << res << "\n";
         // }
         numNodes += res;
      }
      g.unmove(moves[i], currState);
   }

   return numNodes;
}
