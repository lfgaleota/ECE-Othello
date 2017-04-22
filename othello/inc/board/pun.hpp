#ifndef _ECE_OTHELLO_BOARD_PUN_HPP_
	#define _ECE_OTHELLO_BOARD_PUN_HPP_

	/// \namespace Othello
	namespace Othello {
		/// \namespace Board
		namespace Board {
			/// \struct PunCount
			struct PunCount {
				unsigned char white = 0;
				unsigned char black = 0;
			};

			/// \struct Pun
			struct Pun {
				/// \enum Colors
				enum Colors {
					blank = 0,
					black = 1,
					white = 2
				};

				/// \fn opposite
				/// \param {color}
				static inline Colors opposite( Colors color ) {
					return ( Colors ) ( ( int ) white - ( int ) color + ( int ) black );
				}

				static bool check( int v );
			};
		}
	}

#endif
