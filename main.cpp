/// \author { Louis-Félix Galeota, Romain Brisse }
/// \date 24 Avril 2017

#include "othello/inc/ui/main/maincliui.hpp"
#include "othello/inc/board/pun.hpp"
#include "othello/inc/board/gameboard.hpp"
#include "othello/inc/game.hpp"
#include "othello/inc/players/human.hpp"
#include "othello/inc/players/enhancedai.hpp"
#include "othello/inc/players/randomai.hpp"

using namespace std;
using namespace Othello;
using namespace Othello::Board;
using namespace Othello::Players;

#include <allegro.h>

#ifdef ALLEGRO_WINDOWS
#include <winalleg.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <alleggl.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_agl.h"

void InitAllegro() {
	// Initialize Allegro:
	allegro_init();

	// Install AllegroGL:
	install_allegro_gl();

	// Install the mouse:
	install_mouse();

	// Install the keyboard:
	install_keyboard();

	// Install the timer:
	install_timer();
}

void InitGL() {
	// Set the color depth to 32 bits-per-pixel:
	allegro_gl_set( AGL_COLOR_DEPTH, 32 );
	allegro_gl_set( AGL_Z_DEPTH, 8 );
	allegro_gl_set( AGL_SUGGEST, AGL_COLOR_DEPTH | AGL_Z_DEPTH );

	// Create an 800x600 fullscreen window:
	if( set_gfx_mode(GFX_OPENGL_WINDOWED, 1280, 720, 0, 0 )) {
		// Error creating window:
		allegro_message( "There was an error creating the window" );
		exit( 1 );
	}

	// Set cursor as hardware pointer:
	enable_hardware_cursor();
	select_mouse_cursor( 2 );
	show_mouse( screen );

	// Set the OpenGL viewport:
	glViewport( 0, 0, SCREEN_W, SCREEN_H);

	// We need to set the projection transformation matrix,
	// so switch to the projection matrix:
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	// Define the projection transformation matrix.  Notice
	// that this is using glFrustum instead of gluPerspective:
	// In order to use this we need to calculate the min and
	// max x/y range so as to maintain proper aspect ratio:
	float fMinX = -1.0f, fMaxX = 1.0f,
			fMinY = -1.0f, fMaxY = 1.0f;
	float fAspectRatio = SCREEN_W / (float) SCREEN_H;
	if( fAspectRatio > 1.0f ) {
		// The height is greater than the width, so we need to
		// recalculate the x-range:
		fMinY = fMinX / fAspectRatio;
		fMaxY = fMaxX / fAspectRatio;
	} else {
		// The width is greater than the height, so we need to
		// re-calculate the y-range:
		fMinX = fMinY * fAspectRatio;
		fMaxX = fMaxY * fAspectRatio;
	}
	glFrustum( fMinX, fMaxX, fMinY, fMaxY, 1.5f, 20.0f );
	//gluPerspective( 50, SCREEN_W/SCREEN_H, 0.01f, 100.0f);

	// Switch back to the modelview matrix:
	glMatrixMode( GL_MODELVIEW );

	glEnable( GL_TEXTURE_2D );                        // Enable Texture Mapping ( NEW )
	glShadeModel( GL_SMOOTH );                        // Enable Smooth Shading
	glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );                   // Black Background
	glClearDepth( 1.0f );                         // Depth Buffer Setup
	glEnable( GL_DEPTH_TEST );                        // Enables Depth Testing
	glDepthFunc( GL_LEQUAL );                         // The Type Of Depth Testing To Do
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );          // Really Nice Perspective Calculations
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );    // Really Nice Perspective Calculations

}

int main() {
	/*InitAllegro();
	InitGL();
	ImGui_ImplAGL_Init();

	std::vector<Player*> players;
	players.push_back( new Human( "Player1", Pun::black ) );
	players.push_back( new EnhancedAI( "Player2", Pun::white ) );

	Game othello( players );

	ImGui_ImplAGL_Shutdown();
	allegro_exit();*/

	Othello::UI::Main::CLI();

	return 0;
}

END_OF_MAIN();