#include "../chess/game.h"
#include "../test/test_helper.h"

using namespace Chess;

int main()
{
   Game g;
   perft(g, 5);

   return 0;
}
