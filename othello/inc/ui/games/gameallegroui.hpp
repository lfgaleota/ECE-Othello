#ifndef ECE_OTHELLO_UI_GAMES_ALLEGRO_HPP
	#define ECE_OTHELLO_UI_GAMES_ALLEGRO_HPP

	#include <allegro.h>
	#ifdef ALLEGRO_WINDOWS
		#include <winalleg.h>
	#endif
	#include <loadpng.h>
	#include <jpgalleg.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <alleggl.h>
	#include <unordered_map>
	#include "../../../../imgui/imgui.h"
	#include "../../../../imgui/imgui_impl_agl.h"
	#include "gameui.hpp"
	#include "../../exceptions/exceptions.hpp"
	#include "allegrovalidmovetreeviewer.hpp"

	#define PLAYER_NAME_PADDING_W 10
	#define PLAYER_NAME_PADDING_H 2
	#define PLAYER_SCORE_WIDTH_X 30
	#define COLOR_ACTIVE_PLAYER makecol( 27, 144, 170 )
	#define COLOR_INACTIVE_PLAYER makecol( 3, 21, 25 )
	#define COLOR_SELECTION makecol( 255, 0, 0 )
	#define COLOR_SELECTION_BLENDFACTOR 80
	#define COLOR_VALIDMOVE makecol( 255, 255, 0 )
	#define COLOR_VALIDMOVE_BLENDFACTOR 100
	#define VICTORY_PADDING 50
	#define FONT_SIZE_16 0
	#define FONT_SIZE_32 1
	#define PAUSE_HEIGHT 180
	#define PAUSE_BUTTON_WIDTH 300
	#define PAUSE_BUTTON_HEIGHT 40
	#define PAUSE_BLENDING_FACTOR 130

	#ifdef ALLEGRO_WINDOWS
		#define COMPUTE_DT( dt ) dt = (float) ( clock() - before ) / 30;
	#else
		#define COMPUTE_DT( dt ) dt = (float) ( clock() - before ) / 3000;
	#endif

	/**
	 * @namespace Othello
	 * @details Espace de nommage du jeu.
	 */
	namespace Othello {
		/**
		 * @namespace UI
		 * @details Espace de nommage des interfaces du jeu.
		 */
		namespace UI {
			/**
			 * @namespace Games
			 * @details Espace de nommage des interfaces de jeu du jeu.
			 */
			namespace Games {
				float EaseOutQuad( float t, float maxt );

				class ErrorPage;

				class MessageBar {
					friend class ErrorBar;

					protected:
						float t = 0;
						bool in = false, doAnimateIn = false, doAnimateOut = false, shouldAnimateIn = false;
						int xIcon, xBar, y;
						BITMAP* page;
						FONT* font;
						std::string message;

						constexpr static int widthIcon = 20, outXIcon = -16, inX = 0, height = 22, marginX = 4, marginY = 2, marginXIcon = 8, marginYIcon = 2;
						int colorBarFront = makecol( 0, 0, 0 ), colorBarBack = makecol( 200, 200, 200 ), colorIconFront = colorBarBack, colorIconBack = colorBarFront, widthBar = SCREEN_W, outXBar = -SCREEN_W;
						float inTime = 15, outTime = 15;

						virtual void draw();

					public:
						MessageBar();
						MessageBar( BITMAP* page, FONT* font );

						virtual void render( float dt );

						virtual void animateIn( std::string msg, bool force = false );
						void animateOut();
				};

				class ErrorBar : public MessageBar {
					private:
						MessageBar* infoBar;

						constexpr static time_t stayTime = CLOCKS_PER_SEC * 4;
						time_t before, next;
						int diff;
						int colorBarFront = makecol( 255, 255, 255 ), colorBarBack = makecol( 190, 0, 0 ), colorIconFront = makecol( 255, 255, 255 ), colorIconBack = makecol( 100, 0, 0 ), colorBarBackNoTime = makecol( 170, 0, 0 );

						void draw();

					public:
						ErrorBar();
						ErrorBar( BITMAP* page, FONT* font, MessageBar* infoBar );

						void animateIn( std::string msg, bool force = false );
						void render( float dt );
				};

				class Allegro : public Othello::UI::Game {
					private:
						std::unordered_map<std::string, BITMAP*> m_bitmaps;
						BITMAP* m_page;
						FONT *m_textFont, *m_glTextFont;
						ImGuiIO& m_io;
						bool prevKeyEsc = false, keyEsc = false, prevKeyG = false, keyG = false;
						unsigned char x = 0, y = 0;
						float dt;
						time_t before;
						Othello::Board::GameBoard& m_oboard;
						MessageBar infoBar;
						ErrorBar errorBar;
						AllegroValidMoveTreeViewer m_treeViewer;
						bool m_pause = false, m_getMove = false;

						void loadSprites();
						void loadFonts();
						void loadBackgrounds();
						void loadIMGUIStyle();

						void display();
						void displayBackground();
						void displayMatrix();
						void displayPlayers();
						void highlightSelectedPiece( unsigned int x, unsigned int y, int color = COLOR_SELECTION );

						void updateInputs();
						void renderPause();

						void freeBitmaps();

						BITMAP* getPunSprite( Othello::Board::Pun::Colors color ) const;

						void newFrame( bool skipDT = false );
						void endFrame();
						void gameDisplay();

					public:
						Allegro( Othello::Board::GameBoard& oboard, const Othello::Board::GameBoard::punArray board, const std::vector<Othello::Players::Player*>& players, std::vector<Othello::Players::Player*>::iterator& currentPlayer );
						~Allegro();

						void showError( std::string msg );
						void playerTurnBegin( Othello::Players::Player* player );
						void playerTurnEnd( Othello::Players::Player* player );
						void victory( Othello::Players::Player* player );

						Othello::Board::Move getMove();
						void inform( std::string msg );
						void informNoAvailableMoves( Othello::Players::Player* player );

						/**
						 * @brief	Demandeur de rendue
						 * @details	Demande à l'interface de procéder à ses fonctions.
						 */
						void render();
				};
			}
		}
	}

#endif //ECE_OTHELLO_UI_GAMES_ALLEGRO_HPP
