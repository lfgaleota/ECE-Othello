#ifndef _ECE_SIAM_UI_MAIN_ALLEGRO_HPP_
	#define _ECE_SIAM_UI_MAIN_ALLEGRO_HPP_

	#include <allegro.h>

	#ifdef ALLEGRO_WINDOWS
	#include <winalleg.h>
	#endif

	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <alleggl.h>

	#include "../../../../imgui/imgui.h"
	#include "../../../../imgui/imgui_impl_agl.h"
	#include <jpgalleg.h>
	#include <loadpng.h>
	#include <vector>
	#include <ios>
	#include <fstream>
	#include <sstream>
	#include <stdlib.h>
	#include "../../game.hpp"
	#include "../../players/human.hpp"
	#include "../../players/randomai.hpp"
	#include "../../players/simpleai.hpp"
	#include "../../players/enhancedai.hpp"
	#include "../audio/FMOD.hpp"

	#ifdef ALLEGRO_WINDOWS
		#define COMPUTE_DT( dt ) dt = (float) ( clock() - before ) / 30;
	#else
		#define COMPUTE_DT( dt ) dt = (float) ( clock() - before ) / 3000;
	#endif

	#define NAME_SIZE 32
	#define MODAL_BUTTON_WIDTH 300
	#define MODAL_BUTTON_HEIGHT 40
	#define NEWPLAYER_HEIGHT 160
	#define NEWPLAYER_BOTTOM_MARGIN 20
	#define OPTIONS_WIN_MARGIN 20
	#define OPTIONS_HEIGHT SCREEN_H - OPTIONS_WIN_MARGIN
	#define QUIT_HEIGHT 140
	#define NEWAI_HEIGHT 160

	#define ERROR_WIDTH 300
	#define ERROR_HEIGHT 100

	namespace Othello {
		namespace UI {
			namespace Main {
				float EaseOutQuad( float t, float maxt );
				bool AGL_loadTexture( GLuint& texture, std::string path );
				void GL_windowToObjectf( GLfloat x, GLfloat y, GLdouble* retx, GLdouble* rety, GLdouble* retz );

				class AnimatedRectangle {
					protected:
						float t = 0;
						float& dt;
						GLuint texture;
						bool show = false, hoverIn = false, hoverOut = true, doAnimateEntry = false, doAnimateHoverIn = false, doAnimateHoverOut = false, sound = false;
						constexpr static float defaultEntryRY = -60.0f, defaultEntryTime = 15.0f, defaultNormalX = 1.0f, defaultHoverX = 1.0f, defaultHoverZ = 0.5f, defaultHoverTime = 10.0f, defaultClickZ = -defaultHoverZ;
						float entryRY = defaultEntryRY, entryTime = defaultEntryTime, normalX = defaultNormalX, hoverX = defaultHoverX, hoverZ = defaultHoverZ, hoverTime = defaultHoverTime, clickZ = defaultClickZ;
						Othello::UI::Audio::FMOD& m_fmod;

					public:
						bool clicked = false;

						AnimatedRectangle( float& dt, Othello::UI::Audio::FMOD& fmod );

						bool loadTexture( std::string path );

						virtual void playHover();

						virtual void drawOutline();
						virtual void drawReal();

						void draw();

						void animateEntry();
						void animateHoverIn();
						void animateHoverOut();

						void entry();

						void reset();
				};

				class MenuRectangle : public AnimatedRectangle {
					private:
						GLuint backTexture;

					public:
						MenuRectangle( float& dt, Othello::UI::Audio::FMOD& fmod );

						bool loadBackTexture( std::string path );

						void playHover();

						void drawOutline();
						void drawReal();
				};

				class ButtonRectangle : public AnimatedRectangle {
					public:
						ButtonRectangle( float& dt, Othello::UI::Audio::FMOD& fmod );

						void playHover();

						void drawOutline();
						void drawReal();
				};

				class Allegro {
					private:
						BITMAP* m_page;
						FONT* m_textFont;
						std::unordered_map<std::string, BITMAP*> m_bitmaps;
						bool keyEsc = false, prevKeyEsc = false, quit = false;
						int choice;
						std::vector<Othello::Players::Player*> m_players;
						float t = 0, dt = 0;
						time_t before;
						GLdouble inx, iny, inz;
						Othello::UI::Audio::FMOD& m_fmod;
						AnimatedRectangle rectPVP, rectPVAI, rectPVPNet, rectAI1, rectAI2, rectAI3;
						MenuRectangle rectContinue, rectNew, rectOptions, rectQuit;
						ButtonRectangle rectCancel;
						char player1name[ NAME_SIZE ] = { 0 }, player2name[ NAME_SIZE ] = { 0 };
						unsigned char ai_level = 0;
						bool isSave = false;

						enum Stage {
							Menu,
							Options,
							Quit,
							ContinueParty,
							New,
							NewPlayer,
							NewPlayerParty,
							NewAISelect,
							NewAI,
							NewAIParty
						};

						Stage stage = Stage::Menu;

						void initAllegro();
						void initGL();
						void loadSprites();
						void loadFonts();
						void loadIMGUIStyle();
						void loadBackgrounds();
						void loadRectangles();

						void updateInputs();
						void handleMouse();
						void renderScene();
						void renderMenu();
						void renderOptions();
						void renderQuit();
						void renderNew();
						void renderNewPlayer();
						void renderNewAISelect();
						void renderNewAI();
						void renderModalShadow();
						void renderCancelButton();
						void newFrame();
						void endFrame();
						void display();
						void menu();
						void back();
						void forward( Stage newStage );

						void redirectGame();
						void loadGame();
						void newPlayerGame();
						void newAIGame();

						void error( std::string message );

						void forceMenu();

						void freeBitmaps();
					public:
						Allegro( Othello::UI::Audio::FMOD& fmod );
				};
			}
		}
	}

#endif
