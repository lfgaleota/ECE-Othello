#ifndef _ECE_OTHELLO_BOARD_PUN_HPP_
	#define _ECE_OTHELLO_BOARD_PUN_HPP_

	namespace Othello {
		namespace Board {

			/// \struct Pun
			struct Pun {
			    /// \enum Colors
				enum Colors {
					blank = 0,
					black = 1,
					white = 2
				};

				static inline Colors opposite( Colors color ) {
					return (Colors) ((int) Colors::white - (int) color + (int) Colors::black );
				}
			};
		}
	}

#endif
