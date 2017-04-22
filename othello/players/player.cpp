#include "../inc/players/player.hpp"

using namespace std;
using namespace Othello::Board;
using namespace Othello::Players;

Player::Player( string name, Pun::Colors color ) : m_name( name ), m_color( color ) {}

const string &Player::getName() const {
	return m_name;
}

Pun::Colors Player::getColor() const {
	return m_color;
}

bool Player::canPlay() const {
	return m_canPlay;
}

void Player::setCanPlay() {
	m_canPlay = true;
}

void Player::setCannotPlay() {
	m_canPlay = false;
}

unsigned char Player::getPunCount() const {
	return m_punCount;
}

void Player::setPunCount( unsigned char punCount ) {
	m_punCount = punCount;
}

void Player::setBoard( GameBoard* board ) {
	m_board = board;
}

bool Player::typeCheck( int typeInt ) {
	if( typeInt < static_cast<int>( Player::Type::Human ) ) return false;
	if( typeInt > static_cast<int>( Player::Type::EnhancedAI ) ) return false;

	switch( static_cast<Player::Type>( typeInt ) ) {
		case Player::Type::Human:
		case Player::Type::SimpleAI:
		case Player::Type::EnhancedAI:
			return true;
		default:
			return false;
	}
}
