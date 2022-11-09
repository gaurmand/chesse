#include "movegenerator.h"

namespace Chess::Internal
{

//=============================================================================
template<typename OutputIt> 
int GenericMoveGenerator::operator()(OutputIt it, bool isInCheck) const
{
   return Internal::MoveGenerator<OutputIt>(board_, state_, isInCheck, it).exec();
}

}  // namespace Chess::Internal
