#include "movegenerator.h"

namespace Chess::Internal
{

//=============================================================================
template<typename OutputIt> 
int GenericMoveGenerator::operator()(OutputIt it) const
{
   return Internal::MoveGenerator<OutputIt>(board_, state_, it).exec();
}

}  // namespace Chess::Internal
