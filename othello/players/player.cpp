#include "../inc/players/player.hpp"

using namespace std;
using namespace Othello::Board;
using namespace Othello::Players;

/**
* @brief Constructeur surchargé de la classe Player
**/
Player::Player( string name, Pun::Colors color ) : m_name( name ), m_color( color ) {}

/**
* @brief Accesseur du nom du joueur
* @return nom du joueur
**/
const string &Player::getName() const {
	return m_name;
}

/**
* @brief Accesseur de la couleur du joueur
* @return couleur du joueur
**/
Pun::Colors Player::getColor() const {
	return m_color;
}

/**
* @brief Accesseur de la possibilité de jouer ou non du joueur
* @return la possibilité
**/
bool Player::canPlay() const {
	return m_canPlay;
}

/**
* @brief Mutateur de la possibilité de jouer
**/
void Player::setCanPlay() {
	m_canPlay = true;
}

/**
* @brief Mutateur de la non possiblité de jouer
**/
void Player::setCannotPlay() {
	m_canPlay = false;
}

/**
* @brief Accesseur du compte des pions du joueur
* @return le compte des pions
**/
unsigned char Player::getPunCount() const {
	return m_punCount;
}

/**
* @brief Mutateur du compte des pions du joueur
**/
void Player::setPunCount( unsigned char punCount ) {
	m_punCount = punCount;
}

/**
* @brief Mutateur du plateau
**/
void Player::setBoard( GameBoard* board ) {
	m_board = board;
}
