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

}  // namespace Chess::Internal
