#include "move.h"

namespace Chess
{

//=============================================================================
bool operator==(const Move& lhs, const Move& rhs)
{
   return lhs.from_ == rhs.from_ && 
      lhs.to_ == rhs.to_ && 
      lhs.type_ == rhs.type_ && 
      lhs.capture_ == rhs.capture_; 
}

//=============================================================================

std::ostream& operator<<(std::ostream& os, const Move& m)
{
   return os << toMoveAN(m);
}

//=============================================================================
void fromMoveInt(MoveInt move, Move& moveObj)
{
   moveObj.capture_ = static_cast<Piece>(move & 0xFF);
   move >>= 8;
   moveObj.type_ = static_cast<MoveType>(move & 0xFF);
   move >>= 8;
   moveObj.to_ = move & 0xFF;
   move >>= 8;
   moveObj.from_ = move & 0xFF;
}

//=============================================================================
MoveInt toMoveInt(const Move& moveObj)
{
   MoveInt res = moveObj.from_;
   res <<= 8;
   res |= moveObj.to_;
   res <<= 8;
   res |= static_cast<uint8_t>(moveObj.type_);
   res <<= 8;
   res |= static_cast<uint8_t>(moveObj.capture_);
   return res;
}

//=============================================================================
void fromMoveAN(const MoveAN& str, Move& obj)
{
   obj.from_    = fromAN(str.substr(0,2));
   obj.to_      = fromAN(str.substr(3,2));
   obj.type_    = MoveType::Invalid;
   obj.capture_ = Piece::Empty;
}

//=============================================================================
MoveAN toMoveAN(const Move& obj)
{
   MoveAN res = toAN(obj.from_) + toAN(obj.to_);
   switch (obj.type_)
   {
   case MoveType::KnightPromotion:
      return res + "n";
   case MoveType::BishopPromotion:
      return res + "b";
   case MoveType::RookPromotion:
         return res + "r";
   case MoveType::QueenPromotion:
      return res + "q";
   default:
      return res;
   }
}

//=============================================================================
MoveAN toMoveAN(const BMove& obj)
{
   MoveAN res = toAN(obj.from_) + toAN(obj.to_);
   switch (obj.type_)
   {
   case MoveType::KnightPromotion:
      return res + "n";
   case MoveType::BishopPromotion:
      return res + "b";
   case MoveType::RookPromotion:
         return res + "r";
   case MoveType::QueenPromotion:
      return res + "q";
   default:
      return res;
   }
}

//=============================================================================
Move::operator MoveInt() const
{
   return toMoveInt(*this);
}

//=============================================================================
Move::operator MoveAN() const
{
   return toMoveAN(*this);
}

//=============================================================================
BMove::operator Move() const
{
   Move m;
   m.from_ = from_;
   m.to_   = to_;
   m.type_ = type_;

   switch(captured_)
   {
      case PieceType::Pawn:
         m.capture_ = Piece::Pawn;
         break;
      case PieceType::Knight:
         m.capture_ = Piece::Knight;
         break;      
      case PieceType::Bishop:
         m.capture_ = Piece::Bishop;
         break;      
      case PieceType::Rook:
         m.capture_ = Piece::Rook;
         break;      
      case PieceType::Queen:
         m.capture_ = Piece::Queen;
         break;      
      case PieceType::King:
         m.capture_ = Piece::King;
         break;
      case PieceType::EmptyPiece:
      default:
         m.capture_ = Piece::Empty;
         break;
   }
   
   return m;
}

//=============================================================================
BMove::operator MoveAN() const
{
   return Move(*this);
}

//=============================================================================
bool operator==(const BMove& lhs, const BMove& rhs)
{
      return lhs.from_ == rhs.from_ && 
         lhs.to_ == rhs.to_ && 
         lhs.moved_ == rhs.moved_ && 
         lhs.captured_ == rhs.captured_ &&
         lhs.movedColour_ == rhs.movedColour_ &&
         lhs.capColour_ == rhs.capColour_ &&
         lhs.type_ == rhs.type_;
}

//=============================================================================
std::ostream& operator<<(std::ostream& os, const BMove& m)
{
   return os << toMoveAN(m);
}

}  // namespace Chess