#ifndef _ECE_OTHELLO_EXCEPTIONS_HPP_
	#define _ECE_OTHELLO_EXCEPTIONS_HPP_

	#include <stdexcept>
	#include <string>

	/**
	 * @namespace Othello
	 * @details Espace de nommage du jeu.
	 */
	namespace Othello {
	    /**
	     * @namespace exceptions
	     * @details Espace de nommage des exceptions personnalisées du jeu.
	     */
		namespace exceptions {
			#include "invalid_move"
			#include "exit_game"
			#include "no_selected_move"
			#include "invalid_save"
		}
	}
#endif
