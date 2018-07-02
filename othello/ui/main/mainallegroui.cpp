#include "../../inc/ui/main/mainallegroui.hpp"

using namespace std;
using namespace Othello;
using namespace Othello::UI::Main;

const std::string Allegro::configPath = "config";
Allegro* Othello::UI::Main::currentUI = nullptr;

const std::vector<std::pair<unsigned int, unsigned int>> Allegro::resolutions = { std::make_pair<unsigned int, unsigned int>( 800, 600 ), std::make_pair<unsigned int, unsigned int>( 1280, 720 ), std::make_pair<unsigned int, unsigned int>( 1280, 960 ), std::make_pair<unsigned int, unsigned int>( 1280, 1024 ), std::make_pair<unsigned int, unsigned int>( 1440, 900 ), std::make_pair<unsigned int, unsigned int>( 1600, 900 ), std::make_pair<unsigned int, unsigned int>( 1600, 1200 ), std::make_pair<unsigned int, unsigned int>( 1920, 1080 ), std::make_pair<unsigned int, unsigned int>( 1920, 1440 ) };
const char* Allegro::resolutionsNames[] = { "800x600", "1280x720", "1280x960", "1280x1024", "1440x900", "1600x900", "1600x1200", "1920x1080", "1920x1440" };
const char* Allegro::windowModes[] = { "Fenêtré", "Plein écran" };
const unsigned int Allegro::resolutionsNamesNumber = 9;
const unsigned int Allegro::windowModesNumber = 2;

void Othello::UI::Main::AllegroCloseHandler() {
	if( Othello::currentUI != nullptr )
		Othello::currentUI->forceQuit();
	if( Othello::UI::Main::currentUI != nullptr )
		Othello::UI::Main::currentUI->forceQuit();
} END_OF_FUNCTION( AllegroCloseHandler )

float Othello::UI::Main::EaseOutQuad( float t, float maxt ) {
	float sct = t / maxt;
	float opt = 1 - sct;
	return 1 - opt * opt;
}

bool Othello::UI::Main::AGL_loadTexture( GLuint& texture, string path ) {
	BITMAP *tex;

	tex = load_png( path.c_str(), NULL );
	if( tex ) {
		texture = allegro_gl_make_texture( tex );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		destroy_bitmap( tex );
		return true;
	}

	return false;
}

void Othello::UI::Main::GL_windowToObjectf( GLfloat x, GLfloat y, GLdouble* retx, GLdouble* rety, GLdouble* retz ) {
	GLdouble modelViewMatrix[ 16 ];
	GLdouble projectionMatrix[ 16 ];
	GLint viewport[ 4 ];
	GLfloat z;
	glGetDoublev( GL_MODELVIEW_MATRIX, modelViewMatrix );
	glGetDoublev( GL_PROJECTION_MATRIX, projectionMatrix );
	glGetIntegerv( GL_VIEWPORT, viewport );
	y = (float)viewport[ 3 ] - y;
	glReadPixels( (GLint) x, (GLint) y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z );
	auto success = gluUnProject( x, y, z, modelViewMatrix, projectionMatrix, viewport, retx, rety, retz );
	if(success != GL_TRUE)
		throw logic_error( "Assert failed" );
	if( *retx != *retx )
		*retx = 0;
	if( *rety != *rety )
		*rety = 0;
}

AnimatedRectangle::AnimatedRectangle( float& dt, Othello::UI::Audio::FMOD& fmod ) : dt( dt ), m_fmod( fmod ) {}

bool AnimatedRectangle::loadTexture( string path ) {
	return AGL_loadTexture( texture, path );
}

void AnimatedRectangle::drawOutline() {
	// Unbind texture:
	glBindTexture( GL_TEXTURE_2D, 0 );
	// Render the outlines
	glLineWidth( 8 );
	glColor3f( 1.0, 1.0, 1.0 );
	glBegin( GL_LINES );
	glVertex3f( -1.05f, -1.525f, 0.99f ); glVertex3f( 1.05f, -1.525f, 0.99f );
	glVertex3f( 1.025f, -1.55f, 0.99f ); glVertex3f( 1.025f, 1.55f, 0.99f );
	glVertex3f( 1.05f, 1.525f, 0.99f ); glVertex3f( -1.05f, 1.525f, 0.99f );
	glVertex3f( -1.025f, 1.55f, 0.99f ); glVertex3f( -1.025f, -1.55f, 0.99f );
	glEnd();
}

void AnimatedRectangle::drawReal() {
	// Bind texture:
	glBindTexture( GL_TEXTURE_2D, texture );
	// Render the square as a quad:
	glBegin( GL_QUADS );
	// Assign a different color to each vertex
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, -1.5f, 1.0f );  // Bottom Left Of The Texture and Quad
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, -1.5f, 1.0f );  // Bottom Right Of The Texture and Quad
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.5f, 1.0f );  // Top Right Of The Texture and Quad
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, 1.5f, 1.0f );  // Top Left Of The Texture and Quad
	glEnd();
}

void AnimatedRectangle::draw() {
	if( show ) {
		if( doAnimateEntry ) {
			if( t < entryTime - 0.1f ) {
				t += dt;
				glRotatef( entryRY * ( 1 - EaseOutQuad( t, entryTime )), 0.0f, 1.0f, 0.0f );
				glTranslatef( normalX * EaseOutQuad( t, entryTime ), 0.0f, 0.0f );
			} else {
				doAnimateEntry = false;
				glTranslatef( normalX, 0.0f, 0.0f );
			}
		} else if( doAnimateHoverIn ) {
			if( !sound ) {
				playHover();
				sound = true;
			}
			t += dt;
			if( t < hoverTime - 0.1f ) {
				glTranslatef( hoverX + ( normalX - hoverX ) * ( 1 - EaseOutQuad( t, hoverTime )), 0.0f,
				              hoverZ * EaseOutQuad( t, hoverTime ));
			} else {
				doAnimateHoverIn = false;
				glTranslatef( hoverX, 0.0f, hoverZ );
			}
		} else if( hoverIn ) {
			glTranslatef( hoverX, 0.0f, hoverZ );
		} else if( doAnimateHoverOut ) {
			t += dt;
			if( t < hoverTime - 0.1f ) {
				glTranslatef( hoverX + ( normalX - hoverX ) * EaseOutQuad( t, hoverTime ), 0.0f,
				              hoverZ * ( 1 - EaseOutQuad( t, hoverTime )));
			} else {
				doAnimateHoverOut = false;
				glTranslatef( normalX, 0.0f, 0.0f );
			}
		} else {
			glTranslatef( normalX, 0.0f, 0.0f );
		}

		if( hoverIn )
			drawOutline();
		if( clicked )
			glTranslatef( 0.0f, 0.0f, clickZ );
		drawReal();
	}
}

void AnimatedRectangle::animateEntry() {
	if( !show ) {
		t = 0;
		doAnimateEntry = true;
		show = true;
		sound = false;
	}
}

void AnimatedRectangle::animateHoverIn() {
	if( !doAnimateEntry && !hoverIn ) {
		t = 0;
		doAnimateHoverIn = true;
		doAnimateHoverOut = false;
		hoverOut = false;
		hoverIn = true;
		sound = false;
	}
}

void AnimatedRectangle::animateHoverOut() {
	if( !doAnimateEntry && !hoverOut ) {
		t = 0;
		doAnimateHoverIn = false;
		doAnimateHoverOut = true;
		hoverIn = false;
		hoverOut = true;
		sound = false;
	}
}

void AnimatedRectangle::reset() {
	doAnimateEntry = false;
	show = false;
	doAnimateHoverIn = false;
	doAnimateHoverOut = false;
	sound = false;
	t = 0;
}

void AnimatedRectangle::entry() {
	t = 0;
	show = true;
	sound = false;
}

void AnimatedRectangle::playHover() {
	m_fmod.playSound( "hoverCard" );
}

MenuRectangle::MenuRectangle( float& dt, Othello::UI::Audio::FMOD& fmod ) : AnimatedRectangle( dt, fmod ) {
	entryRY = 0.0f, entryTime = defaultEntryTime, normalX = defaultNormalX, hoverX = 1.1f, hoverZ = 0.1f, hoverTime = defaultHoverTime, clickZ = 0.04f;
}

bool MenuRectangle::loadBackTexture( string path ) {
	return AGL_loadTexture( backTexture, path );
}

void MenuRectangle::drawOutline() {
	// Bind texture:
	glBindTexture( GL_TEXTURE_2D, backTexture );
	glBegin( GL_QUADS );
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.90f, -0.21f, 0.95f );  // Bottom Left Of The Texture and Quad
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 4.0f, -0.21f, 0.95f );  // Bottom Right Of The Texture and Quad
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 4.0f, 0.21f, 0.95f );  // Top Right Of The Texture and Quad
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.90f, 0.21f, 0.95f );  // Top Left Of The Texture and Quad
	glEnd();
}

void MenuRectangle::drawReal() {
	// Bind texture:
	glBindTexture( GL_TEXTURE_2D, texture );
	glBegin( GL_QUADS );
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.5f, -0.2f, 1.0f );  // Bottom Left Of The Texture and Quad
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 2.7f, -0.2f, 1.0f );  // Bottom Right Of The Texture and Quad
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 2.7f, 0.2f, 1.0f );  // Top Right Of The Texture and Quad
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.5f, 0.2f, 1.0f );  // Top Left Of The Texture and Quad
	glEnd();
}

void MenuRectangle::playHover() {
	m_fmod.playSound( "hoverButton" );
}

ButtonRectangle::ButtonRectangle( float& dt, Othello::UI::Audio::FMOD& fmod ) : AnimatedRectangle( dt, fmod ) {
	entryRY = 0.0f, entryTime = defaultEntryTime, normalX = 0.0f, hoverX = 0.0f, hoverZ = 0.05f, hoverTime = defaultHoverTime, clickZ = -hoverZ;
}

void ButtonRectangle::playHover() {
	m_fmod.playSound( "hoverButton" );
}

void ButtonRectangle::drawOutline() {
	// Unbind texture:
	glBindTexture( GL_TEXTURE_2D, 0 );
	glLineWidth( 2 );
	glColor3f( 1.0, 1.0, 1.0 );
	glBegin( GL_LINES );
	glVertex3f( -0.5f, -0.1f, 0.99f ); glVertex3f( 0.5f, -0.1f, 0.99f );
	glVertex3f( 0.5f, -0.1f, 0.99f ); glVertex3f( 0.5f, 0.1f, 0.99f );
	glVertex3f( 0.5f, 0.1f, 0.99f ); glVertex3f( -0.5f, 0.1f, 0.99f );
	glVertex3f( -0.5f, 0.1f, 0.99f ); glVertex3f( -0.5f, -0.1f, 0.99f );
	glEnd();
}

void ButtonRectangle::drawReal() {
	// Bind texture:
	glBindTexture( GL_TEXTURE_2D, texture );
	glBegin( GL_QUADS );
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -0.5f, -0.1f, 1.0f );  // Bottom Left Of The Texture and Quad
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 0.5f, -0.1f, 1.0f );  // Bottom Right Of The Texture and Quad
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 0.5f, 0.1f, 1.0f );  // Top Right Of The Texture and Quad
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -0.5f, 0.1f, 1.0f );  // Top Left Of The Texture and Quad
	glEnd();
}

Allegro::Allegro( Othello::UI::Audio::FMOD& fmod ) : m_fmod( fmod ), rectPVP( dt, fmod ), rectPVAI( dt, fmod ), rectPVPNet( dt, fmod ), rectAI1( dt, fmod ), rectAI2( dt, fmod ), rectAI3( dt, fmod ), rectContinue( dt, fmod ), rectNew( dt, fmod ), rectOptions( dt, fmod ), rectQuit( dt, fmod ), rectCancel( dt, fmod ) {
	initAllegro();

	currentUI = this;

	menu();
}

Allegro::~Allegro() {
	currentUI = nullptr;
	exitAllegro();
}


void Allegro::initAllegro() {
	// Hide console window:
	hideConsole();

	// Load configuration:
	loadConfig();

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

	// Install the close button handler:
	LOCK_FUNCTION( Othello::UI::Main::AllegroCloseHandler );
	set_close_button_callback( Othello::UI::Main::AllegroCloseHandler );

	initGL();
	ImGui_ImplAGL_Init();

	loadSprites();
	loadBackgrounds();
	loadFonts();
	loadIMGUI();
	loadRectangles();
}

void Allegro::initGL() {
	// Set the color depth to 32 bits-per-pixel:
	allegro_gl_set( AGL_COLOR_DEPTH, 32 );
	allegro_gl_set( AGL_Z_DEPTH, 8 );
	allegro_gl_set( AGL_SUGGEST, AGL_COLOR_DEPTH | AGL_Z_DEPTH );

	// Enable alpha channel when loading textures
	allegro_gl_use_alpha_channel( true );

	// Create a window:
	if( set_gfx_mode( winMode, winWidth, winHeight, 0, 0 ) ) {
		// Error creating window:
		throw runtime_error( "Mode graphique invalide. Impossible de créer la fenêtre de jeu." );
	}

	// Set window title:
	set_window_title( "ECE Othello" );

	// Set cursor as hardware pointer:
	/*enable_hardware_cursor();
	select_mouse_cursor( 2 );*/
	//show_mouse( screen );

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

	// Switch back to the modelview matrix:
	glMatrixMode( GL_MODELVIEW );

	glEnable( GL_TEXTURE_2D );                           // Enable Texture Mapping
	glShadeModel( GL_SMOOTH );                           // Enable Smooth Shading
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); // Define Alpha Blending function
	glEnable( GL_BLEND );                                // Enable Alpha Blending
	glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );              // Black Background
	glClearDepth( 1.0f );                                // Depth Buffer Setup
	glEnable( GL_DEPTH_TEST );                           // Enables Depth Testing
	glDepthFunc( GL_LEQUAL );                            // The Type Of Depth Testing To Do
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST ); // Really Nice Perspective Calculations

	// Init bitmap:
	m_page = create_bitmap( SCREEN_W, SCREEN_H );

}

void Allegro::exitAllegro() {
	freeBitmaps();

	ImGui_ImplAGL_Shutdown();

	allegro_exit();
}

void Allegro::loadSprites() {
	string path;
	BITMAP* bmp;
	vector<string> bmpNames = {
		"logo"
	};

	for( const auto& bmpName : bmpNames ) {
		path = "images/menu/";
		path += bmpName;
		path += ".png";

		bmp = load_png( path.c_str(), NULL );
		if( bmp ) {
			m_bitmaps.insert( make_pair( bmpName, bmp ) );
		} else {
			path = "File not found: ";
			path = "images/menu/";
			path += bmpName;
			path += ".png";
			throw ios_base::failure( path );
		}
	}

	m_cursor = load_png( "images/cursor.png", NULL );
}

void Allegro::loadBackgrounds() {
	string path;
	BITMAP* bmp;
	vector<string> bmpNames = {
		"menuBg",
	    "selectBg",
	    "loadingBg"
	};

	for( const auto& bmpName : bmpNames ) {
		path = "images/menu/";
		path += bmpName;
		path += ".jpg";

		bmp = load_jpg( path.c_str(), NULL );
		if( bmp ) {
			m_bitmaps.insert( make_pair( bmpName, bmp ) );
		} else {
			path = "File not found: ";
			path = "images/menu/";
			path += bmpName;
			path += ".png";
			throw ios_base::failure( path );
		}
	}
}

void Allegro::loadFonts() {
	m_textFont = load_font( "fonts/droidsans_14_mono.pcx", NULL, NULL );
	if( !m_textFont ) {
		throw ios_base::failure( "File not found: fonts/droidsans_14_mono.pcx" );
	}
	font = m_textFont;
}

void Allegro::loadIMGUI() {
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->Clear();
	ImGui_ImplAGL_InvalidateDeviceObjects();
	io.Fonts->AddFontFromFileTTF( "fonts/DroidSans.ttf", 16.0f );
	io.Fonts->AddFontFromFileTTF( "fonts/DroidSans.ttf", 32.0f );
	io.Fonts->Build();
	io.FontDefault = ImGui::GetIO().Fonts->Fonts[ FONT_SIZE_16 ];

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ ImGuiCol_Text ]                  = ImVec4( 1.00f, 1.00f, 1.00f, 1.00f );
	style.Colors[ ImGuiCol_WindowBg ]              = ImVec4( 0.15f, 0.20f, 0.29f, 0.94f );
	style.Colors[ ImGuiCol_Button ]                = ImVec4( 0.90f, 0.51f, 0.35f, 0.84f );
	style.Colors[ ImGuiCol_ButtonHovered ]         = ImVec4( 1.00f, 0.55f, 0.31f, 0.93f );
	style.Colors[ ImGuiCol_ButtonActive ]          = ImVec4( 1.00f, 0.71f, 0.50f, 1.00f );
	ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, 0.0f );
}

void Allegro::loadRectangles() {
	rectPVP.loadTexture( "images/menu/gamemode_pvp.png" );
	rectPVAI.loadTexture( "images/menu/gamemode_pvai.png" );
	rectPVPNet.loadTexture( "images/menu/gamemode_pvpnet.png" );

	rectAI1.loadTexture( "images/menu/ai1.png" );
	rectAI2.loadTexture( "images/menu/ai2.png" );
	rectAI3.loadTexture( "images/menu/ai3.png" );

	rectContinue.loadTexture( "images/menu/continue.png" );
	rectContinue.loadBackTexture( "images/menu/back.png" );
	rectNew.loadTexture( "images/menu/new.png" );
	rectNew.loadBackTexture( "images/menu/back.png" );
	rectOptions.loadTexture( "images/menu/options.png" );
	rectOptions.loadBackTexture( "images/menu/back.png" );
	rectQuit.loadTexture( "images/menu/quit.png" );
	rectQuit.loadBackTexture( "images/menu/back.png" );

	rectCancel.loadTexture( "images/menu/cancel.png" );

	rectContinue.entry();
	rectNew.entry();
	rectOptions.entry();
	rectQuit.entry();
	rectCancel.entry();
}

void Allegro::loadConfig() {
	ifstream configFile( configPath, ios::out );

	if( configFile.is_open() ) {
		string soundEnabled, volume, winModeS, winResS;
		if( !getline( configFile, winModeS ) )
			return;
		if( !getline( configFile, winResS ) )
			return;
		if( !getline( configFile, soundEnabled ) )
			return;
		if( !getline( configFile, volume ) )
			return;
		stringstream volumeSS( volume ), winModeSS( winModeS ), winResSS( winResS );
		winModeSS >> selWinMode;
		winResSS >> selWinResI;
		selWinRes = static_cast<Allegro::Resolution>( selWinResI );
		if( selWinMode == 1 )
			winMode = GFX_OPENGL_FULLSCREEN;
		else
			winMode = GFX_OPENGL_WINDOWED;
		resolutionSelector( selWinRes );
		volumeSS >> m_volume;
		if( soundEnabled == "y" ) {
			m_soundActivated = true;
			m_fmod.setMasterVolume( m_volume / 100 );
		} else {
			m_soundActivated = false;
			m_fmod.setMasterVolume( 0.0f );
		}

		prevSelWinMode = selWinMode;
		prevSelWinResI = selWinResI;

		configFile.close();
	}
}

void Allegro::saveConfig() {
	ofstream configFile( configPath, ios::in | ios::trunc );

	if( configFile.is_open() ) {
		configFile << selWinMode << endl
				   << selWinResI << endl
				   << ( m_soundActivated ? 'y' : 'f' ) << endl
				   << m_volume;
		configFile.close();
	}
}

void Allegro::freeBitmaps() {
	destroy_bitmap( m_page );

	for( auto bmp = m_bitmaps.begin(); bmp != m_bitmaps.end(); bmp++ ) {
		if( bmp->second != nullptr ) {
			destroy_bitmap( bmp->second );
			bmp->second = nullptr;
		}
	}
}

void Allegro::handleMouse() {
	ImGuiIO &io = ImGui::GetIO();

	// On teste si le curseur est sur les rectangles
	// Si oui, on anime l'effet d'avancement, sinon on anime l'effet de retrait
	// On teste aussi si le bouton gauche est enfoncé et on anime en conséquence
	// On teste aussi si le bouton gauche est relaché, si oui on page à la page qu'il faut
	if( stage == Stage::New ) {
		if( iny > 0.75 && iny < 3.75 && inz > 0 && inz < 2 ) {
			//if( inx > -3.2 && inx < -1.2 ) {
			if( inx > -2.2 && inx < -0.2 ) {
				// Rectangle Nouvelle Partie PVP
				rectPVP.animateHoverIn();
				rectPVP.clicked = io.MouseDown[ 0 ];

				if( io.MouseReleased[ 0 ] ) {
					rectPVP.animateHoverOut();
					rectPVP.clicked = false;
					forward( Stage::NewPlayer );
				}
			} else {
				rectPVP.animateHoverOut();
			}

			//if( inx > -1.0 && inx < 1.0 ) {
			if( inx > 0.2f && inx < 2.2f ) {
				// Rectangle Nouvelle Partie PVAI
				rectPVAI.animateHoverIn();
				rectPVAI.clicked = io.MouseDown[ 0 ];

				if( io.MouseReleased[ 0 ] ) {
					rectPVAI.animateHoverOut();
					rectPVAI.clicked = false;
					forward( Stage::NewAISelect );
				}
			} else {
				rectPVAI.animateHoverOut();
			}

			/*if( inx > 1.2 && inx < 3.2 ) {
				// Rectangle Nouvelle Partie PVP réseau
				rectPVPNet.animateHoverIn();
				rectPVPNet.clicked = io.MouseDown[ 0 ];

				if( io.MouseReleased[ 0 ] ) {
					rectPVPNet.animateHoverOut();
					rectPVPNet.clicked = false;
					forward( Stage::NewPlayerNet );
				}
			} else {
				rectPVPNet.animateHoverOut();
			}*/
		} else {
			rectPVPNet.animateHoverOut();
			rectPVAI.animateHoverOut();
			rectPVP.animateHoverOut();
		}
	} else if( stage == Stage::NewAISelect ) {
		if( iny > 0.75 && iny < 3.75 && inz > 0 && inz < 2 ) {
			if( inx > -3.2 && inx < -1.2 ) {
				// Rectangle Nouvelle Partie IA Niveau 1
				rectAI1.animateHoverIn();
				rectAI1.clicked = io.MouseDown[ 0 ];

				if( io.MouseReleased[ 0 ] ) {
					ai_level = 1;
					rectAI1.animateHoverOut();
					rectAI1.clicked = false;
					forward( Stage::NewAI );
				}
			} else {
				rectAI1.animateHoverOut();
			}

			if( inx > -1.0 && inx < 1.0 ) {
				// Rectangle Nouvelle Partie IA Niveau 2
				rectAI2.animateHoverIn();
				rectAI2.clicked = io.MouseDown[ 0 ];

				if( io.MouseReleased[ 0 ] ) {
					ai_level = 2;
					rectAI2.animateHoverOut();
					rectAI2.clicked = false;
					forward( Stage::NewAI );
				}
			} else {
				rectAI2.animateHoverOut();
			}

			if( inx > 1.2 && inx < 3.2 ) {
				// Rectangle Nouvelle Partie IA Niveau 3
				rectAI3.animateHoverIn();
				rectAI3.clicked = io.MouseDown[ 0 ];

				if( io.MouseReleased[ 0 ] ) {
					ai_level = 3;
					rectAI3.animateHoverOut();
					rectAI3.clicked = false;
					forward( Stage::NewAI );
				}
			} else {
				rectAI3.animateHoverOut();
			}
		} else {
			rectAI1.animateHoverOut();
			rectAI2.animateHoverOut();
			rectAI3.animateHoverOut();
		}
	} else if( stage == Stage::Menu ) {
		if( inx > -1.5 && inx < 2.7 && inz > 0 && inz < 2 ) {
			if( isSave ) {
				if( iny > 1.35 && iny < 1.64 ) {
					rectContinue.animateHoverIn();
					rectContinue.clicked = io.MouseDown[ 0 ];

					if( io.MouseReleased[ 0 ] ) {
						rectContinue.animateHoverOut();
						rectContinue.clicked = false;
						forward( Stage::ContinueParty );
					}
				} else {
					rectContinue.animateHoverOut();
				}
			}
			if( iny > 0.86 && iny < 1.14 ) {
				rectNew.animateHoverIn();
				rectNew.clicked = io.MouseDown[ 0 ];

				if( io.MouseReleased[ 0 ] ) {
					rectNew.animateHoverOut();
					rectNew.clicked = false;
					forward( Stage::New );
				}
			} else {
				rectNew.animateHoverOut();
			}
			if( iny > 0.355 && iny < 0.64 ) {
				rectOptions.animateHoverIn();
				rectOptions.clicked = io.MouseDown[ 0 ];

				if( io.MouseReleased[ 0 ] ) {
					rectOptions.animateHoverOut();
					rectOptions.clicked = false;
					forward( Stage::Options );
				}
			} else {
				rectOptions.animateHoverOut();
			}
			if( iny > -0.145 && iny < 0.13 ) {
				rectQuit.animateHoverIn();
				rectQuit.clicked = io.MouseDown[ 0 ];

				if( io.MouseReleased[ 0 ] ) {
					rectQuit.animateHoverOut();
					rectQuit.clicked = false;
					forward( Stage::Quit );
				}
			} else {
				rectQuit.animateHoverOut();
			}
		} else {
			rectContinue.animateHoverOut();
			rectNew.animateHoverOut();
			rectOptions.animateHoverOut();
			rectQuit.animateHoverOut();
		}
	}
	if( stage == Stage::New || stage == Stage::NewAISelect ) {
		if( inz > 0 && inz < 2 && iny > -0.1 && iny < 0.1 && inx > -0.5 && inx < 0.5 ) {
			rectCancel.animateHoverIn();
			rectCancel.clicked = io.MouseDown[ 0 ];

			if( io.MouseReleased[ 0 ] ) {
				rectCancel.animateHoverOut();
				rectCancel.clicked = false;
				back();
			}
		} else {
			rectCancel.animateHoverOut();
		}
	}
}

void Allegro::newFrame() {
	COMPUTE_DT( dt );
	ImGui_ImplAGL_NewFrame( dt );
	before = clock();
	t += dt;
	GL_windowToObjectf( mouse_x, mouse_y, &inx, &iny, &inz );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	m_fmod.update();
}

void Allegro::endFrame() {
	renderMouse();
	glFlush();
	allegro_gl_flip();
}

void Allegro::updateInputs() {
	prevKeyEsc = keyEsc;
	keyEsc = (bool) key[ KEY_ESC ];

	if( !prevKeyEsc && keyEsc ) {
		back();
	}
}

void Allegro::back() {
	switch( stage ) {
		case Stage::Menu:
			stage = Stage::Quit;
			break;
		case Stage::Quit:
			isSave = Othello::Save::SaveManager::check();
			stage = Stage::Menu;
			break;
		case Stage::Options:
			isSave = Othello::Save::SaveManager::check();
			stage = Stage::Menu;
			break;
		case Stage::New:
			m_fmod.playSound( "back" );
			isSave = Othello::Save::SaveManager::check();
			stage = Stage::Menu;
			break;
		case Stage::NewPlayer:
			stage = Stage::New;
			break;
		case Stage::NewAISelect:
			m_fmod.playSound( "back" );
			t = 0;
			rectPVP.reset();
			rectPVAI.reset();
			rectPVPNet.reset();
			stage = Stage::New;
			break;
		case Stage::NewAI:
			stage = Stage::NewAISelect;
			break;
		case Stage::ContinueParty:
			isSave = Othello::Save::SaveManager::check();
			stage = Stage::Menu;
			break;
		case Stage::NewAIParty:
			isSave = Othello::Save::SaveManager::check();
			stage = Stage::New;
			break;
		case Stage::NewPlayerParty:
			isSave = Othello::Save::SaveManager::check();
			stage = Stage::New;
			break;
		default:
			break;
	}
}

void Allegro::forward( Stage newStage ) {
	switch( newStage ) {
		case Stage::New:
			m_fmod.playSound( "clickNextCard" );
			rectPVP.reset();
			rectPVAI.reset();
			rectPVPNet.reset();
			t = 0;
			stage = newStage;
			break;

		case Stage::NewAISelect:
			m_fmod.playSound( "clickNextCard" );
			rectAI1.reset();
			rectAI2.reset();
			rectAI3.reset();
			t = 0;
			stage = newStage;
			break;

		case Stage::Options:
			prevSelWinMode = selWinMode;
			prevSelWinResI = selWinResI;
			stage = newStage;
			break;

		default:
			stage = newStage;
			break;
	}
}

void Allegro::renderScene() {
	display();
	renderMenu();
	renderOptions();
	renderQuit();
	renderNew();
	renderNewAISelect();
	renderCancelButton();
	renderNewPlayer();
	renderNewAI();
}

void Allegro::display() {
	allegro_gl_set_allegro_mode();

	if( stage == Stage::Menu || stage == Stage::Options || stage == Stage::Quit ) {
		stretch_blit( m_bitmaps.find( "menuBg" )->second, m_page, 0, 0, m_bitmaps.find( "menuBg" )->second->w, m_bitmaps.find( "menuBg" )->second->h, 0, 0, SCREEN_W, SCREEN_H);
		set_alpha_blender();

		draw_trans_sprite( m_page, m_bitmaps.find( "logo" )->second, SCREEN_W - 50 - m_bitmaps.find( "logo" )->second->w, 100 );

		blit( m_page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );
	} else {
		stretch_blit( m_bitmaps.find( "selectBg" )->second, m_page, 0, 0, m_bitmaps.find( "selectBg" )->second->w, m_bitmaps.find( "selectBg" )->second->h, 0, 0, SCREEN_W, SCREEN_H );
		blit( m_page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );
	}

	allegro_gl_unset_allegro_mode();
}

void Allegro::renderMenu() {
	if( stage == Stage::Menu || stage == Stage::Options || stage == Stage::Quit ) {
		if( isSave ) {
			glLoadIdentity();
			glTranslatef( -4.10f, 0.75f, -8.0f );
			rectContinue.draw();
		}

		glLoadIdentity();
		glTranslatef( -4.10f, 0.25f, -8.0f );
		rectNew.draw();

		glLoadIdentity();
		glTranslatef( -4.10f, -0.25f, -8.0f );
		rectOptions.draw();

		glLoadIdentity();
		glTranslatef( -4.10f, -0.75f, -8.0f );
		rectQuit.draw();
	}
}

void Allegro::renderNew() {
	if( stage == Stage::New || stage == Stage::NewPlayer ) {
		/*glLoadIdentity();
		glTranslatef( 1.2f, 0.0f, -8.0f );
		rectPVPNet.draw();*/

		glLoadIdentity();
		//glTranslatef( -1.0f, 0.0f, -8.0f );
		glTranslatef( 0.2f, 0.0f, -8.0f );
		rectPVAI.draw();

		glLoadIdentity();
		//glTranslatef( -3.2f, 0.0f, -8.0f );
		glTranslatef( -2.2f, 0.0f, -8.0f );
		rectPVP.draw();

		//rectPVPNet.animateEntry();

		//if( t > 3.0f )
			rectPVAI.animateEntry();

		//if( t > 6.0f )
		if( t > 3.0f )
			rectPVP.animateEntry();
	}
}

void Allegro::renderNewAISelect() {
	if( stage == Stage::NewAISelect || stage == Stage::NewAI ) {
		glLoadIdentity();
		glTranslatef( 1.2f, 0.0f, -8.0f );
		rectAI3.draw();

		glLoadIdentity();
		glTranslatef( -1.0f, 0.0f, -8.0f );
		rectAI2.draw();

		glLoadIdentity();
		glTranslatef( -3.2f, 0.0f, -8.0f );
		rectAI1.draw();

		rectAI3.animateEntry();

		if( t > 3.0f )
			rectAI2.animateEntry();

		if( t > 6.0f )
			rectAI1.animateEntry();
	}
}

void Allegro::renderNewPlayer() {
	if( stage == Stage::NewPlayer ) {
		float button_x, button_y, input_x;
		renderModalShadow();

		ImGui::SetNextWindowSize( ImVec2( SCREEN_W, NEWPLAYER_HEIGHT ), ImGuiSetCond_Appearing );
		ImGui::SetNextWindowPosCenter();
		ImGui::Begin( "", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar );
		button_x = ( ImGui::GetWindowWidth() - MODAL_BUTTON_WIDTH ) / 2;
		button_y = NEWPLAYER_HEIGHT - NEWPLAYER_BOTTOM_MARGIN - MODAL_BUTTON_HEIGHT;
		input_x = ( ImGui::GetWindowWidth() - ImGui::CalcItemWidth() ) / 2;
		ImGui::SetCursorPosX( ( ImGui::GetWindowWidth() - ImGui::CalcTextSize( "JOUEUR VS JOUEUR" ).x ) / 2 );
		ImGui::Text( "JOUEUR VS JOUEUR" );
		ImGui::SetCursorPosX( input_x );
		ImGui::InputText( "Nom du joueur 1", player1name, NAME_SIZE );
		ImGui::SetCursorPosX( input_x );
		ImGui::InputText( "Nom du joueur 2", player2name, NAME_SIZE );
		ImGui::SetCursorPosY( button_y );
		ImGui::SetCursorPosX( button_x - MODAL_BUTTON_WIDTH );
		if( ImGui::Button( "ANNULER", ImVec2( MODAL_BUTTON_WIDTH, MODAL_BUTTON_HEIGHT ) ) ) {
			back();
			ImGui::GetIO().MouseReleased[ 0 ] = false;
		}
		ImGui::SetCursorPosY( button_y );
		ImGui::SetCursorPosX( button_x + MODAL_BUTTON_WIDTH );
		if( ImGui::Button( "CRÉER", ImVec2( MODAL_BUTTON_WIDTH, MODAL_BUTTON_HEIGHT ) ) ) {
			forward( Stage::NewPlayerParty );
			ImGui::GetIO().MouseReleased[ 0 ] = false;
		}
		ImGui::End();

		ImGui::Render();
	}
}

void Allegro::renderOptions() {
	if( stage == Stage::Options ) {
		float button_x, input_x;
		renderModalShadow();

		ImGui::SetNextWindowSize( ImVec2( SCREEN_W, OPTIONS_HEIGHT ), ImGuiSetCond_Appearing );
		ImGui::SetNextWindowPosCenter();
		ImGui::Begin( "", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar );
		button_x  = ( ImGui::GetWindowWidth() - MODAL_BUTTON_WIDTH ) / 2;
		input_x = ( ImGui::GetWindowWidth() - ImGui::CalcItemWidth() ) / 2;
		ImGui::SetCursorPosX( ( ImGui::GetWindowWidth() - ImGui::CalcTextSize( "OPTIONS" ).x ) / 2 );
		ImGui::Text( "OPTIONS" );
		ImGui::SetCursorPosX( input_x );
		ImGui::Checkbox( "Sons et musiques", &m_soundActivated );
		ImGui::SetCursorPosX( input_x );
		ImGui::SliderFloat( "Volume", &m_volume, 0, 100, "%.f" );
		if( m_soundActivated ) {
			this->m_fmod.setMasterVolume( m_volume / 100 );
		} else {
			this->m_fmod.setMasterVolume( 0.0f );
		}
		ImGui::SetCursorPosX( input_x );
		ImGui::ListBox( "Mode d'affichage", &selWinMode, windowModes, windowModesNumber, 2 );
		ImGui::SetCursorPosX( input_x );
		ImGui::ListBox( "Résolution", &selWinResI, resolutionsNames, resolutionsNamesNumber, 4 );
		ImGui::SetCursorPosY( OPTIONS_HEIGHT - OPTIONS_WIN_MARGIN - MODAL_BUTTON_HEIGHT );
		ImGui::SetCursorPosX( button_x );
		if( ImGui::Button( "FERMER", ImVec2( MODAL_BUTTON_WIDTH, MODAL_BUTTON_HEIGHT ) ) ) {
			saveConfig();
			back();
			ImGui::GetIO().MouseReleased[ 0 ] = false;
		}
		ImGui::End();

		ImGui::Render();
	}
}

void Allegro::renderModalShadow() {
	allegro_gl_set_allegro_mode();
	set_trans_blender( 0, 0, 0, PAUSE_BLENDING_FACTOR );

	drawing_mode( DRAW_MODE_TRANS, NULL, 0, 0 );
	rectfill( m_page, 0, 0, m_page->w, m_page->h, makecol( 0, 0, 0 ) );
	drawing_mode( DRAW_MODE_SOLID, NULL, 0, 0 );

	set_alpha_blender();

	blit( m_page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );
	allegro_gl_unset_allegro_mode();
}

void Allegro::renderQuit() {
	if( stage == Stage::Quit ) {
		float button_x;
		renderModalShadow();

		ImGui::SetNextWindowSize( ImVec2( SCREEN_W, QUIT_HEIGHT ), ImGuiSetCond_Appearing );
		ImGui::SetNextWindowPosCenter();
		ImGui::Begin( "", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar );
		button_x  = ( ImGui::GetWindowWidth() - MODAL_BUTTON_WIDTH ) / 2;
		ImGui::SetCursorPosX( ( ImGui::GetWindowWidth() - ImGui::CalcTextSize( "VOULEZ-VOUS QUITTER LE JEU ?" ).x ) / 2 );
		ImGui::Text( "VOULEZ-VOUS QUITTER LE JEU ?" );
		ImGui::SetCursorPosX( button_x );
		if( ImGui::Button( "QUITTER", ImVec2( MODAL_BUTTON_WIDTH, MODAL_BUTTON_HEIGHT ) ) ) {
			quit = true;
		}
		ImGui::SetCursorPosX( button_x );
		if( ImGui::Button( "ANNULER", ImVec2( MODAL_BUTTON_WIDTH, MODAL_BUTTON_HEIGHT ) ) ) {
			back();
			ImGui::GetIO().MouseReleased[ 0 ] = false;
		}
		ImGui::End();

		ImGui::Render();
	}
}

void Allegro::renderNewAI() {
	if( stage == Stage::NewAI ) {
		float button_x, button_y, input_x;
		renderModalShadow();

		ImGui::SetNextWindowSize( ImVec2( SCREEN_W, NEWAI_HEIGHT ), ImGuiSetCond_Appearing );
		ImGui::SetNextWindowPosCenter();
		ImGui::Begin( "", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar );
		button_x = ( ImGui::GetWindowWidth() - MODAL_BUTTON_WIDTH ) / 2;
		button_y = NEWPLAYER_HEIGHT - NEWPLAYER_BOTTOM_MARGIN - MODAL_BUTTON_HEIGHT;
		input_x = ( ImGui::GetWindowWidth() - ImGui::CalcItemWidth() ) / 2;
		ImGui::SetCursorPosX( ( ImGui::GetWindowWidth() - ImGui::CalcTextSize( "JOUEUR VS IA" ).x ) / 2 );
		ImGui::Text( "JOUEUR VS IA" );
		ImGui::SetCursorPosX( ( ImGui::GetWindowWidth() - ImGui::CalcTextSize( "Niveau IA: 0" ).x ) / 2 );
		ImGui::Text( "Niveau IA: %d", ai_level );
		ImGui::SetCursorPosX( input_x );
		ImGui::InputText( "Nom du joueur", player1name, NAME_SIZE );
		ImGui::SetCursorPosY( button_y );
		ImGui::SetCursorPosX( button_x - MODAL_BUTTON_WIDTH );
		if( ImGui::Button( "ANNULER", ImVec2( MODAL_BUTTON_WIDTH, MODAL_BUTTON_HEIGHT ) ) ) {
			back();
			ImGui::GetIO().MouseReleased[ 0 ] = false;
		}
		ImGui::SetCursorPosY( button_y );
		ImGui::SetCursorPosX( button_x + MODAL_BUTTON_WIDTH );
		if( ImGui::Button( "CRÉER", ImVec2( MODAL_BUTTON_WIDTH, MODAL_BUTTON_HEIGHT ) ) ) {
			forward( Stage::NewAIParty );
			ImGui::GetIO().MouseReleased[ 0 ] = false;
		}
		ImGui::End();

		ImGui::Render();
	}
}

void Allegro::renderLoading() {
	allegro_gl_set_allegro_mode();
	BITMAP* bg = m_bitmaps.find( "loadingBg" )->second;
	stretch_blit( bg, m_page, 0, 0, bg->w, bg->h, 0, 0, SCREEN_W, SCREEN_H );
	blit( m_page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );
	allegro_gl_unset_allegro_mode();

	ImGui::SetNextWindowSize( ImVec2( SCREEN_W, LOADING_HEIGHT ), ImGuiSetCond_Appearing );
	ImGui::SetNextWindowPosCenter();
	ImGui::Begin( "", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar );
	ImVec2 size = ImGui::CalcTextSize( "CHARGEMENT..." );
	ImGui::SetCursorPosX( ( ImGui::GetWindowWidth() - size.x ) / 2 );
	ImGui::SetCursorPosY( ( ImGui::GetWindowHeight() - size.y ) / 2 );
	ImGui::Text( "CHARGEMENT..." );
	ImGui::End();

	ImGui::Render();
}

void Allegro::renderCancelButton() {
	if( stage == Stage::New || stage == Stage::NewAISelect || stage == Stage::NewPlayer || stage == Stage::NewAI ) {
		glLoadIdentity();
		glTranslatef( 0.0f, -2.25f, -8.0f );
		rectCancel.draw();
	}
}

void Allegro::renderMouse() {
	allegro_gl_set_allegro_mode();
	set_alpha_blender();
	draw_trans_sprite( screen, m_cursor, mouse_x, mouse_y );
	allegro_gl_unset_allegro_mode();
}

void Allegro::menu() {
	m_fmod.playMusic( "menu" );

	isSave = Othello::Save::SaveManager::check();
	before = clock() - 1;

	while( !quit ) {
		newFrame();
		updateInputs();
		handleMouse();
		renderScene();
		endFrame();
		reopenAllegro();
		redirectGame();
	}
}

void Allegro::loadGame() {
	if( isSave ) {
		try {
			Othello::Game game( m_fmod, true );
		} catch( logic_error e ) {
			isSave = Othello::Save::SaveManager::check();
			error( e.what() );
		}
	} else {
		error( "Pas de sauvegarde !" );
	}
}

void Allegro::newPlayerGame() {
	m_players.clear();
	m_players.push_back( new Othello::Players::Human( string( player1name ), Othello::Board::Pun::Colors::black ) );
	m_players.push_back( new Othello::Players::Human( string( player2name ), Othello::Board::Pun::Colors::white ) );

	try {
		Othello::Game game( m_players, m_fmod, true );
	} catch( logic_error e ) {
		error( e.what() );
	}

	for( Othello::Players::Player* player : m_players ) {
		delete player;
	}
}

void Allegro::newAIGame() {
	m_players.clear();

	switch( ai_level ) {
		case 1:
			m_players.push_back( new Othello::Players::RandomAI( "IA", Othello::Board::Pun::Colors::white ) );
			break;
		case 2:
			m_players.push_back( new Othello::Players::SimpleAI( "IA", Othello::Board::Pun::Colors::white ) );
			break;
		case 3:
			m_players.push_back( new Othello::Players::EnhancedAI( "IA", Othello::Board::Pun::Colors::white ) );
			break;
	}

	m_players.push_back( new Othello::Players::Human( string( player1name ), Othello::Board::Pun::Colors::black ) );

	try {
		Othello::Game game( m_players, m_fmod, true );
	} catch( logic_error e ) {
		error( e.what() );
	}

	for( Othello::Players::Player* player : m_players ) {
		delete player;
	}
}

void Allegro::error( string message ) {
	before = clock() - 1;
	for( bool loop = true; loop; ) {
		newFrame();

		ImGui::SetNextWindowSize( ImVec2( ERROR_WIDTH, ERROR_HEIGHT ), ImGuiSetCond_Appearing );
		ImGui::SetNextWindowPosCenter();
		ImGui::Begin( "Erreur", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings );
		ImGui::Text( message.c_str() );
		ImGui::SetCursorPosX( ( ImGui::GetWindowWidth() - MODAL_BUTTON_WIDTH ) / 2 );
		if( ImGui::Button( "OK", ImVec2( MODAL_BUTTON_WIDTH, MODAL_BUTTON_HEIGHT ) ) ) {
			loop = false;
			ImGui::GetIO().MouseReleased[ 0 ] = false;
		}
		ImGui::End();

		ImGui::Render();

		endFrame();
	}
}

void Allegro::redirectGame() {
	if( stage == Stage::ContinueParty ) {
		m_fmod.stopMusic();
		newFrame();
		renderLoading();
		endFrame();
		loadGame();
		ImGui::GetIO().MouseReleased[ 0 ] = false;
		back();
		m_fmod.playMusic( "menu" );
	} else if( stage == Stage::NewPlayerParty ) {
		m_fmod.stopMusic();
		newFrame();
		renderLoading();
		endFrame();
		newPlayerGame();
		ImGui::GetIO().MouseReleased[ 0 ] = false;
		back();
		m_fmod.playMusic( "menu" );
	} else if( stage == Stage::NewAIParty ) {
		m_fmod.stopMusic();
		newFrame();
		renderLoading();
		endFrame();
		newAIGame();
		ImGui::GetIO().MouseReleased[ 0 ] = false;
		back();
		m_fmod.playMusic( "menu" );
	}
}

void Allegro::resolutionSelector( Allegro::Resolution res ) {
	unsigned int resI = static_cast<unsigned int>( res );
	if( resI < resolutions.size() ) {
		winWidth = resolutions[ resI ].first;
		winHeight = resolutions[ resI ].second;
	}
}

void Allegro::reopenAllegro() {
	if( stage == Stage::Menu && ( prevSelWinMode != selWinMode || prevSelWinResI != selWinResI ) ) {
		destroy_bitmap( m_page );
		loadConfig();
		initGL();
		m_page = create_bitmap( SCREEN_W, SCREEN_H );
		loadIMGUI();
		loadRectangles();
	}
}

void Allegro::forceQuit() {
	quit = true;
}

void Allegro::hideConsole() {
	#ifdef ALLEGRO_WINDOWS
		ShowWindow( GetConsoleWindow(), SW_HIDE );
	#endif
}
