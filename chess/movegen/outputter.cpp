#include "outputter.h"

namespace Chess::Internal
{

//=============================================================================
template<typename OutputIt>
class Outputter<Move, OutputIt>
{
public:
   //==========================================================================
   Outputter(OutputIt out)  : out_(out) {}

   //==========================================================================
   int numOutputted() const { return numOutputted_; }

   //==========================================================================
   Outputter& operator<<(const Move& mv)
   {
      *out_ = mv;
      out_++;
      numOutputted_++;
      return *this;
   }

private:
   //==========================================================================
   OutputIt out_;
   int numOutputted_ = 0;
};

//=============================================================================
template<typename OutputIt>
class Outputter<MoveInt, OutputIt>
{
public:
   //==========================================================================
   Outputter(OutputIt out)  : out_(out) {}

   //==========================================================================
   int numOutputted() const { return numOutputted_; }

   //==========================================================================
   Outputter& operator<<(const Move& mv)
   {
      *out_ = toMoveInt(mv);
      out_++;
      numOutputted_++;
      return *this;
   }

private:
   //==========================================================================
   OutputIt out_;
   int numOutputted_ = 0;
};

//=============================================================================
template<typename OutputIt>
class Outputter<MoveAN, OutputIt>
{
public:
   //==========================================================================
   Outputter(OutputIt out)  : out_(out) {}

   //==========================================================================
   int numOutputted() const { return numOutputted_; }

   //==========================================================================
   Outputter& operator<<(const Move& mv)
   {
      *out_ = toMoveAN(mv);
      out_++;
      numOutputted_++;
      return *this;
   }

private:
   //==========================================================================
   OutputIt out_;
   int numOutputted_ = 0;
};

}  // namespace Chess::Internal
