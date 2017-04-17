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
	return punCount;
}

void Player::setPunCount( unsigned char punCount ) {
	punCount = punCount;
}
