#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H

#include <cstdint>
#include <string>

namespace Chess
{

using Square = uint8_t;
using AN = std::string;

Square fromAN(const AN& squareStr);
AN toAN(Square sqr);

}  // namespace Chess


#endif   // CHESS_SQUARE_H