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
