#include "movegenerator.h"

namespace Chess::Internal
{

//=============================================================================
template<typename MoveFormat>
template<typename OutputIt> 
int GenericMoveGenerator<MoveFormat>::operator()(OutputIt it) const
{
   return MoveGenerator<MoveFormat, OutputIt>(board_, state_, it).exec();
}

//=============================================================================
template<typename MoveFormat>
bool GenericMoveGenerator<MoveFormat>::isInCheck(Colour c) const
{
   return MoveGenerator<MoveFormat, std::nullptr_t>(board_, state_, nullptr).isInCheck(c);
}

}  // namespace Chess::Internal
