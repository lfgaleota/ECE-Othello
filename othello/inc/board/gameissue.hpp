#ifndef _ECE_OTHELLO_BOARD_GAMEISSUE_HPP_
	#define _ECE_OTHELLO_BOARD_GAMEISSUE_HPP_

	/// \namespace Othello
	namespace Othello {
	    /// \namespace Board
		namespace Board {
		    /// \enum  GameIssue
			enum GameIssue {
				Nothing,
				Victory,
				Defeat,
				Draw
			};
		}
	}

#endif
