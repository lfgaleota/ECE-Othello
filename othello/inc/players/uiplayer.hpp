#ifndef _ECE_OTHELLO_PLAYER_UIPLAYER_HPP_
	#define _ECE_OTHELLO_PLAYER_UIPLAYER_HPP_

	#include "player.hpp"
	#include "../ui/games/gameui.hpp"

	namespace Othello {
		namespace Players {
		    /// \class UIPlayer uiplayer.hpp
			class UIPlayer : public Player {
				protected:
					Othello::UI::Game* m_ui;

				public:
					UIPlayer( std::string name, Othello::Board::Pun::Colors color );

					void setUI( Othello::UI::Game *m_ui );
			};
		}
	}

#endif
