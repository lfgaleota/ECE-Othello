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
	#include "../audio/FMOD.hpp"

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

				/// \class ErrorPage
				class ErrorPage;

                /// \class MessageBar
                /// \brief classe gérant le barre des messages avec allegro
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

						/// \fn draw
                        /// \param {no Parameters}
						virtual void draw();

					public:
					    /// \fn default constructor
                        /// \param {no Parameters}
						MessageBar();
						/// \fn overload Constructor
                        /// \param {page, font}
						MessageBar( BITMAP* page, FONT* font );

                        /// \fn render
                        /// \param {dt}
						virtual void render( float dt );

                        /// \fn animateIn
                        /// \param {message, force}
						virtual void animateIn( std::string msg, bool force = false );
						/// \fn animateOut
                        /// \param {no Parameters}
						void animateOut();
				};

				/// \class ErrorBar
				/// \brief classe gérant la barre d'erreur avec allegro
				class ErrorBar : public MessageBar {
					private:
						MessageBar* infoBar;

						constexpr static time_t stayTime = CLOCKS_PER_SEC * 4;
						time_t before, next;
						int diff;
						int colorBarFront = makecol( 255, 255, 255 ), colorBarBack = makecol( 190, 0, 0 ), colorIconFront = makecol( 255, 255, 255 ), colorIconBack = makecol( 100, 0, 0 ), colorBarBackNoTime = makecol( 170, 0, 0 );

						/// \fn draw
                        /// \param {no Parameters}
						void draw();

					public:
					    /// \fn default constructor
                        /// \param {no Parameters}
						ErrorBar();
						/// \fn overload constructor
                        /// \param {page, font, infoBar}
						ErrorBar( BITMAP* page, FONT* font, MessageBar* infoBar );

						/// \fn animateIn
                        /// \param {msg, force}
						void animateIn( std::string msg, bool force = false );
						/// \fn render
                        /// \param {dt}
						void render( float dt );
				};

				/// \class Allegro
				/// \brief classe gérant allegro
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
						Othello::UI::Audio::FMOD& m_fmod;

                        /// \fn loadSprites
                        /// \param {no Parameters}
						void loadSprites();
						/// \fn loadFonts
                        /// \param {no Parameters}
						void loadFonts();
						/// \fn loadBackgrounds
                        /// \param {no Parameters}
						void loadBackgrounds();
						/// \fn loadIMGUIStyle
                        /// \param {no Parameters}
						void loadIMGUIStyle();

                        /// \fn display
                        /// \param {no Parameters}
						void display();
						/// \fn displayBackground
                        /// \param {no Parameters}
						void displayBackground();
						/// \fn displayMatrix
                        /// \param {no Parameters}
						void displayMatrix();
						/// \fn displayPlayers
                        /// \param {no Parameters}
						void displayPlayers();
						/// \fn highlightSelectedPiece
                        /// \param {x,y,color}
						void highlightSelectedPiece( unsigned int x, unsigned int y, int color = COLOR_SELECTION );

						/// \fn updateInputs
                        /// \param {no Parameters}
						void updateInputs();
						/// \fn renderPause
                        /// \param {no Parameters}
						void renderPause();

						/// \fn freeBitmaps
                        /// \param {no Parameters}
						void freeBitmaps();

						/// \fn getPunSprite
                        /// \param {color}
						BITMAP* getPunSprite( Othello::Board::Pun::Colors color ) const;

						/// \fn newFrame
                        /// \param {skipDT}
						void newFrame( bool skipDT = false );
						/// \fn endFrame
                        /// \param {no Parameters}
						void endFrame();
						/// \fn gameDisplay
                        /// \param {no Parameters}
						void gameDisplay();

					public:
						/// \fn overload constructor
                        /// \param {oboard,board,players,currentPlayer}
						Allegro( Othello::Board::GameBoard& oboard, const Othello::Board::punArray board, const std::vector<Othello::Players::Player*>& players, std::vector<Othello::Players::Player*>::iterator& currentPlayer, Othello::UI::Audio::FMOD& fmod );
						/// \fn destructor
                        /// \param {no Parameters}
						~Allegro();

                        /// \fn showError
                        /// \param {msg}
						void showError( std::string msg );
						/// \fn playerTurnBegin
                        /// \param {player}
						void playerTurnBegin( Othello::Players::Player* player );
						/// \fn playerTurnEnd
                        /// \param {player}
						void playerTurnEnd( Othello::Players::Player* player );
						/// \fn victory
                        /// \param {player}
						void victory( Othello::Players::Player* player );

						/// \fn getmove accesseur en lecture du mouvement
                        /// \param {no parameters}
						Othello::Board::Move getMove();
						/// \fn inform
                        /// \param {msg}
						void inform( std::string msg );
						/// \fn informNoAvailableMoves
                        /// \param {player}
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
