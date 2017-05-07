#include "../../inc/ui/games/gameallegroui.hpp"

using namespace std;
using namespace Othello;
using namespace Othello::Board;
using namespace Othello::Players;
using namespace Othello::UI::Games;

float Othello::UI::Games::EaseOutQuad( float t, float maxt ) {
	float sct = t / maxt;
	float opt = 1 - sct;
	return 1 - opt * opt;
}

MessageBar::MessageBar() {}
MessageBar::MessageBar( BITMAP* page, FONT* font ) : page( page ), font( font ) {}

void MessageBar::draw()  {
	rectfill( page, xBar, y, xBar + widthBar, y + height, colorBarBack );
	textprintf_ex( page, font, xBar + widthIcon + marginX, y + marginY, colorBarFront, -1, "%s", message.c_str() );
	rectfill( page, xIcon, y, xIcon + widthIcon, y + height, colorIconBack );
	textprintf_ex( page, font, xIcon + marginXIcon, y + marginYIcon, colorIconFront, -1, "i" );
}

void MessageBar::render( float dt )  {
	float ease;
	if( in ) {
		if( doAnimateIn ) {
			t += dt;
			if( t < inTime - 0.1f ) {
				ease = EaseOutQuad( t, inTime );
				xIcon = outXIcon + (int) ( ( inX - outXIcon ) * ease );
				xBar = outXBar + (int) ( ( inX - outXBar ) * ease );
			} else {
				doAnimateIn = false;
				xIcon = inX;
				xBar = inX;
			}
		} else if( doAnimateOut ) {
			t += dt;
			if( t < outTime - 0.1f ) {
				ease = 1 - EaseOutQuad( t, inTime );
				xIcon = outXIcon + (int) ( ( inX - outXIcon ) *  ease );
				xBar = outXBar + (int) ( ( inX - outXBar ) *  ease );
			} else {
				doAnimateOut = false;
				in = false;
				if( shouldAnimateIn )
					animateIn( message );
			}
		} else {
			xIcon = inX;
			xBar = inX;
		}

		y = SCREEN_H - height;

		draw();
	}
}

void MessageBar::animateIn( std::string msg, bool force ) {
	if( !in || force ) {
		t = 0;
		doAnimateIn = true;
		doAnimateOut = false;
		shouldAnimateIn = false;
		in = true;
	} else {
		shouldAnimateIn = true;
	}
	message = msg;
}

void MessageBar::animateOut() {
	if( in ) {
		t = 0;
		doAnimateIn = false;
		doAnimateOut = true;
		shouldAnimateIn = false;
	}
}

ErrorBar::ErrorBar() {}

ErrorBar::ErrorBar( BITMAP* page, FONT* font, MessageBar* infoBar ) : MessageBar( page, font ), infoBar( infoBar ) {}

void ErrorBar::render( float dt ) {
	float ease;
	if( in ) {
		diff = next - clock();
		if( doAnimateIn ) {
			t += dt;
			if( t < inTime - 0.1f ) {
				ease = EaseOutQuad( t, inTime );
				xIcon = outXIcon + (int) ( ( inX - outXIcon ) * ease );
				xBar = outXBar + (int) ( ( inX - outXBar ) * ease );
			} else {
				doAnimateIn = false;
				xIcon = inX;
				xBar = inX;
			}
		} else if( doAnimateOut ) {
			t += dt;
			if( t < outTime - 0.1f ) {
				ease = 1 - EaseOutQuad( t, inTime );
				xIcon = outXIcon + (int) ( ( inX - outXIcon ) *  ease );
				xBar = outXBar + (int) ( ( inX - outXBar ) *  ease );
			} else {
				doAnimateOut = false;
				in = false;
				if( shouldAnimateIn )
					animateIn( message );
			}
		} else {
			xIcon = inX;
			xBar = inX;

			if( diff < 0 ) {
				animateOut();
			}
		}

		y = SCREEN_H - height;

		if( infoBar->in )
			y -= infoBar->height;

		draw();
	}
}

void ErrorBar::draw() {
	rectfill( page, xBar, y, xBar + widthBar, y + height, colorBarBackNoTime );
	rectfill( page, xBar, y, (int) ( ( xBar + widthBar ) * (float) diff / stayTime ), y + height, colorBarBack );
	textprintf_ex( page, font, xBar + widthIcon + marginX, y + marginY, colorBarFront, -1, "%s", message.c_str() );
	rectfill( page, xIcon, y, xIcon + widthIcon, y + height, colorIconBack );
	textprintf_ex( page, font, xIcon + marginXIcon, y + marginYIcon, colorIconFront, -1, "!" );
}

void ErrorBar::animateIn( std::string msg, bool force ) {
	before = clock();
	next = before + stayTime;
	MessageBar::animateIn( msg, force );
}

Allegro::Allegro( Othello::Board::GameBoard& oboard, const Othello::Board::punArray board, const std::vector<Othello::Players::Player*>& players, std::vector<Othello::Players::Player*>::iterator& currentPlayer, Othello::UI::Audio::FMOD& fmod ) : Game( board, players, currentPlayer ), m_io( ImGui::GetIO() ), m_oboard( oboard ), m_fmod( fmod ) {
	loadSprites();
	loadBackgrounds();
	loadFonts();
	loadIMGUIStyle();

	m_fmod.playMusic( "main1" );

	m_page = create_bitmap( SCREEN_W, SCREEN_H );

	m_treeViewer = AllegroValidMoveTreeViewer( &m_tree, 5, m_page );

	infoBar = MessageBar( m_page, m_textFont );
	errorBar = ErrorBar( m_page, m_textFont, &infoBar );
}

void Allegro::freeBitmaps() {
	for( auto bmp = m_bitmaps.begin(); bmp != m_bitmaps.end(); bmp++ ) {
		if( bmp->second != nullptr ) {
			destroy_bitmap( bmp->second );
			bmp->second = nullptr;
		}
	}
}

Allegro::~Allegro() {
	m_fmod.stopMusic();
	freeBitmaps();
}

void Allegro::loadSprites() {
	std::string path;
	BITMAP* bmp;
	std::vector<std::string> bmpNames = {
			"punWhite",
			"punBlack",
			"case",
			"caseInv",
			"youWin"
	};

	for( const auto& bmpName : bmpNames ) {
		path = "images/";
		path += bmpName;
		path += ".png";

		bmp = load_png( path.c_str(), NULL );
		if( bmp ) {
			m_bitmaps.insert( std::make_pair( bmpName, bmp ) );
		} else {
			path = "File not found: ";
			path = "images/";
			path += bmpName;
			path += ".png";
			throw std::ios_base::failure( path );
		}
	}

	m_cursor = load_png( "images/cursor.png", NULL );
}

void Allegro::loadBackgrounds() {
	std::string path;
	BITMAP* bmp;
	std::vector<std::string> bmpNames = {
			"mainBg",
			"gameBg"
	};

	for( const auto& bmpName : bmpNames ) {
		path = "images/";
		path += bmpName;
		path += ".jpg";

		bmp = load_jpg( path.c_str(), NULL );
		if( bmp ) {
			m_bitmaps.insert( std::make_pair( bmpName, bmp ) );
		} else {
			path = "File not found: ";
			path = "images/";
			path += bmpName;
			path += ".jpg";
			throw std::ios_base::failure( path );
		}
	}
}

void Allegro::loadFonts() {
	m_textFont = load_font( "fonts/droidsans_14_mono.pcx", NULL, NULL );
	if( !m_textFont ) {
		throw std::ios_base::failure( "File not found: fonts/droidsans_14_mono.pcx" );
	}
	m_glTextFont = allegro_gl_load_system_font( (char*) "Arial", AGL_FONT_STYLE_ANTI_ALIASED, 16, 14 );
	ImGui::GetIO().Fonts->AddFontFromFileTTF( "fonts/DroidSans.ttf", 16.0f );
	ImGui::GetIO().Fonts->AddFontFromFileTTF( "fonts/DroidSans.ttf", 32.0f );
	ImGui::GetIO().FontDefault = ImGui::GetIO().Fonts->Fonts[ FONT_SIZE_16 ];
}

void Allegro::loadIMGUIStyle() {
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ ImGuiCol_Text ]                  = ImVec4( 1.00f, 1.00f, 1.00f, 1.00f );
	style.Colors[ ImGuiCol_WindowBg ]              = ImVec4( 0.15f, 0.20f, 0.29f, 0.94f );
	style.Colors[ ImGuiCol_Button ]                = ImVec4( 0.90f, 0.51f, 0.35f, 0.84f );
	style.Colors[ ImGuiCol_ButtonHovered ]         = ImVec4( 1.00f, 0.55f, 0.31f, 0.93f );
	style.Colors[ ImGuiCol_ButtonActive ]          = ImVec4( 1.00f, 0.71f, 0.50f, 1.00f );
	ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, 0.0f );
}

BITMAP* Allegro::getPunSprite( Othello::Board::Pun::Colors color ) const {
	switch( color ) {
		case Pun::black:
			return m_bitmaps.find( "punBlack" )->second;
		case Pun::white:
			return m_bitmaps.find( "punWhite" )->second;
		default:
			return nullptr;
	}
}

void Allegro::displayMatrix() {
	BITMAP* sprite;
	Pun::Colors piece;
	int x, y, pos_x = 0, pos_y = 0, rw, rh;
	bool inv = false;
	BITMAP *caseNormal = m_bitmaps.find( "case" )->second;
	BITMAP *caseInv = m_bitmaps.find( "caseInv" )->second;

	rw = (unsigned int) m_bitmaps.find( "case" )->second->w;
	rh = (unsigned int) m_bitmaps.find( "case" )->second->h;
	pos_x = ( SCREEN_W - Board::sizeEdge * rw ) / 2;
	pos_y = ( SCREEN_H - Board::sizeEdge * rh ) / 2;

	for( unsigned int j = 0; j < Board::sizeEdge; j++ ) { //browse
		for( unsigned int i = 0; i < Board::sizeEdge; i++ ) {
			piece = m_board[ i ][ j ];
			if( inv ) {
				draw_sprite( m_page, caseInv, pos_x + i * caseInv->w, pos_y + j * caseInv->h );
			} else {
				draw_sprite( m_page, caseNormal, pos_x + i * caseNormal->w, pos_y + j * caseNormal->h );
			}
			inv ^= true;

			if( piece != Pun::blank ) {
				sprite = getPunSprite( piece );
				x = pos_x + i * rw + ( rw - sprite->w ) / 2;
				y = pos_y + j * rh + ( rh - sprite->h ) / 2;
				draw_trans_sprite( m_page, sprite, x, y );
			}
		}
		inv ^= true;
	}

	for( const ValidMove& validMove : m_oboard.getValidMoves() ) {
		set_trans_blender( 0, 0, 0, COLOR_VALIDMOVE_BLENDFACTOR );
		drawing_mode( DRAW_MODE_TRANS, NULL, 0, 0 );
		rectfill( m_page, pos_x + validMove.x * rw, pos_y + validMove.y * rh, pos_x + validMove.x * rw + rw, pos_y + validMove.y * rh + rh, COLOR_VALIDMOVE );
		drawing_mode( DRAW_MODE_SOLID, NULL, 0, 0 );

		set_alpha_blender();
	}
}

void Allegro::displayPlayers() {
	int pos_x = 0;

	if( m_currentPlayer == m_players.begin() ) {
		rectfill( m_page, 0, 0, SCREEN_W / 2, m_textFont->height + 2 * PLAYER_NAME_PADDING_H, COLOR_ACTIVE_PLAYER );
		rectfill( m_page, SCREEN_W / 2, 0, SCREEN_W, m_textFont->height + 2 * PLAYER_NAME_PADDING_H, COLOR_INACTIVE_PLAYER );

	} else {
		rectfill( m_page, 0, 0, SCREEN_W / 2, m_textFont->height + 2 * PLAYER_NAME_PADDING_H, COLOR_INACTIVE_PLAYER );
		rectfill( m_page, SCREEN_W / 2, 0, SCREEN_W, m_textFont->height + 2 * PLAYER_NAME_PADDING_H, COLOR_ACTIVE_PLAYER );
	}

	for( unsigned int i = 0; i < m_players.size(); i++ ) {
		pos_x = ( !( i % 2 ) ? 0 : SCREEN_W / 2 );
		textprintf_ex( m_page, m_textFont, pos_x + PLAYER_NAME_PADDING_W, PLAYER_NAME_PADDING_H, makecol( 255, 255, 255 ), -1, "%s", m_players[ i ]->getName().c_str() );
		textprintf_ex( m_page, m_textFont, SCREEN_W / 2 + pos_x - PLAYER_SCORE_WIDTH_X - PLAYER_NAME_PADDING_W, PLAYER_NAME_PADDING_H, makecol( 255, 255, 255 ), -1, "%d", m_oboard.punCount( m_players[ i ]->getColor() ) );
	}
}

void Allegro::displayBackground() {
	stretch_blit( m_bitmaps.find( "gameBg" )->second, m_page, 0, 0, m_bitmaps.find( "gameBg" )->second->w, m_bitmaps.find( "gameBg" )->second->h, 0, 0, SCREEN_W, SCREEN_H );
}

void Allegro::display() {
	displayBackground();

	set_alpha_blender();

	displayMatrix();
	displayPlayers();

	set_trans_blender( 255, 0, 255, 0 );
}

void Allegro::updateInputs() {
	prevKeyEsc = keyEsc;
	keyEsc = (bool) key[ KEY_ESC ];
	prevKeyG = keyG;
	keyG = (bool) key[ KEY_G ];

	if( !prevKeyEsc && keyEsc ) {
		if( m_treeViewer.opened ) {
			m_treeViewer.opened = false;
		} else {
			m_pause ^= true;
		}
	}

	if( !prevKeyG && keyG ) {
		m_treeViewer.opened ^= true;
	}
}

void Allegro::highlightSelectedPiece( unsigned int x, unsigned int y, int color ) {
	unsigned int rw, rh, posx, posy;
	if( x < Board::sizeEdge && y < Board::sizeEdge ) {
		rw = (unsigned int) m_bitmaps.find( "case" )->second->w;
		rh = (unsigned int) m_bitmaps.find( "case" )->second->h;
		posx = ( SCREEN_W - Board::sizeEdge * rw ) / 2;
		posy = ( SCREEN_H - Board::sizeEdge * rh ) / 2;

		set_trans_blender( 0, 0, 0, COLOR_SELECTION_BLENDFACTOR );

		drawing_mode( DRAW_MODE_TRANS, NULL, 0, 0 );
		rectfill( m_page, posx + x * rw, posy + y * rh, posx + x * rw + rw, posy + y * rh + rh, color );
		drawing_mode( DRAW_MODE_SOLID, NULL, 0, 0 );

		set_alpha_blender();
	}
}

Othello::Board::Move Allegro::getMove() {
	int mx, my;
	unsigned int rw, rh, posx, posy;

	if( !m_pause && !m_treeViewer.opened ) {
		x = 0;
		y = 0;
		m_getMove = true;

		rw = ( unsigned int ) m_bitmaps.find( "case" )->second->w;
		rh = ( unsigned int ) m_bitmaps.find( "case" )->second->h;
		posx = ( SCREEN_W - Board::sizeEdge * rw ) / 2;
		posy = ( SCREEN_H - Board::sizeEdge * rh ) / 2;

		mx = ( mouse_x - posx ) / rw;
		my = ( mouse_y - posy ) / rh;

		if( mx >= 0 && my >= 0 && ( unsigned ) mx < Board::sizeEdge && ( unsigned ) my < Board::sizeEdge ) {
			x = ( unsigned char ) mx;
			y = ( unsigned char ) my;

			if( ImGui::IsMouseReleased( 0 ) ) {
				m_getMove = false;
				return Move( x, y );
			}
		}
	}

	throw exceptions::no_selected_move();
}

void Allegro::playerTurnBegin( Player* player ) {
	render();
}

void Allegro::playerTurnEnd( Player* player ) {

}

void Allegro::gameDisplay() {
	allegro_gl_set_allegro_mode();
	if( !m_treeViewer.opened ) {
		display();
		infoBar.render( dt );
		errorBar.render( dt );
		if( m_pause ) {
			renderPause();
		} else {
			if( m_getMove ) {
				highlightSelectedPiece( x, y, COLOR_SELECTION );
			}
			blit( m_page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );
			allegro_gl_unset_allegro_mode();
		}
	} else {
		displayBackground();
		m_treeViewer.render();
		blit( m_page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );
		allegro_gl_unset_allegro_mode();
	}
}

void Allegro::renderMouse() {
	allegro_gl_set_allegro_mode();
	set_alpha_blender();
	draw_trans_sprite( screen, m_cursor, mouse_x, mouse_y );
	allegro_gl_unset_allegro_mode();
}

void Allegro::render() {
	newFrame( false );
	updateInputs();
	gameDisplay();
	endFrame();
}

void Allegro::victory( Player* player ) {
	m_fmod.stopMusic();

	bool mouseL = false;
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	allegro_gl_set_allegro_mode();
	stretch_blit( m_bitmaps.find( "mainBg" )->second, m_page, 0, 0, m_bitmaps.find( "mainBg" )->second->w, m_bitmaps.find( "mainBg" )->second->h, 0, 0, SCREEN_W, SCREEN_H);
	set_alpha_blender();
	draw_trans_sprite( m_page, m_bitmaps.find( "youWin" )->second, ( SCREEN_W - m_bitmaps.find( "youWin" )->second->w ) / 2, VICTORY_PADDING );
	textprintf_centre_ex( m_page, m_textFont, SCREEN_W / 2, SCREEN_H / 2, makecol( 255, 255, 255 ), -1, "Bravo %s ! Tu as gagne !", player->getName().c_str() );
	blit( m_page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );
	allegro_gl_unset_allegro_mode();
	endFrame();

	m_fmod.playSoundWait( "victory" );
	m_fmod.playMusic( "victory" );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	allegro_gl_set_allegro_mode();
	textprintf_centre_ex( m_page, m_textFont, SCREEN_W / 2, SCREEN_H - m_textFont->height - VICTORY_PADDING, makecol( 255, 255, 255 ), -1, "Continuer >" );
	blit( m_page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );
	allegro_gl_unset_allegro_mode();
	endFrame();

	before = clock() - 1;
	for( bool loop = true; loop; ) {
		if( mouseL )
			loop = false;
		mouseL = (bool) ( mouse_b & 1 );
	}

	m_fmod.stopMusic();
}

void Allegro::newFrame( bool skipDT ) {
	if( !skipDT ) {
		COMPUTE_DT( dt )
		ImGui_ImplAGL_NewFrame( dt );
		before = clock();
	} else {
		ImGui_ImplAGL_NewFrame( 1 / 30.0f );
	}
	m_fmod.update();
	if( m_forceQuit )
		throw exceptions::exit_game();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void Allegro::endFrame() {
	renderMouse();
	glFlush();
	allegro_gl_flip();
}

void Allegro::inform( std::string msg ) {
	infoBar.animateOut();
	infoBar.animateIn( msg );
}

void Allegro::renderPause() {
	float button_x;
	set_trans_blender( 0, 0, 0, PAUSE_BLENDING_FACTOR );

	drawing_mode( DRAW_MODE_TRANS, NULL, 0, 0 );
	rectfill( m_page, 0, 0, m_page->w, m_page->h, makecol( 0, 0, 0 ) );
	drawing_mode( DRAW_MODE_SOLID, NULL, 0, 0 );

	set_alpha_blender();

	blit( m_page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );
	allegro_gl_unset_allegro_mode();

	//ImGui::GetIO().FontDefault = ImGui::GetIO().Fonts->Fonts[ FONT_SIZE_32 ];

	ImGui::SetNextWindowSize( ImVec2( SCREEN_W, PAUSE_HEIGHT ), ImGuiSetCond_Appearing );
	ImGui::SetNextWindowPosCenter();
	ImGui::Begin( "", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar );
	button_x  = ( ImGui::GetWindowWidth() - PAUSE_BUTTON_WIDTH ) / 2;
	ImGui::SetCursorPosX( ( ImGui::GetWindowWidth() - ImGui::CalcTextSize( "PAUSE" ).x ) / 2 );
	ImGui::Text( "PAUSE" );
	ImGui::SetCursorPosX( button_x );
	if( ImGui::Button( "CONTINUER", ImVec2( PAUSE_BUTTON_WIDTH, PAUSE_BUTTON_HEIGHT ) ) ) {
		m_pause = false;
		ImGui::GetIO().MouseReleased[ 0 ] = false;
	}
	ImGui::SetCursorPosX( button_x );
	if( ImGui::Button( "GRAPHE", ImVec2( PAUSE_BUTTON_WIDTH, PAUSE_BUTTON_HEIGHT ) ) ) {
		m_pause = false;
		m_treeViewer.opened = true;
		ImGui::GetIO().MouseReleased[ 0 ] = false;
	}
	ImGui::SetCursorPosX( button_x );
	if( ImGui::Button( "QUITTER", ImVec2( PAUSE_BUTTON_WIDTH, PAUSE_BUTTON_HEIGHT ) ) ) {
		throw exceptions::exit_game();
	}
	ImGui::End();

	ImGui::Render();
	//ImGui::GetIO().FontDefault = ImGui::GetIO().Fonts->Fonts[ FONT_SIZE_16 ];
}

void Allegro::informNoAvailableMoves( Othello::Players::Player* player ) {
	showError( "Aucun coup disponible pour " + player->getName() + " !" );
}

void Allegro::showError( std::string msg ) {
	errorBar.animateIn( msg );
}

void Allegro::forceQuit() {
	m_forceQuit = true;
}