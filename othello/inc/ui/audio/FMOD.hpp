#ifndef _ECE_SIAM_FMOD_HPP_
	#define _ECE_SIAM_FMOD_HPP_

	#include <string>
	#include <unordered_map>
	#include "../../../../fmod/inc/fmod.h"

	namespace Othello {
		namespace UI {
			namespace Audio {
				class FMOD {
					private:
						FMOD_SYSTEM* m_system;
						FMOD_CHANNELGROUP* m_masterChannel;
						FMOD_CHANNEL* m_musicChannel;
						FMOD_CHANNEL* m_soundChannel;
						std::unordered_map<std::string, FMOD_SOUND*> m_sounds;
						std::unordered_map<std::string, FMOD_SOUND*> m_musics;

					public:
						FMOD();
						~FMOD();

						bool loadSound( std::string name, std::string filepath );
						bool loadMusic( std::string name, std::string filepath );

						void playSound( std::string name );
						void playSoundWait( std::string name );
						void playMusic( std::string name );

						void pauseMusic();

						void stopMusic();

						void setMasterVolume( float volume );
						float getMasterVolume() const;
				};
			}
		}
	}
#endif
