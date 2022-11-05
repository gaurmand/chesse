#ifndef CHESS_INTERNAL_OUTPUTTER_H
#define CHESS_INTERNAL_OUTPUTTER_H

#include "../move.h"

#include <string>

namespace Chess::Internal
{

template<typename MoveFormat, typename OutputIt>
class Outputter
{
public:
   //==========================================================================
   Outputter(OutputIt out) : out_(out) {}

   //==========================================================================
   int numOutputted() const;

   //==========================================================================
   Outputter& operator<<(const Move& mv);

private:
   //==========================================================================
   OutputIt out_;
   int numOutputted_ = 0;
};

}  // namespace Chess::Internal

#include "outputter.cpp" // template impl

#endif   // CHESS_INTERNAL_OUTPUTTER_H