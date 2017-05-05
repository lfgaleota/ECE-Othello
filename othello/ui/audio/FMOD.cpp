#include "../../inc/ui/audio/FMOD.hpp"

using namespace std;
using namespace Othello::UI::Audio;

FMOD::FMOD() {
	//Initilization of system with 10 channels
	FMOD_System_Create( &this->m_system );

	FMOD_System_Init( this->m_system, 10, FMOD_INIT_NORMAL, 0 );
	FMOD_System_GetMasterChannelGroup( this->m_system, &this->m_masterChannel );
	FMOD_ChannelGroup_SetVolume( this->m_masterChannel, 100 );
}

FMOD::~FMOD() {
	// release the sounds
	for( auto& sound : m_sounds ) {
		FMOD_Sound_Release( sound.second );
	}
	for( auto& music : m_musics ) {
		FMOD_Sound_Release( music.second );
	}

	// release the system
	FMOD_System_Close( this->m_system );
	FMOD_System_Release( this->m_system );
}

bool FMOD::update() {
	return ( FMOD_System_Update( m_system ) == FMOD_OK );
}

bool FMOD::loadSound( string name, string filepath ) { //takes name and filepath in order to get the right one
	//Load sounds, if you cannot, then leave function
	FMOD_RESULT ret;
	FMOD_SOUND* sound;

	ret = FMOD_System_CreateSound( this->m_system, filepath.c_str(), FMOD_CREATESAMPLE | FMOD_LOOP_OFF, NULL, &sound );
	if( ret != FMOD_OK )
		return false;
	this->m_sounds[ name ] = sound;

	return true;
}

bool FMOD::loadMusic( string name, string filepath ) { //takes name and filepath in order to get the right one
	//Load musics, if you cannot then leaves the function
	FMOD_RESULT ret;
	FMOD_SOUND* sound;

	ret = FMOD_System_CreateSound( this->m_system, filepath.c_str(), FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, NULL, &sound );
	if( ret != FMOD_OK )
		return false;
	this->m_musics[ name ] = sound;

	return true;
}

void FMOD::playSound( string name ) { //plays a sound
	FMOD_System_PlaySound( this->m_system, this->m_sounds[ name ], this->m_masterChannel, 0, &this->m_soundChannel );
}

void FMOD::playSoundWait( string name ) { //pauses for a certain amount of time
	unsigned int length, pos = 0;
	FMOD_System_PlaySound( this->m_system, this->m_sounds[ name ], this->m_masterChannel, 0, &this->m_soundChannel );
	for( FMOD_Sound_GetLength( this->m_sounds[ name ], &length, FMOD_TIMEUNIT_MS ); pos < length; FMOD_Channel_GetPosition( this->m_soundChannel, &pos, FMOD_TIMEUNIT_MS )) {}
}

void FMOD::playMusic( string name ) { //plays music
	FMOD_Sound_SetLoopCount( this->m_musics[ name ], -1 );
	FMOD_System_PlaySound( this->m_system, this->m_musics[ name ], this->m_masterChannel, 0, &this->m_musicChannel );
	FMOD_Channel_SetVolume( this->m_musicChannel, 0.2f );
}

void FMOD::pauseMusic() { //pauses music
	FMOD_BOOL state;
	FMOD_Channel_GetPaused( this->m_musicChannel, &state );
	FMOD_Channel_SetPaused( this->m_musicChannel, !state );
}

void FMOD::stopMusic() { //stops music
	FMOD_Channel_Stop( this->m_musicChannel );
}

void FMOD::setMasterVolume( float volume ) {
	FMOD_ChannelGroup_SetVolume( this->m_masterChannel, volume );
}

float FMOD::getMasterVolume() const {
	float volume;
	FMOD_ChannelGroup_GetVolume( this->m_masterChannel, &volume );
	return volume;
}