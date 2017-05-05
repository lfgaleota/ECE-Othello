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
			 * @namespace Main
			 * @details Espace de nommage des interfaces du menu.
			 */
			namespace Main {
				/**
				 * @brief Fonction d'animation implémentant une fonction Ease-Out
				 * @param t Temps actuel
				 * @param maxt Temps maximal
				 * @return Valeur d'animation
				 */
				float EaseOutQuad( float t, float maxt );

				/**
				 * @brief Chargeur de texture AllegroGL
				 * @param texture Référence vers le GLuint qui recevra la texture
				 * @param path Chemi nde la texture
				 * @return Succès ou non du chargement
				 */
				bool AGL_loadTexture( GLuint& texture, std::string path );

				/**
				 * @brief Projeteur de coordonnée fenêtre en coordonnées OpenGL
				 * @details Permet de récupérer les coordonnées dans la projection 3D du curseur par projection d'un rayon
				 * @param x Coordonnée en abscisse du curseur
				 * @param y Coordonnée en ordonnée du curseur
				 * @param retx Coordonnée en abscisse du rayon
				 * @param rety Coordonnée en ordonnée du rayon
				 * @param retz Coordonnée en profondeur du rayon
				 */
				void GL_windowToObjectf( GLfloat x, GLfloat y, GLdouble* retx, GLdouble* rety, GLdouble* retz );

				/**
				 * @class AnimatedRectangle
				 * @brief Rectangle animé
				 * @details Gère un rectangle dont les effets d'entrée et surimpression sont animés. Utilisez pour tous les rectangles animés du menu.
				 */
				class AnimatedRectangle {
					protected:
						float t = 0;
						float& dt;
						GLuint texture;
						bool show = false, hoverIn = false, hoverOut = true, doAnimateEntry = false, doAnimateHoverIn = false, doAnimateHoverOut = false, sound = false;
						constexpr static float defaultEntryRY = -60.0f, defaultEntryTime = 15.0f, defaultNormalX = 1.0f, defaultHoverX = 1.0f, defaultHoverZ = 0.5f, defaultHoverTime = 10.0f, defaultClickZ = -defaultHoverZ;
						float entryRY = defaultEntryRY, entryTime = defaultEntryTime, normalX = defaultNormalX, hoverX = defaultHoverX, hoverZ = defaultHoverZ, hoverTime = defaultHoverTime, clickZ = defaultClickZ;
						Othello::UI::Audio::FMOD& m_fmod;

						/**
						 * @brief Joueur de son lors d'une surimpression
						 */
						virtual void playHover();

						/**
						 * @brief Afficheur de la ligne de surimpression
						 */
						virtual void drawOutline();

						/**
						 * @brief Afficheur réel du rectangle
						 */
						virtual void drawReal();

					public:
						bool clicked = false;

						/**
						 * @brief Constructeur
						 * @param dt Référence vers le temps entre cette frame et la frame précédente
						 * @param fmod Référence vers un objet de gestion #FMOD
						 */
						AnimatedRectangle( float& dt, Othello::UI::Audio::FMOD& fmod );

						/**
						 * @brief Chargeur de texture du rectangle
						 * @param path Chemin de la texture
						 * @return Succès ou non du chargement
						 */
						bool loadTexture( std::string path );

						/**
						 * @brief Afficheur du rectangle
						 */
						void draw();

						/**
						 * @brief Animateur d'entrée
						 */
						void animateEntry();

						/**
						 * @brief Animateur de surimpression
						 */
						void animateHoverIn();

						/**
						 * @brief Animateur de sortie de surimpression
						 */
						void animateHoverOut();

						/**
						 * @brief Forçage de l'entrée sans animation
						 */
						void entry();

						/**
						 * @brief Réinitialisateur d'état du rectangle
						 */
						void reset();
				};

				/**
				 * @class MenuRectangle
				 * @brief Rectangle animé servant de bouton sur le menu principal
				 */
				class MenuRectangle : public AnimatedRectangle {
					private:
						GLuint backTexture;

						/**
						 * @brief Joueur de son lors d'une surimpression
						 */
						virtual void playHover();

						/**
						 * @brief Afficheur de la ligne de surimpression
						 */
						virtual void drawOutline();

						/**
						 * @brief Afficheur réel du rectangle
						 */
						virtual void drawReal();

					public:
						/**
						 * @brief Constructeur
						 * @param dt Référence vers le temps entre cette frame et la frame précédente
						 * @param fmod Référence vers un objet de gestion #FMOD
						 */
						MenuRectangle( float& dt, Othello::UI::Audio::FMOD& fmod );

						/**
						 * @brief Chargeur de texture d'arrière-plan du rectangle
						 * @param path Chemin de la texture
						 * @return Succès ou non du chargement
						 */
						bool loadBackTexture( std::string path );
				};

				/**
				 * @class ButtonRectangle
				 * @brief Rectangle animé bouton
				 */
				class ButtonRectangle : public AnimatedRectangle {
					private:
						/**
						 * @brief Joueur de son lors d'une surimpression
						 */
						virtual void playHover();

						/**
						 * @brief Afficheur de la ligne de surimpression
						 */
						virtual void drawOutline();

						/**
						 * @brief Afficheur réel du rectangle
						 */
						virtual void drawReal();

					public:
						/**
						 * @brief Constructeur
						 * @param dt Référence vers le temps entre cette frame et la frame précédente
						 * @param fmod Référence vers un objet de gestion #FMOD
						 */
						ButtonRectangle( float& dt, Othello::UI::Audio::FMOD& fmod );
				};

				/**
				 * @class Allegro
				 * @brief Interface du menu graphique
				 */
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
						float m_volume = 100;
						bool isSave = false, m_soundActivated = true;
						static const std::string configPath;

						/**
						 * @enum Stage
						 * @brief Page actuelle du menu
						 */
						enum Stage {
							Menu, /*!< Menu principal */
							Options, /*!< Menu d'options */
							Quit, /*!< Confirmation pour quitter */
							ContinueParty, /*!< Jeu / Contineur une partie */
							New, /*!< Menu de nouvelle partie */
							NewPlayer, /*!< Invité de nouvelle partie PVP */
							NewPlayerParty, /*!< Jeu / Nouvelle partie PVP */
							NewAISelect, /*!< Menu de sélection d'IA */
							NewAI, /*!< Invité de nouvelle partie PVAI */
							NewAIParty /*!< Jeu / Nouvelle partie PVAI */
						};

						Stage stage = Stage::Menu;

						/**
						 * @brief Initialisateur d'Allegro
						 */
						void initAllegro();

						/**
						 * @brief Initialisateur d'AllegroGL et OpenGL
						 */
						void initGL();

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
						 * @brief Initialisateur des rectangles animés
						 */
						void loadRectangles();

						/**
						 * @brief Chargeur de configuration
						 */
						void loadConfig();

						/**
						 * @brief Enregistreur de configuration
						 */
						void saveConfig();

						/**
						 * @brief Gestionnaire d'entrées
						 * @details Met à jour les entrées clavier pour l'interface propre au jeu.
						 */
						void updateInputs();
						/**
						 * @brief Gestionnaire de sourie
						 * @details Met à jour les informatiosnde la sourie pour les rectangles animés
						 */
						void handleMouse();
						/**
						 * @brief Afficheur de scène
						 * @details Affiche tout ce qui doit être affiché en fonction de l'état du menu.
						 */
						void renderScene();
						/**
						 * @brief Afficheur de menu principal, s'il le faut
						 */
						void renderMenu();
						/**
						 * @brief Afficheur de menu des options, s'il le faut
						 */
						void renderOptions();
						/**
						 * @brief Afficheur d'invité pour quitter, s'il le faut
						 */
						void renderQuit();
						/**
						 * @brief Afficheur de menu de nouvelle partie, s'il le faut
						 */
						void renderNew();
						/**
						 * @brief Afficheur d'invité de nouvelle partie PVP, s'il le faut
						 */
						void renderNewPlayer();
						/**
						 * @brief Afficheur de menu de sélection d'IA, s'il le faut
						 */
						void renderNewAISelect();
						/**
						 * @brief Afficheur d'invité de nouvelle partie PVAI, s'il le faut
						 */
						void renderNewAI();
						/**
						 * @brief Afficheur d'arrièer plan des invités, s'il le faut
						 */
						void renderModalShadow();
						/**
						 * @brief Afficheur de bouton de retour, s'il le faut
						 */
						void renderCancelButton();
						/**
						 * @brief Initiateur de nouvelle frame
						 */
						void newFrame();
						/**
						 * @brief Termineur de frame
						 */
						void endFrame();
						/**
						 * @brief Afficheur d'élément Allegro
						 */
						void display();
						/**
						 * @brief Boucle de menu
						 */
						void menu();
						/**
						 * @brief Retour à la page précédente
						 */
						void back();
						/**
						 * @brief Passage à la page suivante
						 * @param newStage Page vers laquelle aller
						 */
						void forward( Stage newStage );

						/**
						 * @brief Joueur de partie
						 * @details En fonction de l'état du menu, démarre une partie selon les critères définis
						 */
						void redirectGame();
						/**
						 * @brief Continueur de partie
						 */
						void loadGame();
						/**
						 * @brief Initiateur de partie PVP
						 */
						void newPlayerGame();
						/**
						 * @brief Initiateur de partie PVAI
						 */
						void newAIGame();

						/**
						 * @brief Afficheur d'erreur
						 * @param message Message d'erreur
						 */
						void error( std::string message );

						/**
						 * @brief Libérateur de mémoire des bitmaps
						 */
						void freeBitmaps();
					public:
						/**
						 * @brief Constructeur
						 * @param fmod Référence vers un objet de gestion #FMOD
						 */
						Allegro( Othello::UI::Audio::FMOD& fmod );
				};
			}
		}
	}

#endif
