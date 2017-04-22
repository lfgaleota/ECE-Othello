#include "../../inc/ui/games/allegrovalidmovetreeviewer.hpp"

using namespace std;
using namespace Othello::Board;
using namespace Othello::UI::Games;

AllegroValidMoveTreeViewer::AllegroValidMoveTreeViewer() {}

AllegroValidMoveTreeViewer::AllegroValidMoveTreeViewer( Othello::Board::Tree::ValidMoveNode** m_tree, unsigned int depth, BITMAP* page ) : m_tree( m_tree ), m_page( page ), m_depth( depth ) {
	m_cursors = std::vector<unsigned int>( depth, 0 );
	m_nodes = std::vector<const Tree::ValidMoveNode*>( depth, nullptr );
}

void AllegroValidMoveTreeViewer::render() {
	if( opened ) {
		if( *m_tree == nullptr ) {
			opened = false;
			return;
		}

		renderTree();

		if( key[ KEY_UP ] ) {
			if( !m_keyPressed ) {
				if( m_cursors.at( x ) > 0 ) {
					m_cursors.at( x )--;
					for( unsigned int i = x + 1; i < m_cursors.size(); i++ )
						m_cursors.at( i ) = 0;
				}
			}
			m_keyPressed = true;
		} else if( key[ KEY_DOWN ] ) {
			if( !m_keyPressed ) {
				if( m_cursors.at( x ) < m_nodes.at( x )->getNextNodes().size() - 1 ) {
					m_cursors.at( x )++;
					for( unsigned int i = x + 1; i < m_cursors.size(); i++ )
						m_cursors.at( i ) = 0;
				}
			}
			m_keyPressed = true;
		} else if( key[ KEY_LEFT ] ) {
			if( !m_keyPressed ) {
				if( x > 0 )
					x--;
			}
			m_keyPressed = true;
		} else if( key[ KEY_RIGHT ] ) {
			if( !m_keyPressed ) {
				if( x < m_depth - 1 )
					x++;
			}
			m_keyPressed = true;
		} else {
			m_keyPressed = false;
		}
	}
}

void AllegroValidMoveTreeViewer::renderTree() {
	m_nodes.at( 0 ) = *m_tree;

	renderColumn( *m_tree, 1 );
}

void AllegroValidMoveTreeViewer::renderColumn( const Tree::ValidMoveNode* node, unsigned int depth ) {
	unsigned int i = 0, actuali = 0, cursor = m_cursors.at( depth - 1 ), offset_x, offset_y;
	bool showCursor, selected;

	for( const Tree::ValidMoveNode& next : node->getNextNodes() ) {
		selected = false;
		showCursor = false;

		if( i >= cursor ) {
			offset_x = VIEWER_MARGIN + ( depth - 1 ) * VIEWER_CASE_SIZE * ( GameBoard::sizeEdge + VIEWER_CASE_MARGIN );
			offset_y = VIEWER_MARGIN + actuali * VIEWER_CASE_SIZE * ( GameBoard::sizeEdge + VIEWER_CASE_MARGIN );

			if( i == cursor ) {
				if( x == depth - 1 )
					selected = true;
				showCursor = true;

				if( depth < m_cursors.size() ) {
					m_nodes.at( depth ) = &next;
					renderColumn( &next, depth + 1 );
				}
			}
			renderNode( next.getBoard(), next.getEval(), offset_x, offset_y, showCursor, selected );
			actuali++;
		}
		i++;
	}
}

void AllegroValidMoveTreeViewer::renderNode( const GameBoard* ref, int eval, unsigned int offset_x, unsigned int offset_y, bool showCursor, bool selected ) {
	Pun::Colors piece;
	int x, y;

	if( showCursor ) {
		rectfill( m_page, offset_x - VIEWER_BORDER_SIZE, offset_y - VIEWER_BORDER_SIZE, offset_x + VIEWER_CASE_SIZE * GameBoard::sizeEdge + VIEWER_BORDER_SIZE, offset_y + VIEWER_CASE_SIZE * GameBoard::sizeEdge + VIEWER_BORDER_SIZE, ( selected ? VIEWER_BORDER_COLOR_SELECTED : VIEWER_BORDER_COLOR ) );
	}
	rectfill( m_page, offset_x, offset_y, offset_x + VIEWER_CASE_SIZE * GameBoard::sizeEdge, offset_y + VIEWER_CASE_SIZE * GameBoard::sizeEdge, VIEWER_CASE_COLOR );

	for( unsigned char j = 0; j < GameBoard::sizeEdge; j++ ) { //browse again
		for( unsigned char i = 0; i < GameBoard::sizeEdge; i++ ) {
			piece = ref->at( i, j );
			x = offset_x + VIEWER_CASE_SIZE * i + VIEWER_CASE_SIZE / 2;
			y = offset_y + VIEWER_CASE_SIZE * j + VIEWER_CASE_SIZE / 2;

			if( piece == Pun::white ) {
				circlefill( m_page, x, y, VIEWER_CASE_SIZE / 2, VIEWER_PUN_COLOR_WHITE );
			} else if( piece == Pun::black ) {
				circlefill( m_page, x, y, VIEWER_CASE_SIZE / 2, VIEWER_PUN_COLOR_BLACK );
			}
		}
	}

	textprintf_centre_ex( m_page, font, offset_x + VIEWER_CASE_SIZE * GameBoard::sizeEdge / 2, offset_y + VIEWER_CASE_SIZE * GameBoard::sizeEdge, VIEWER_TEXT_COLOR, VIEWER_TEXT_BGCOLOR, "%d", eval );
	if( showCursor )
		textprintf_ex( m_page, font, offset_x + VIEWER_CASE_SIZE * GameBoard::sizeEdge, offset_y + VIEWER_CASE_SIZE * GameBoard::sizeEdge/ 2, VIEWER_TEXT_COLOR, VIEWER_TEXT_BGCOLOR, ">" );
}