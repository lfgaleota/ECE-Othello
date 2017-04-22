#ifndef _ECE_OTHELLO_SAVE_SAVEMANAGER_HPP_
	#define _ECE_OTHELLO_SAVE_SAVEMANAGER_HPP_

	#include <iostream>
	#include "save.hpp"

	/// \class SaveManager SaveManager.h
	class SaveManager {
		private :

			Save m_firstSlot;
			Save m_secondSlot;
			Save m_thirdSlot;

		public :

			/// \fn Destructor
			~SaveManager();

			/// \fn save
			void save( Othello::Board::GameBoard gameBoard_toSave, Othello::Players::Human player_toSave, int slot );

	};

#endif
