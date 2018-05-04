#include "sound.h"

Sound::Sound(const std::string& name, const std::string& path, Mix_Chunk* data)
	: m_path(path), m_name(name), m_loaded(false), m_playing(false)
{
	m_data = data;
}

Sound::~Sound()
{
	Mix_FreeChunk(m_data);
}