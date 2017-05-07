#ifndef _ECE_OTHELLO_SAVE_SAVEMANAGER_HPP_
	#define _ECE_OTHELLO_SAVE_SAVEMANAGER_HPP_

	#include <fstream>
	#include <sstream>
	#include "save.hpp"
	#include "../players/human.hpp"
	#include "../players/randomai.hpp"
	#include "../players/simpleai.hpp"
	#include "../players/enhancedai.hpp"

	/**
	 * @namespace Othello
	 * @details Espace de nommage du jeu.
	 */
	namespace Othello {
		/**
		 * @namespace Save
		 * @details Espace de nommage regroupant les entitées liées à la sauvegarde.
		 */
		namespace Save {
		    /**
		     * @class SaveManager
		     * @brief Ensemble de fonctions de sauvegarde
		     */
			class SaveManager {
				private:
					static const std::string savePath; /*! < Chemin du fichier de sauvegarde */

					/**
					 * @brief Sauvegarde du plateau
					 * @details Enregistre le contenu du plateau dans le fichier de sauvegarde
					 * @param ref Plateau
					 * @param saveFile Référence vers le fichier de sauvegarde en écriture
					 * @return Succès de l'opération
					 */
					static bool dumpBoard( Othello::Board::GameBoard* ref, std::ostream& saveFile );
					/**
					 * @brief Sauvegarde des voisins vides
					 * @details Enregistre les voisins vides dans le fichier de sauvegarde
					 * @param ref Plateau
					 * @param saveFile Référence vers le fichier de sauvegarde en écriture
					 * @return Succès de l'opération
					 */
					static bool dumpEmptyNeighbors( Othello::Board::GameBoard* ref, std::ostream& saveFile );
					/**
					 * @brief Sauvegarde du nombre de pions
					 * @details Enregistre le nombre de pions dans le fichier de sauvegarde
					 * @param ref Plateau
					 * @param saveFile Référence vers le fichier de sauvegarde en écriture
					 * @return Succès de l'opération
					 */
					static bool dumpPunCounts( Othello::Board::GameBoard* ref, std::ostream& saveFile );
					/**
					 * @brief Sauvegarde des joueurs
					 * @details Enregistre les joueurs dans le fichier de sauvegarde
					 * @param ref Référence vers la liste ds joueurs
					 * @param current Itérateur pointant vers le joueur actuel
					 * @param saveFile Référence vers le fichier de sauvegarde en écriture
					 * @return Succès de l'opération
					 */
					static bool dumpPlayers( std::vector<Othello::Players::Player*>& ref, std::vector<Othello::Players::Player*>::iterator& current, std::ostream& saveFile );

					/**
					 * @brief Créateur d'objet joueur
					 * @param type Type de joueur
					 * @param name Nom du joueur
					 * @param color Couleur associé
					 * @return Pointeur créé
					 */
					static Othello::Players::Player* init( Othello::Players::Player::Type type, std::string name, Othello::Board::Pun::Colors color );

					/**
					 * @brief Chargeur de plateau
					 * @param save Sauvegarde cible
					 * @param value Valeur extraire du fichier
					 * @return Succès de l'opération
					 */
					static bool loadBoard( Save& save, std::string value );
					/**
					 * @brief Chargeur de voisins vides
					 * @param save Sauvegarde cible
					 * @param value Valeur extraire du fichier
					 * @return Succès de l'opération
					 */
					static bool loadEmptyNeighbors( Save& save, std::string value );
					/**
					 * @brief Chargeur du nombre de pions
					 * @param save Sauvegarde cible
					 * @param value Valeur extraire du fichier
					 * @return Succès de l'opération
					 */
					static bool loadPunCounts( Save& save, std::string value );
					/**
					 * @brief Chargeur des joueurs
					 * @param save Sauvegarde cible
					 * @param value Valeur extraire du fichier
					 * @return Succès de l'opération
					 */
					static bool loadPlayers( Save& save, std::string value );

				public:
					/**
					 * @brief Chargeur de sauvegarde
					 * @details Charge la suavegarde depuis le ficheir. Renvoie une exception #invalid_save si elle est corrompue.
					 * @return Sauvegarde chargée
					 */
					static Save load();
					/**
					 * @brief Enregistreur de partie
					 * @details Enregistre la parite fournie dans le fichier.
					 * @param board Plateau de jeu
					 * @param players Ensemble des joueurs
					 * @param current Joueur actuel
					 */
					static void save( Othello::Board::GameBoard* board, std::vector<Othello::Players::Player*>& players, std::vector<Othello::Players::Player*>::iterator& current );
					/**
					 * @brief Vérificateur de présence de sauvegarde
					 * @details Vérifie que la sauvegarde st présente. Ne vérifie pas sa validité/conformité.
					 * @return Présence de la sauvegarde.
					 */
					static bool check();
					/**
					 * @brief Suppresseur de sauvegarde
					 * @return Succès de la suppression
					 */
					 static bool remove();
			};
		}
	}

#endif
