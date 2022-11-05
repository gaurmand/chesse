#include "movegenerator.h"

namespace Chess::Internal
{

//=============================================================================
template<typename MoveFormat>
template<typename OutputIt> 
int GenericMoveGenerator<MoveFormat>::operator()(OutputIt it, bool checkLegal) const
{
   return MoveGenerator<MoveFormat, OutputIt>(board_, state_, it, checkLegal).exec();
}

}  // namespace Chess::Internal
