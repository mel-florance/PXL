#include "sound.h"

Sound::Sound(const std::string& path = "") : m_path(path), m_loaded(false)
{

}

Sound::~Sound()
{
	SDL_CloseAudio();
	SDL_FreeWAV(m_wav_buffer);
}