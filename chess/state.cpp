#include "state.h"

#include <algorithm>
#include <sstream>
#include <stdexcept>

namespace Chess
{

//=============================================================================
bool operator==(const State& lhs, const State& rhs)
{
   return lhs.active_ == rhs.active_ && 
      lhs.inactive_ == rhs.inactive_ && 
      lhs.canWhiteShortCastle_ == rhs.canWhiteShortCastle_ && 
      lhs.canWhiteLongCastle_ == rhs.canWhiteLongCastle_ && 
      lhs.canBlackShortCastle_ == rhs.canBlackShortCastle_ && 
      lhs.canBlackLongCastle_ == rhs.canBlackLongCastle_ && 
      lhs.enPassantSquare_ == rhs.enPassantSquare_ && 
      lhs.halfMoveClock_ == rhs.halfMoveClock_ && 
      lhs.fullMoveClock_ == rhs.fullMoveClock_;
}

//=============================================================================
bool operator!=(const State& lhs, const State& rhs)
{
   return !(lhs == rhs);
}

//=============================================================================
void fromStateInt(StateInt state, State& obj)
{
   obj.fullMoveClock_ = state & 0x3FF;
   state >>= 10;
   obj.halfMoveClock_ = state & 0x1FF;
   state >>= 9;
   obj.enPassantSquare_ = state & 0xFF;
   state >>= 8;
   obj.canBlackLongCastle_ = state & 0x1;
   state >>= 1;
   obj.canBlackShortCastle_ = state & 0x1;
   state >>= 1;
   obj.canWhiteLongCastle_ = state & 0x1;
   state >>= 1;
   obj.canWhiteShortCastle_ = state & 0x1;
   state >>= 1;
   if (state)
   {
      obj.active_ = Colour::White;
      obj.inactive_ = Colour::Black;
   }
   else
   {
      obj.active_ = Colour::Black;
      obj.inactive_ = Colour::White;
   }
}

//=============================================================================
StateInt toStateInt(const State& obj)
{
   StateInt res = obj.active_ == Colour::White ? 0x1 : 0x0;
   res <<= 1;
   res |= obj.canWhiteShortCastle_;
   res <<= 1;
   res |= obj.canWhiteLongCastle_;
   res <<= 1;
   res |= obj.canBlackShortCastle_;
   res <<= 1;
   res |= obj.canBlackLongCastle_;
   res <<= 8;
   res |= obj.enPassantSquare_;
   res <<= 9;
   res |= obj.halfMoveClock_;
   res <<= 10;
   res |= obj.fullMoveClock_;
   return res;
}

//=============================================================================
State fromFEN(const FEN& fen)
{
   State res;
   std::istringstream stream(fen);
   
   // Skip to relevant part of FEN
   const std::streamsize maxFENLength = 100;
   if (!(stream.ignore(maxFENLength, ' ')))
   {
      throw std::invalid_argument("Invalid FEN");
   }

   // Active / Inactive
   char active;
   if (!(stream >> active))
   {
      throw std::invalid_argument("Invalid FEN");
   }
   if (active == 'b')
   {
      res.active_   = Colour::Black;
      res.inactive_ = Colour::White;
   }
   else
   {
      res.active_   = Colour::White;
      res.inactive_ = Colour::Black;
   }

   // Castling
   std::string castling;
   if (!(stream >> castling))
   {
      throw std::invalid_argument("Invalid FEN");
   }

   res.canWhiteShortCastle_ = castling.find('K') != std::string::npos;
   res.canWhiteLongCastle_  = castling.find('Q') != std::string::npos;
   res.canBlackShortCastle_ = castling.find('k') != std::string::npos;
   res.canBlackLongCastle_  = castling.find('q') != std::string::npos;

   // En Passant
   std::string enPassant;
   if (!(stream >> enPassant))
   {
      throw std::invalid_argument("Invalid FEN");
   }

   try
   {
      res.enPassantSquare_ = fromAN(enPassant);
   }
   catch(const std::exception& e)
   {
      res.enPassantSquare_ = Sq::Invalid;
   }
   
   // Halfmove clock
   int halfmoveClock;
   if (!(stream >> halfmoveClock))
   {
      throw std::invalid_argument("Invalid FEN");
   }
   res.halfMoveClock_ = halfmoveClock;

   // Fullmove clock
   int fullmoveClock;
   if (!(stream >> fullmoveClock))
   {
      throw std::invalid_argument("Invalid FEN");
   }
   res.fullMoveClock_ = fullmoveClock;

   return res;
}

//=============================================================================
void toggleColour(State& state)
{
   std::swap(state.active_, state.inactive_);
}

//=============================================================================
Colour enemy(Colour c)
{
   return c == Colour::White ? Colour::Black : Colour::White;
}

}  // namespace Chess
