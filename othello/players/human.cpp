#include "../inc/players/human.hpp"

using namespace std;
using namespace Othello::Board;
using namespace Othello::Players;

/**
* @brief Constructeur surchargé de la classe Human
**/
Human::Human( string name, Pun::Colors color ) : UIPlayer( name, color ) {}

/**
* @brief Accesseur en lecture du mouvement dans la classe Human
* @return Le mouvement pour l'UI
**/
Move Human::getMove() {
	return m_ui->getMove();
}
