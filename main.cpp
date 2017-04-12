#include "inc/board/pun.hpp"
#include "inc/board/gameboard.hpp"
#include "inc/game.hpp"
#include "inc/players/human.hpp"

//ENORME idée, si on a le temps on fait un undo, on annule le coup qui vient d'être joué et on propose de le rejouer !

using namespace std;
using namespace Othello;
using namespace Othello::Board;
using namespace Othello::Players;

int main() {
	std::vector<Player*> players;
	players.push_back( new Human( "Player1", Pun::black ) );
	players.push_back( new Human( "Player2", Pun::white ) );

	Game othello( players );
	return 0;
}
