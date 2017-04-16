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

	namespace Othello {
		namespace Board {
			namespace Tree {
				class ValidMoveNode;
			}

			class GameBoard {
				friend class Othello::Board::Tree::ValidMoveNode;

				public:
					const static unsigned char sizeEdge = 8;
					const static unsigned char size = sizeEdge * sizeEdge;
					const static size_t sizeMemory = (size_t) ( GameBoard::size * 4 );

					typedef Pun::Colors (*punArray)[GameBoard::sizeEdge];

				private:

					Pun::Colors m_board[sizeEdge][sizeEdge];
					std::list<ValidMove> m_validMoves;
					uint64_t m_emptyNeighbors = 0;

					void turnOverPuns( Move position, DirectionVector dvec );

					bool isValidDirection( Move position, DirectionVector dvec, Pun::Colors color );

					inline void addEmptyNeighbors( Move position );

					inline void addEmptyNeighbors( unsigned char x, unsigned char y );

					inline const Pun::Colors quickAt( const unsigned char x, const unsigned char y );

					inline void quickSet( const unsigned char x, const unsigned char y, const Pun::Colors color );

					inline bool quickEmptyNeighborsGet( const unsigned char index );

					inline void quickEmptyNeighborsSet( const unsigned char x, const unsigned char y );

					inline void quickEmptyNeighborsUnset( const unsigned char x, const unsigned char y );

					void quickPlay( ValidMove validMove );

				public:
					GameBoard();
					GameBoard( GameBoard& ref );
					~GameBoard();

					const punArray getBoard();

					const std::list<ValidMove> &getValidMoves();

					void computeValidMoves( Pun::Colors color );

					void play( Move move );

					const Pun::Colors at( const unsigned char x, const unsigned char y );

					void set( const unsigned char x, const unsigned char y, const Pun::Colors color );
			};
		}
	}

#endif
