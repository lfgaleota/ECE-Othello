/// \author { Louis-Félix Galeota, Romain Brisse }
/// \date 24 Avril 2017

#include "othello/inc/board/pun.hpp"
#include "othello/inc/board/gameboard.hpp"
#include "othello/inc/game.hpp"
#include "othello/inc/players/human.hpp"
#include "othello/inc/players/enhancedai.hpp"
#include "othello/inc/players/simpleai.hpp"


using namespace std;
using namespace Othello;
using namespace Othello::Board;
using namespace Othello::Players;

int main() {
	std::vector<Player*> players;
	players.push_back( new Human( "Player1", Pun::black ) );
	players.push_back( new EnhancedAI( "Player2", Pun::white ) );

	/** This line starts the Othello game. **/
	Game othello( players );
	return 0;
}
