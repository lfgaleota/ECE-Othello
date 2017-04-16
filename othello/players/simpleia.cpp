#include "../inc/players/simpleia.hpp"

using namespace std;
using namespace Othello::Board;
using namespace Othello::Players;

SimpleIA::SimpleIA( string name, Pun::Colors color ) : Player( name, color ) {}

Move SimpleIA::getMove() {
	return Move( 0, 0 );
}