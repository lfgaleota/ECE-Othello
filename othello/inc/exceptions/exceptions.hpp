#ifndef _ECE_OTHELLO_EXCEPTIONS_HPP_
	#define _ECE_OTHELLO_EXCEPTIONS_HPP_

	#include <stdexcept>
	#include <string>

	/// \namespace Othello
	namespace Othello {
	    /// \namespace Exceptions
		namespace exceptions { //exeptions inclusions
			#include "invalid_move"
			#include "exit_game"
		}
	}
#endif
