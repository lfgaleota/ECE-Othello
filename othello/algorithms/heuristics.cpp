#include "../inc/algorithms/heuristics.hpp"

using namespace std;
using namespace Othello::Algorithms;
using namespace Othello::Board;

int Heuristics::simple( Othello::Board::GameBoard* ref, Othello::Board::Pun::Colors color ) {
	if( color == Pun::black )
		return ref->m_count.black - ref->m_count.white;
	else if( color == Pun::white )
		return ref->m_count.white - ref->m_count.black;
	return 0;
}
