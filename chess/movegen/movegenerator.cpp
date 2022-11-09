#include "movegenerator.h"

namespace Chess::Internal
{

//=============================================================================
template<typename OutputIt> 
int GenericMoveGenerator::operator()(OutputIt it) const
{
   return Internal::MoveGenerator<OutputIt>(board_, state_, it).exec();
}

//=============================================================================
template<typename OutputIt> 
bool GenericMoveGenerator::isInCheck(Colour c) const
{
   return Internal::MoveGenerator<std::nullptr_t>(board_, state_, nullptr).isInCheck(c);
}

}  // namespace Chess::Internal
