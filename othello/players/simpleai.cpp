#include "../inc/players/simpleai.hpp"

using namespace std;
using namespace Othello::Board;
using namespace Othello::Players;

SimpleAI::SimpleAI( string name, Pun::Colors color ) : Player( name, color ) {}

Move SimpleAI::getMove() {
	return Move( 0, 0 );
}