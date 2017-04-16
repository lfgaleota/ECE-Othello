#include "../inc/board/gameboard.hpp"

using namespace std;
using namespace Othello::Board;

/**
 * @bried Constructeur de plateau de jeu
 * @details Initialise un nouveau plateau de jeu, en concordance avec les règles du jeu. Initialise également les différents éléments spécifiques qui ne correspondent pas au jeu en lui-même, mais qui permettent de faire fonctionner l'implémentation, comme la liste des cases vides voisines à des pions.
 */
GameBoard::GameBoard() {
	// On initialise la matrice de jeu conformément au règles
	for( unsigned char i = 0; i < GameBoard::sizeEdge; i++ ) {
		for( unsigned char j = 0; j < GameBoard::sizeEdge; j++ ) {
			if(( i == 3 && j == 3 ) || ( i == 4 && j == 4 )) {
				quickSet( i, j, Pun::black );
			} else {
				if(( i == 3 && j == 4 ) || ( i == 4 && j == 3 )) {
					quickSet( i, j, Pun::white );
				} else {
					quickSet( i, j, Pun::blank );
				}
			}
		}
	}

	// On indique toutes les cases voisines à des pions qui sont actuellement vides, en accord avec le plateau initalisé
	quickEmptyNeighborsSet( 2, 2 );
	quickEmptyNeighborsSet( 2, 3 );
	quickEmptyNeighborsSet( 2, 4 );
	quickEmptyNeighborsSet( 2, 5 );
	quickEmptyNeighborsSet( 3, 2 );
	quickEmptyNeighborsSet( 4, 2 );
	quickEmptyNeighborsSet( 5, 2 );
	quickEmptyNeighborsSet( 5, 3 );
	quickEmptyNeighborsSet( 5, 4 );
	quickEmptyNeighborsSet( 5, 5 );
	quickEmptyNeighborsSet( 4, 5 );
	quickEmptyNeighborsSet( 3, 5 );
}

/**
 * @brief Constructeur par copie de plateau de jeu
 * @details Clone un plateau de jeu.
 * @param[in] ref Plateau de référence à cloner
 */
GameBoard::GameBoard( GameBoard& ref ) {
	m_emptyNeighbors = ref.m_emptyNeighbors;
	std::memcpy( m_board, ref.m_board, sizeof( Pun ) * GameBoard::size );
}

GameBoard::~GameBoard() {

}

/**
 * @brief Accesseur de plateau de jeu
 * @return Pointeur constant vers le plateau de jeu
 */
const GameBoard::punArray GameBoard::getBoard() {
	return (const GameBoard::punArray) m_board;
}

/**
 * @brief Accesseur de coups valides
 * @return Référence constante vers la liste de coups valides
 */
const std::list<ValidMove> &GameBoard::getValidMoves() {
	return m_validMoves;
}

/**
 * @brief Accesseur de plateau
 * @details Retourne l'élément du plateau aux coordonnées indiquées, avec vérifications des entrées.
 * @param[in] x Coordonnée en abscisse de l'emplacement
 * @param[in] y Coordonnée en ordonnée de l'emplacement
 * @return Élément aux coordonnées indiquées
 */
const Pun::Colors GameBoard::at( const unsigned char x, const unsigned char y ) {
	if( x < GameBoard::sizeEdge && y < GameBoard::sizeEdge )
		return quickAt( x, y );
	else
		throw std::out_of_range( "Accessing outside of m_board range." );
}

/**
 * @brief Accesseur de plateau rapide
 * @details Retourne l'élément du plateau aux coordonnées indiquées, sans vérifications des entrées.
 * @param[in] x Coordonnée en abscisse de l'emplacement
 * @param[in] y Coordonnée en ordonnée de l'emplacement
 * @return Élément aux coordonnées indiquées
 */
const Pun::Colors GameBoard::quickAt( const unsigned char x, const unsigned char y ) {
	return m_board[ x ][ y ];
}

/**
 * @brief Définisseur de plateau
 * @details Inscrit l'élément fourni sur le plateau aux coordonnées indiquées, avec vérifications des entrées.
 * @param[in] x Coordonnée en abscisse de l'emplacement
 * @param[in] y Coordonnée en ordonnée de l'emplacement
 * @param color Élément à placer
 */
void GameBoard::set( const unsigned char x, const unsigned char y, const Pun::Colors color ) {
	if( x < GameBoard::sizeEdge && y < GameBoard::sizeEdge )
		return quickSet( x, y, color );
	else
		throw std::out_of_range( "Accessing outside of m_board range." );
}

/**
 * @brief Définisseur de plateau rapide
 * @details Inscrit l'élément fourni sur le plateau aux coordonnées indiquées, sans vérifications des entrées.
 * @param[in] x Coordonnée en abscisse de l'emplacement
 * @param[in] y Coordonnée en ordonnée de l'emplacement
 * @param color Élément à placer
 */
void GameBoard::quickSet( const unsigned char x, const unsigned char y, const Pun::Colors color ) {
	m_board[ x ][ y ] = color;
}

/*
 * Explications sur la variable emptyNeighbors:
 *
 * Cette variable stocke les cases qui sont à côté d'une case sur lequel un pion se trouve, mais quis sont elles-mêmes vides.
 * Cette liste nous permet de ne pas reparcourir le tableau en entier/éviter de calculer pour chaque case si elle est vide et adjacente à un pion, pour accélérer les calculs.
 *
 * Cette liste est stockée dans un entier non-signé de 64bit. Le plateau comporte 8*8=64 cases, chaque bit de cet entier correspond à une case du plateau.
 * -> 0 ce n'est pas un "voisin vide"
 * -> 1 c'est un voisin "vide"
 *
 * On sépare cet entier en 8 sections de 8 bits, chaque section de 8 bits correspond à une coordonnées en x (0->7) et chaque bit de chaque section à une coordonnée en y (0->7).
 * Ainsi, est assigné à chaque chaque couple (x,y) un même bit unique de l'entier.
 * L'index se calcule à partir des coordonnées x et y par ( x * 8 + y ).
 *
 * Cette bizarrerie s'explique par les raisons suivantes:
 * - Je ne voulais pas memêbetr à faire une fonction de comparaison qui fonctionne pour un couple (x,y) afin d'utiliser un set
 * - Je ne voulais pas utiliser un set tout court, car on n'a pas besoin du trie, juste de l'unicité, et le set est beaucoup trop lourd pour juste cette tâche.
 * - Sur l'entier, il est simple d'assigner à chaque couple (x,y) un bit unique -> pas de duplication, on peut écrire et réécrire sans se soucier du reste
 * - L'entier est simple à accéder, copier et maintenir en mémoire, surtout sur un processeur 64bit:
 * -> l'entier tient sur un seul registre de 64 bits
 * -> pas besoin de reconsulter la mémoire pour accéder aux autres cases
 * -> la copie se fait en un nombre minimale de cylces horloges
 * -> lors dun traitement sur plusieurs cases, il y a plus de probabilités que cet entier reste dans le cache du processeur pour une utilisation immédiate ou ultérieure
 */

/**
 * @brief Accesseur de voisins vides rapide
 * @details Retourne si la case à l'index indiquée est un voisin vide
 * @param[in] index Index de la case désirée ( x * 8 + y )
 * @return État de la case
 */
bool GameBoard::quickEmptyNeighborsGet( const unsigned char index ) {
	return ( ( m_emptyNeighbors & ( ( (uint64_t) 1 ) << index ) ) != 0 );
}

/**
 * @brief Définisseur de voisins vides rapide
 * @details Définie la case indiquée comme voisin vide
 * @param[in] x Coordonnée en abscisse de l'emplacement
 * @param[in] y Coordonnée en ordonnée de l'emplacement
 */
void GameBoard::quickEmptyNeighborsSet( const unsigned char x, const unsigned char y ) {
	m_emptyNeighbors |= ( ( (uint64_t) 1 ) << ( x * 8 + y ) );
}

/**
 * @brief Réinitialisateur de voisins vides rapide
 * @details Définie la case indiquée comme n'étant pas un voisin vide
 * @param[in] x Coordonnée en abscisse de l'emplacement
 * @param[in] y Coordonnée en ordonnée de l'emplacement
 */
void GameBoard::quickEmptyNeighborsUnset( const unsigned char x, const unsigned char y ) {
	m_emptyNeighbors &= ~( ( (uint64_t) 1 ) << ( x * 8 + y ) );
}

/**
 * @brief Calculateur de coups valides
 * @details Calcule, pour une couleur de pion donnée, les coups qui peuvent être joués, en accord avec les règles du jeu, en l'état actuel du plateau.
 * @param[in] color Couleur de pion qui doit jouer
 */
void GameBoard::computeValidMoves( Pun::Colors color ) {
	bool value;
	m_validMoves.clear();

	// On parcours la liste des voisins vides, qui contient la liste de tous les emplacements vides voisins d'un pion
	for( unsigned char i = 0; i < GameBoard::size; i++ ) {
		value = quickEmptyNeighborsGet( i );
		if( value ) {
			Move emptyNeighbor( (unsigned char) ( i / 8 ), (unsigned char) ( i % 8 ), color );
			// On teste si un pion de la couleur demandé existe dans toutes les directions (à optimiser ?)
			ValidMove validMove = ValidMove( emptyNeighbor );
			for( const DirectionVector &dvec : DirectionVector::directions ) {
				if( isValidDirection( emptyNeighbor, dvec, color ) )
					// Si la direction comporte un pion de la couleur demandée, alors elle est valide et on l'ajoute
					validMove.addDirection( dvec );
			}
			// Si on a au moins une direction correct, on a un mouvement valide, on l'ajoute
			if( validMove.directions.size() > 0 )
				m_validMoves.push_back( validMove );
		}
	}
}

/**
 * @brief Calculateur de validité de direction
 * @details Indique si, pour une case de coordonnées données, pour une couleur de pion donnée, si une direction donnée comporte des pions adverses qui peuvent être retournée si le pion de couleur donnée est joué aux coordonnées données.
 * @param[in] position Position du pion
 * @param[in] dvec Direction à considérer
 * @param[in] color Couleur de pion à jouer
 * @return Validité de la direction
 */
bool GameBoard::isValidDirection( Move position, DirectionVector dvec, Pun::Colors color ) {
	try {
		unsigned char x = position.x, y = position.y;
		Pun::Colors opposite = Pun::opposite( color );
		// On regarde la case à la position + 1 (après déplacement)
		x += dvec.x;
		y += dvec.y;
		Pun::Colors next = at( x, y );
		// Si elle n'est pas de la couleur opposée, on s'arrête et on la déclare comme invalide directement (on a soit un pion "ami", soit un trou).
		if( next != opposite )
			return false;
		// Sinon, on continue l'exploration dans le sens de dvec, jusqu'à tomber sur un pion de la couleur opposée.
		// La vérification du .at() nous extrait d'ici si on arrive en dehors du plateau sans tomber sur un pion correct.
		do {
			x += dvec.x;
			y += dvec.y;
			next = at( x, y );
		} while( next == opposite );
		if( next == color )
			return true;
	} catch( std::out_of_range e ) {
		// On est en dehors du plateau, on n'a donc pas trouvé de pion de la couleur demandé sur la direction demandée
	}
	return false;
}

/**
 * @brief Actuateur de coup
 * @details Effectue le coup désiré, en vérifiant qu'il est valide.
 * @param[in] move Coup à jouer
 */
void GameBoard::play( Move move ) {
	// On parcours la liste des coups valides
	for( ValidMove &validMove: m_validMoves ) {
		// Si le coup désiré correspond à un coup valide
		if( move == validMove ) {
			// On insert la nouvelle pièce
			quickSet( move.x, move.y, move.color );
			// On retourne toutes les pièces dans les directions concernées
			for( DirectionVector& direction : validMove.directions ) {
				turnOverPuns( move, direction );
			}
			// On supprime la position actuelle des emplacements vides et on rajoute ses voisins vides
			quickEmptyNeighborsUnset( move.x, move.y );
			addEmptyNeighbors( move );
			return;
		}
	}

	// Mauvais coup
	throw exceptions::invalid_move( "Not a valid move." );
}

/**
 * @brief Actuateur de retournement de pièces
 * @details Retourne tous les pions adverses à partir dune position donnée, dans uen direction donnée, jusqu'à rencontrer un pion ami.
 * @param[in] position Position de démarrage
 * @param[in] dvec Direction de retournement
 */
void GameBoard::turnOverPuns( Move position, DirectionVector dvec ) {
	try {
		// On part de la position + 1 (après uin déplacement dans le sens de dvec), tant qu'on ne retombe pas sur la couleur initiale/ami, on "bascule" la pièce et on passe à la position suivante.
		for( unsigned char x = position.x + dvec.x, y = position.y + dvec.y; at( x, y ) != position.color; x += dvec.x, y += dvec.y )
			quickSet( x, y, position.color );
	} catch( std::out_of_range e ) {
		// On est en dehors du plateau, gros problème ! Cela ne devrait pas être le cas si le coup est valide.
	}
}

/**
 * @brief Ajouteur de voisins vides
 * @details Ajoute les voisins vides d'une case donnée.
 * @param[in] position Position de la case
 */
void GameBoard::addEmptyNeighbors( Move position ) {
	addEmptyNeighbors( position.x, position.y );
}

/**
 * @brief Ajouteur de voisins vides
 * @details Ajoute les voisins vides d'une case donnée.
 * @param[in] posx Coordonnée en abscisse de l'emplacement
 * @param[in] posy Coordonnée en ordonnée de l'emplacement
 */
void GameBoard::addEmptyNeighbors( unsigned char posx, unsigned char posy ) {
	// On parcours chaque case annexe
	for( unsigned char x = (unsigned char) ( posx - 1 ); x <= posx + 1; x++ ) {
		for( unsigned char y = (unsigned char) ( posy - 1 ); y <= posy + 1; y++ ) {
			try {
				// Si elle est vide, on l'ajoute aux voisins vides
				if( at( x, y ) == Pun::blank )
					quickEmptyNeighborsSet( (unsigned char) x, (unsigned char) y );
			} catch( std::out_of_range e ) {
				// On est en dehors du plateau, rien de grave, ça peut arriver.
			}
		}
	}
}
