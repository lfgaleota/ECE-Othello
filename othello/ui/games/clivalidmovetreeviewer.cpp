#include "../../inc/ui/games/clivalidmovetreeviewer.hpp"

using namespace std;
using namespace Othello::Board;
using namespace Othello::UI::Games;

CLIValidMoveTreeViewer::CLIValidMoveTreeViewer( Othello::Board::Tree::ValidMoveNode* m_tree, unsigned int depth ) : m_tree( m_tree ) {
	if( m_tree != nullptr ) {
		m_cursors = std::vector<unsigned int>( depth, 0 );
		m_nodes = std::vector<const Tree::ValidMoveNode*>( depth, nullptr );
		cli = Functions::CLI();

		Functions::Keys::Key key;

		for( bool loop = true; loop; ) {
			cli.clearScreen();
			render();
			key = cli.getKey(); //gets the use entry choice

			switch( key ) {
				case Functions::Keys::Key::ArrowUp:
					if( m_cursors.at( x ) > 0 ) {
						m_cursors.at( x )--;
						for( unsigned int i = x + 1; i < m_cursors.size(); i++ )
							m_cursors.at( i ) = 0;
					}
					break;

				case Functions::Keys::Key::ArrowDown:
					if( m_cursors.at( x ) < m_nodes.at( x )->getNextNodes().size() - 1 ) {
						m_cursors.at( x )++;
						for( unsigned int i = x + 1; i < m_cursors.size(); i++ )
							m_cursors.at( i ) = 0;
					}
					break;

				case Functions::Keys::Key::ArrowLeft:
					if( x > 0 )
						x--;
					break;

				case Functions::Keys::Key::ArrowRight:
					if( x < depth - 1 )
						x++;
					break;

				case Functions::Keys::Key::N0:
				case Functions::Keys::Key::Escape:
					loop = false;
					break;

				default:
					break;
			}
		}
	}
}

void CLIValidMoveTreeViewer::render() {
	m_nodes.at( 0 ) = m_tree;
	if( x == 0 )
		cli.setColor( BACKGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY );
	cli.moveCursor( 3, 0 );
	cout << ">";
	cli.moveCursor( 4, 0 );
	cout << ">";
	cli.resetColor();

	renderColumn( m_tree, 1 );

	unsigned int width, height;

	cli.getSize( width, height );

	cli.setColor( BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY );
	cli.moveCursor( height - 1, 0 );
	for( unsigned int i = 0; i < width; i++ )
		cout << " ";

	cli.moveCursor( height - 1, 0 );
	cli.setColor( BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY );
	cout << "0";
	cli.setColor( FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY );
	cout << "Retour";

	cli.resetColor();
	cli.moveCursor( 0, 0 );
}

void CLIValidMoveTreeViewer::renderColumn( const Tree::ValidMoveNode* node, unsigned int depth ) {
	unsigned int i = 0, actuali = 0, cursor = m_cursors.at( depth - 1 ), offset_x, offset_y;

	for( const Tree::ValidMoveNode& next : node->getNextNodes() ) {
		if( i >= cursor ) {
			offset_x = 2 + ( depth - 1 ) * ( GameBoard::sizeEdge + 2 );
			offset_y = actuali * ( GameBoard::sizeEdge + 1 );

			if( i == cursor && depth < m_cursors.size() ) {
				if( x == depth )
					cli.setColor( BACKGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY );

				m_nodes.at( depth ) = &next;
				cli.moveCursor( offset_y + 3, offset_x + GameBoard::sizeEdge );
				cout << ">";
				cli.moveCursor( offset_y + 4, offset_x + GameBoard::sizeEdge );
				cout << ">";
				cli.resetColor();

				renderColumn( &next, depth + 1 );
				cli.resetColor();
			}
			renderNode( next.getBoard(), next.getEval(), offset_x, offset_y );
			actuali++;
		}
		i++;
	}
}

void CLIValidMoveTreeViewer::renderNode( const GameBoard* ref, int eval, unsigned int offset_x, unsigned int offset_y ) {
	Pun::Colors piece;

	for( unsigned char j = 0; j < GameBoard::sizeEdge; j++ ) { //browse again
		for( unsigned char i = 0; i < GameBoard::sizeEdge; i++ ) {
			piece = ref->at( i, j );

			if( piece == Pun::white )
				cli.setColor( BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
			else if( piece == Pun::black )
				cli.setColor( 0 );

			cout << " ";

			cli.moveCursor( offset_y + i, offset_x + j );

			cli.resetColor();
		}
	}

	cli.moveCursor( offset_y, offset_x + 1 );
	cout << eval;

	if( offset_x > 0 ) {
		for( unsigned char j = 0; j < GameBoard::sizeEdge; j++ ) {
			cli.moveCursor( offset_y + j, offset_x - 1 );
			cout << "|";
		}
	}
}