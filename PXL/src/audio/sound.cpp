
#include "sound.h"

 Sound::Sound(const std::string & name, const std::string & path, Mix_Chunk & data) {

	m_data = data;
}

 Sound::~Sound() {

	Mix_FreeChunk(m_data);
}

