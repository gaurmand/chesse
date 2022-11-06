#include "test_helper.h"

#include "chess/board.h"
#include "chess/state.h"

// ============================================================================
// FEN: r3kb1N/Q1qn2p1/8/1pP4p/3Pp1b1/1P2P3/1P3P2/3RK2R w Kq b6 0 18
void setBoard1(Chess::Board& b, Chess::State& s)
{
   using namespace Chess;

   b.setEmpty();
   b.setPiece(Sq::d1, Piece::Rook, Colour::White);
   b.setPiece(Sq::e1, Piece::King, Colour::White);
   b.setPiece(Sq::h1, Piece::Rook, Colour::White);
   b.setPiece(Sq::b2, Piece::Pawn, Colour::White);
   b.setPiece(Sq::f2, Piece::Pawn, Colour::White);
   b.setPiece(Sq::b3, Piece::Pawn, Colour::White);
   b.setPiece(Sq::e3, Piece::Pawn, Colour::White);
   b.setPiece(Sq::d4, Piece::Pawn, Colour::White);
   b.setPiece(Sq::c5, Piece::Pawn, Colour::White);
   b.setPiece(Sq::a7, Piece::Queen, Colour::White);
   b.setPiece(Sq::h8, Piece::Knight, Colour::White);

   b.setPiece(Sq::e4, Piece::Pawn, Colour::Black);
   b.setPiece(Sq::g4, Piece::Bishop, Colour::Black);
   b.setPiece(Sq::b5, Piece::Pawn, Colour::Black);
   b.setPiece(Sq::h5, Piece::Pawn, Colour::Black);
   b.setPiece(Sq::c7, Piece::Queen, Colour::Black);
   b.setPiece(Sq::d7, Piece::Knight, Colour::Black);
   b.setPiece(Sq::g7, Piece::Pawn, Colour::Black);
   b.setPiece(Sq::a8, Piece::Rook, Colour::Black);
   b.setPiece(Sq::e8, Piece::King, Colour::Black);
   b.setPiece(Sq::f8, Piece::Bishop, Colour::Black);

   b.updateKings();

   s = {Colour::White, Colour::Black, true, false, false, true, Sq::b6, 0, 8};
}

// ============================================================================
// FEN: 8/3k4/3b4/3P3p/1p2pP2/1R6/8/4K2R b K f3 0 29
void setBoard2(Chess::Board& b, Chess::State& s)
{
   using namespace Chess;

   b.setEmpty();
   b.setPiece(Sq::e1, Piece::King, Colour::White);
   b.setPiece(Sq::h1, Piece::Rook, Colour::White);
   b.setPiece(Sq::b3, Piece::Rook, Colour::White);
   b.setPiece(Sq::f4, Piece::Pawn, Colour::White);
   b.setPiece(Sq::d5, Piece::Pawn, Colour::White);

   b.setPiece(Sq::b4, Piece::Pawn, Colour::Black);
   b.setPiece(Sq::e4, Piece::Pawn, Colour::Black);
   b.setPiece(Sq::h5, Piece::Pawn, Colour::Black);
   b.setPiece(Sq::d6, Piece::Bishop, Colour::Black);
   b.setPiece(Sq::d7, Piece::King, Colour::Black);

   b.updateKings();

   s = {Colour::Black, Colour::White, true, false, false, false, Sq::f3, 0, 29};
}

// ============================================================================
// FEN: 3k4/p1p3P1/8/4P1n1/8/1P6/1p1K4/R7 b - - 0 318
void setBoard3(Chess::Board& b, Chess::State& s)
{
   using namespace Chess;

   b.setEmpty();
   b.setPiece(Sq::a1, Piece::Rook, Colour::White);
   b.setPiece(Sq::d2, Piece::King, Colour::White);
   b.setPiece(Sq::b3, Piece::Pawn, Colour::White);
   b.setPiece(Sq::e5, Piece::Pawn, Colour::White);
   b.setPiece(Sq::g7, Piece::Pawn, Colour::White);

   b.setPiece(Sq::b2, Piece::Pawn, Colour::Black);
   b.setPiece(Sq::g5, Piece::Knight, Colour::Black);
   b.setPiece(Sq::a7, Piece::Pawn, Colour::Black);
   b.setPiece(Sq::c7, Piece::Pawn, Colour::Black);
   b.setPiece(Sq::d8, Piece::King, Colour::Black);

   b.updateKings();

   s = {Colour::Black, Colour::White, false, false, false, false, Sq::Invalid, 0, 31};
}

// ============================================================================
void setCastleBoard1(Chess::Board& b, Chess::State& s)
{
   using namespace Chess;

   b.setEmpty();
   b.setPiece(Sq::a1, Piece::Rook, Colour::White);
   b.setPiece(Sq::e1, Piece::King, Colour::White);
   b.setPiece(Sq::h1, Piece::Rook, Colour::White);
   b.setPiece(Sq::a3, Piece::Queen, Colour::White);
   b.setPiece(Sq::c7, Piece::Pawn, Colour::White);

   b.setPiece(Sq::a8, Piece::Rook, Colour::Black);
   b.setPiece(Sq::e8, Piece::King, Colour::Black);
   b.setPiece(Sq::h8, Piece::Rook, Colour::Black);
   b.setPiece(Sq::h6, Piece::Bishop, Colour::Black);
   b.setPiece(Sq::h2, Piece::Knight, Colour::Black);

   b.updateKings();

   s = {Colour::Black, Colour::White, true, true, true, true, Sq::Invalid, 2, 35};
}

// ============================================================================
void setCastleBoard2(Chess::Board& b, Chess::State& s)
{
   using namespace Chess;

   b.setEmpty();
   b.setPiece(Sq::a1, Piece::Rook, Colour::White);
   b.setPiece(Sq::e1, Piece::King, Colour::White);
   b.setPiece(Sq::f4, Piece::Queen, Colour::White);

   b.setPiece(Sq::a8, Piece::Rook, Colour::Black);
   b.setPiece(Sq::e8, Piece::King, Colour::Black);
   b.setPiece(Sq::b6, Piece::Rook, Colour::Black);

   b.updateKings();

   s = {Colour::White, Colour::Black, false, true, false, true, Sq::Invalid, 0, 41};
}

// ============================================================================
void setCheckBoard1(Chess::Board& b, Chess::State& s)
{
   using namespace Chess;

   b.setEmpty();
   b.setPiece(Sq::e1, Piece::King, Colour::White);
   b.setPiece(Sq::d7, Piece::Pawn, Colour::White);

   b.setPiece(Sq::e8, Piece::King, Colour::Black);
   b.setPiece(Sq::e2, Piece::Pawn, Colour::Black);

   b.updateKings();

   s = {Colour::Black, Colour::White, false, false, false, false, Sq::Invalid, 0, 1};
}

// ============================================================================
void setCheckBoard2(Chess::Board& b, Chess::State& s)
{
   using namespace Chess;

   b.setEmpty();
   b.setPiece(Sq::e1, Piece::King, Colour::White);
   b.setPiece(Sq::g2, Piece::Knight, Colour::White);
   b.setPiece(Sq::d2, Piece::Pawn, Colour::White);
   b.setPiece(Sq::e5, Piece::Queen, Colour::White);

   b.setPiece(Sq::e8, Piece::King, Colour::Black);
   b.setPiece(Sq::f1, Piece::Bishop, Colour::Black);
   b.setPiece(Sq::c1, Piece::Knight, Colour::Black);

   b.updateKings();

   s = {Colour::Black, Colour::White, false, false, false, false, Sq::Invalid, 0, 1};
}

// ============================================================================
void setCheckBoard3(Chess::Board& b, Chess::State& s)
{
   using namespace Chess;

   b.setEmpty();
   b.setPiece(Sq::e1, Piece::King, Colour::White);
   b.setPiece(Sq::h5, Piece::Bishop, Colour::White);

   b.setPiece(Sq::e8, Piece::King, Colour::Black);
   b.setPiece(Sq::c2, Piece::Knight, Colour::Black);

   b.updateKings();

   s = {Colour::White, Colour::Black, false, false, false, false, Sq::Invalid, 0, 1};
}

// ============================================================================
void setCheckBoard4(Chess::Board& b, Chess::State& s)
{
   using namespace Chess;

   b.setEmpty();
   b.setPiece(Sq::c1, Piece::King, Colour::White);
   b.setPiece(Sq::d2, Piece::King, Colour::Black);

   b.updateKings();

   s = {Colour::White, Colour::Black, false, false, false, false, Sq::Invalid, 0, 1};
}
