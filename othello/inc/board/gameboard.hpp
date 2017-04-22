#ifndef _ECE_OTHELLO_BOARD_GAMEBOARD_HPP_
	#define _ECE_OTHELLO_BOARD_GAMEBOARD_HPP_

	#include <iostream>
	#include <string>
	#include <vector>
	#include <set>
	#include <cstring>
	#include "pun.hpp"
	#include "move.hpp"
	#include "valid_move.hpp"
	#include "../exceptions/exceptions.hpp"
	#include "gameissue.hpp"
	#include "gameboardconstants.hpp"
	#include "../save/save.hpp"

	/// \namespace Othello
	namespace Othello {
	    /// \namespace Algorithms
		namespace Algorithms {
			class MiniMax;
			class AlphaBeta;
			class Heuristics;
		}

		namespace Players {
			class SimpleAI;
		}

        /// \namespace Board
		namespace Board {
		    /// \namespace Tree
			namespace Tree {
				class ValidMoveNode;
			}

			/// \class GameBoard gameboard.hpp
			class GameBoard {
				friend class Othello::Board::Tree::ValidMoveNode;
				friend class Othello::Algorithms::MiniMax;
				friend class Othello::Algorithms::AlphaBeta;
				friend class Othello::Algorithms::Heuristics;
				friend class Othello::Players::SimpleAI;

				private:
					Pun::Colors m_board[ sizeEdge ][ sizeEdge ];
					std::list<ValidMove> m_validMoves;
					uint64_t m_emptyNeighbors = 0;

					PunCount m_count;

					/// \fn turnOverPuns
					/// \param {position, dvec, count, oppositeCount}
					void turnOverPuns( Move position, DirectionVector dvec, unsigned char& count, unsigned char& oppositeCount );

					/// \fn isValidDirection
					/// \param {position, dvec, color}
					bool isValidDirection( Move position, DirectionVector dvec, Pun::Colors color );

					/// \fn addEmptyNeighbors
					/// \param {position}
					inline void addEmptyNeighbors( Move position );

					/// \fn addEmptyNeighborsBis
					/// \param {x, y}
					inline void addEmptyNeighbors( unsigned char x, unsigned char y );

					/**
					 * @brief Accesseur de plateau rapide
					 * @details Retourne l'élément du plateau aux coordonnées indiquées, sans vérifications des entrées.
					 * @param[in] x Coordonnée en abscisse de l'emplacement
					 * @param[in] y Coordonnée en ordonnée de l'emplacement
					 * @return Élément aux coordonnées indiquées
					 */
					inline const Pun::Colors quickAt( const unsigned char x, const unsigned char y ) const {
						return m_board[ x ][ y ];
					}

					/// \fn quickSet
					/// \param {x, y, color}
					inline void quickSet( const unsigned char x, const unsigned char y, const Pun::Colors color );

					/**
					 * @brief Accesseur de voisins vides rapide
					 * @details Retourne si la case à l'index indiquée est un voisin vide
					 * @param[in] index Index de la case désirée ( x * 8 + y )
					 * @return État de la case
					 */
					inline bool quickEmptyNeighborsGet( const unsigned char index ) const {
						return ( ( m_emptyNeighbors & ( ( (uint64_t) 1 ) << index ) ) != 0 );
					}

					/// \fn quickEmptyNeighborsSet
					/// \param {x, y}
					inline void quickEmptyNeighborsSet( const unsigned char x, const unsigned char y );

					/// \fn quickEmptyNeighborsUnset
					/// \param {x, y}
					inline void quickEmptyNeighborsUnset( const unsigned char x, const unsigned char y );

					/// \fn quickPlay
					/// \param {validMove}
					void quickPlay( ValidMove validMove );

				public:

					/// \fn accesseur de emptyNeighbors
					/// \param {no parameters}
				    uint64_t getEmptyNeighbors();

					/// \fn GameBoardDefaultConstructor
					/// \param {no parameters}
					GameBoard();
					/// \fn GameBoardCopyConstructor
					/// \param {ref}
					GameBoard( GameBoard& ref );
					GameBoard( GameBoard* ref );
					/// \fn GameBoardCopyConstructor
					/// \param {ref}
					GameBoard( Othello::Save::Save& save );
					/// \fn GameBoardDestructor
					/// \param {no parameters}
					~GameBoard();

					/// \fn getBoard
					/// \param {no parameters}
					const punArray getBoard();

					/// \fn getValidMovesReference
					/// \param {no parameters}
					const std::list<ValidMove> &getValidMoves();

					/// \fn computeValidMoves
					/// \param {color}
					void computeValidMoves( Pun::Colors color );

					/// \fn canPlay
					/// \param {no parameters}
					bool canPlay();
					/// \fn play
					/// \param {move}
					void play( Move move );

					/// \fn at
					/// \param {x, y}
					const Pun::Colors at( const unsigned char x, const unsigned char y ) const;

					/// \fn set
					/// \param {x, y color}
					void set( const unsigned char x, const unsigned char y, const Pun::Colors color );

					/// \fn punCount
					/// \param {color}
					const unsigned char punCount( Pun::Colors color ) const;

					/// \fn issue
					/// \param {color}
					const GameIssue issue( Pun::Colors color ) const;
			};
		}
	}

#endif
