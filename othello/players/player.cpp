#include "../../inc/players/player.hpp"

Player::Player( std::string name, Pun::Colors color ) : m_name( name ), m_color( color ) {}

const std::string &Player::getName() const {
	return m_name;
}

Pun::Colors Player::getColor() const {
	return m_color;
}
