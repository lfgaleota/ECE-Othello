#ifndef _ECE_SIAM_FMOD_HPP_
	#define _ECE_SIAM_FMOD_HPP_

	#include <string>
	#include <unordered_map>
	#include "../../../../fmod/inc/fmod.h"

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
			 * @namespace Audio
			 * @details Espace de nommage des clases se rapportant à l'audio.
			 */
			namespace Audio {
				/**
				 * @class FMOD
				 * @brief Classe permettant de gérer FMOD
				 */
				class FMOD {
					private:
						FMOD_SYSTEM* m_system;
						FMOD_CHANNELGROUP* m_masterChannel;
						FMOD_CHANNEL* m_musicChannel;
						FMOD_CHANNEL* m_soundChannel;
						std::unordered_map<std::string, FMOD_SOUND*> m_sounds;
						std::unordered_map<std::string, FMOD_SOUND*> m_musics;

					public:
						/**
						 * @brief Constructeur
						 * @etails Initialise le système audio
						 */
						FMOD();

						/**
						 * @brief Destructeur
						 * @etails Détruit le système audio
						 */
						~FMOD();

						/**
						 * @brief Chargement de fichier son
						 * @param name Nom du son
						 * @param filepath Chemin vers le fichier
						 * @return Chargement effectué ou non
						 */
						bool loadSound( std::string name, std::string filepath );

						/**
						 * @brief Chargement de fichier musique
						 * @param name Nom de la musique
						 * @param filepath Chemin vers le fichier
						 * @return Chargement effectué ou non
						 */
						bool loadMusic( std::string name, std::string filepath );

						/**
						 * @brief Lecture de son (pas de boucle)
						 * @param name Nom du son
						 */
						void playSound( std::string name );

						/**
						 * @brief Lecture de son (pas de boucle), attente jusqu'à la fin
						 * @param name Nom du son
						 */
						void playSoundWait( std::string name );

						/**
						 * @brief Lecture de musique (boucle)
						 * @param name Nom de la musique
						 */
						void playMusic( std::string name );

						/**
						 * @brief Mettre en pause les musiques
						 */
						void pauseMusic();

						/**
						 * @brief Arrêter les musiques
						 */
						void stopMusic();

						/**
						 * @brief Réglage du son principal
						 * @param volume Volume entre 0 et 1
						 */
						void setMasterVolume( float volume );

						/**
						 * @brief Valeur du son principal
						 * @return Volume entre 0 et 1
						 */
						float getMasterVolume() const;
				};
			}
		}
	}
#endif
