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
	#include <chrono>
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
				/**
				 * @brief Fonction d'animation implémentant une fonction Ease-Out
				 * @param t Temps actuel
				 * @param maxt Temps maximal
				 * @return Valeur d'animation
				 */
				float EaseOutQuad( float t, float maxt );

				class ErrorBar;

				/**
				 * @class MessageBar
				 * @brief Barre de message graphique
				 */
				class MessageBar {
						friend class ErrorBar;

					protected:
						double t = 0;
						bool in = false, doAnimateIn = false, doAnimateOut = false, shouldAnimateIn = false;
						int xIcon, xBar, y;
						BITMAP* page;
						FONT* font;
						std::string message;

						constexpr static int widthIcon = 20, outXIcon = -16, inX = 0, height = 22, marginX = 4, marginY = 2, marginXIcon = 8, marginYIcon = 2;
						int colorBarFront = makecol( 0, 0, 0 ), colorBarBack = makecol( 200, 200,
						                                                                200 ), colorIconFront = colorBarBack, colorIconBack = colorBarFront, widthBar = SCREEN_W, outXBar = -SCREEN_W;
						double inTime = 0.5, outTime = 0.5;

						/**
						 * @brief Afficheur de barre réel
						 */
						virtual void draw();

					public:
						/**
						 * @brief Constructeur par défaut
						 * @details Permet d'avoir un objet résidant sans pour autant fournir les arguments
						 */
						MessageBar();
						/**
						 * @brief Constructeur
						 * @param page Bitmap sur laquelle afficher
						 * @param font Police à utiliser
						 */
						MessageBar( BITMAP* page, FONT* font );

						/**
						 * @brief Afficheur de barre
						 * @param dt Temps entre cette frame et la frame précédente
						 */
						virtual void render( double dt );

						/**
						 * @brief Animateur d'entrée
						 * @details A appeler une fois pour animer l'entrée de la barre.
						 * @param msg Message à afficher
						 * @param force Forçage de l'apparition
						 */
						virtual void animateIn( std::string msg, bool force = false );

						/**
						 * @brief Animateur de sortie
						 * @details A appeler pour cacher la barre.
						 */
						void animateOut();
				};

				/**
				 * @class ErrorBar
				 * @brief Barre de message d'erreur graphique
				 */
				class ErrorBar : public MessageBar {
					private:
						MessageBar* infoBar;

						constexpr static std::chrono::seconds stayTime = std::chrono::seconds( 4 );
						std::chrono::time_point<std::chrono::high_resolution_clock> before, next;
						double diff;
						int colorBarFront = makecol( 255, 255, 255 ), colorBarBack = makecol( 190, 0, 0 ), colorIconFront = makecol( 255, 255, 255 ), colorIconBack = makecol( 100, 0, 0 ), colorBarBackNoTime = makecol( 170, 0, 0 );

						/**
						 * @brief Afficheur de barre réel
						 */
						void draw();

					public:
						/**
						 * @brief Constructeur par défaut
						 * @details Permet d'avoir un objet résidant sans pour autant fournir les arguments
						 */
						ErrorBar();

						/**
						 * @brief Constructeur
						 * @param page Bitmap sur laquelle afficher
						 * @param font Police à utiliser
						 * @param infoBar Barre à prendre en compte lors de l'affichage
						 */
						ErrorBar( BITMAP* page, FONT* font, MessageBar* infoBar );

						/**
						 * @brief Animateur d'entrée
						 * @details A appeler une fois pour animer l'entrée de la barre.
						 * @param msg Message à afficher
						 * @param force Forçage de l'apparition
						 */
						void animateIn( std::string msg, bool force = false );

						/**
						 * @brief Afficheur de barre
						 * @param dt Temps entre cette frame et la frame précédente
						 */
						void render( double dt );
				};

				/**
				 * @class Allegro
				 * @brief Interface de jeu graphique
				 */
				class Allegro : public Othello::UI::Game {
					private:
						std::unordered_map<std::string, BITMAP*> m_bitmaps;
						BITMAP* m_page, *m_cursor;
						FONT* m_textFont, * m_glTextFont;
						ImGuiIO& m_io;
						bool prevKeyEsc = false, keyEsc = false, prevKeyG = false, keyG = false;
						unsigned char x = 0, y = 0;
						double dt;
						std::chrono::time_point<std::chrono::high_resolution_clock> before;
						Othello::Board::GameBoard& m_oboard;
						MessageBar infoBar;
						ErrorBar errorBar;
						AllegroValidMoveTreeViewer m_treeViewer;
						bool m_pause = false, m_getMove = false;
						Othello::UI::Audio::FMOD& m_fmod;
						bool m_forceQuit = false;

						/**
						 * @brief Chargeur de sprites
						 */
						void loadSprites();

						/**
						 * @brief Chargeur de police
						 * @details Charge pour Allegro et ImGui.
						 */
						void loadFonts();

						/**
						 * @brief Chargeur de fond
						 */
						void loadBackgrounds();

						/**
						 * @brief Chargeur de style de fenêtre ImGui
						 */
						void loadIMGUIStyle();

						/**
						 * @brief Afficheur d'interface purement Allegro (pas AllegroGL)
						 */
						void display();

						/**
						 * @breif Afficheur de fond
						 */
						void displayBackground();

						/**
						 * @brief Afficheur de plateau
						 */
						void displayMatrix();

						/**
						 * @brief Afficheur de joueurs
						 */
						void displayPlayers();

						/**
						 * @brief	Met en valeur une pièce
						 * @details	Permet de mettre en valeur un emplacement du plateau aux coordonnées indiquées, avec la couleur fournie.
						 * @param[in] x Coordonnée en abscisse de l'emplacement
						 * @param[in] y Coordonnée en ordonnée de l'emplacement
						 * @param[in] color Couleur de surimpression
						 */
						void highlightSelectedPiece( unsigned int x, unsigned int y, int color = COLOR_SELECTION );

						/**
						 * @brief Gestionnaire d'entrées
						 * @details Met à jour les entrées clavier pour l'interface propre au jeu.
						 */
						void updateInputs();

						/**
						 * @brief Afficheur de menu pause, s'il est ouvert
						 */
						void renderPause();

						/**
						 * @brief Libérateur de mémoire des bitmaps
						 */
						void freeBitmaps();

						/**
						 * @brief Accesseur de sprite de pion
						 * @details Donne la sprite associé à la couleur d'un pion.
						 * @param color Couleur
						 * @return Sprite
						 */
						BITMAP* getPunSprite( Othello::Board::Pun::Colors color ) const;

						/**
						 * @brief Initiateur de nouvelle frame
						 * @param skipDT Ne pas faire le calcul du temps entre cette frame et la frame précédente
						 */
						void newFrame( bool skipDT = false );

						/**
						 * @brief Termineur de frame
						 */
						void endFrame();

						/**
						 * @brief Afficheur de jeu
						 */
						void gameDisplay();

						/**
						 * @brief Calcul l'intervalle de temps entre deux frames
						 */
						double inline computeDt();

					public:
						/**
						 * @brief Constructeur
						 * @param oboard Objet #GameBoard originel
						 * @param board Plateau de jeu
						 * @param players Référence vers la liste des joueurs
						 * @param currentPlayer Référence vers le joueur actuel
						 * @param fmod Référence vers un objet de gestion #FMOD
						 */
						Allegro( Othello::Board::GameBoard& oboard, const Othello::Board::punArray board, const std::vector<Othello::Players::Player*>& players, std::vector<Othello::Players::Player*>::iterator& currentPlayer, Othello::UI::Audio::FMOD& fmod );

						/**
						 * @brief Destructeur
						 */
						~Allegro();

						/**
						 * @brief Affichage d'une erreur
						 * @details Informe l'utilisateur d'une erreur au sein du programme. Bloque le programme en attendant une action de l'utilisateur.
						 * @param msg Message d'erreur
						 */
						void showError( std::string msg );

						/**
						 * @brief	Évènement début de tour
						 * @details	Fonction appelée au début du tour d'un joueur, avant toute chose.
						 * @param[in] player Joueur actuel
						 */
						void playerTurnBegin( Othello::Players::Player* player );

						/**
						 * @brief	Évènement fin de tour
						 * @details	Fonction appelée à la fin du tour d'un joueur, après toutes ses actions.
						 * @param[in] player Joueur actuel
						 */
						void playerTurnEnd( Othello::Players::Player* player );

						/**
						 * @brief	Écran de victoire
						 * @details	Affiche un écran de victoire pour le joueur gagnant.
						 * @param[in] player Joueur gagnant
						 */
						void victory( Othello::Players::Player* player );

						/**
						 * @brief	Évènement demande de coup
						 * @details	Fonction appelée lorsque le jeu a besoin du coup voulu par le joueur humain. Lâche une exception #no_selected_move si le coup n'est pas sélectionné.
						 * @return	Coup joué/demandé par le joueur
						 */
						Othello::Board::Move getMove();

						/**
						 * @brief Affichage d'un message d'information
						 * @details Informe l'utilisateur d'une erreur au sein du programme. Non bloquant.
						 * @param msg Message d'erreur
						 */
						void inform( std::string msg );

						/**
						 * @brief Informer qu'un joueur ne peut pas jouer
						 * @param player Joueur qui ne peut pas jouer
						 */
						void informNoAvailableMoves( Othello::Players::Player* player );

						/**
						 * @brief	Demandeur de rendue
						 * @details	Demande à l'interface de procéder à ses fonctions.
						 */
						void render();

						/**
						 * @brief Afficheur de curseur de souris
						 */
						void renderMouse();

						/**
						 * @brief Forceur de fermeture de l'interface
						 */
						void forceQuit();
				};
			}
		}
	}

#endif //ECE_OTHELLO_UI_GAMES_ALLEGRO_HPP
