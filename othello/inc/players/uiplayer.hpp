#ifndef _ECE_OTHELLO_PLAYER_UIPLAYER_HPP_
	#define _ECE_OTHELLO_PLAYER_UIPLAYER_HPP_

	#include "player.hpp"
	#include "../ui/games/gameui.hpp"

	/// \namespace Othello
	namespace Othello {
	    /// \namespace Players
		namespace Players {
		    /// \class UIPlayer uiplayer.hpp
			class UIPlayer : public Player {
				protected:
					Othello::UI::Game* m_ui;

				public:
					/// \fn UIPlayerOverloadConstructor
					UIPlayer( std::string name, Othello::Board::Pun::Colors color );

					/// \fn setUISetter
					void setUI( Othello::UI::Game *m_ui );
			};
		}
	}

#endif
