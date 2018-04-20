#pragma once

#include <string>
#include <iostream>

#include <SDL2/SDL.h>

class Sound
{
public:
	Sound(const std::string& path);

	Uint8* m_audio_pos;
	Uint32 m_audio_length;

	inline void load()
	{
		if (m_path.size() > 0) 
		{
			if (SDL_LoadWAV(m_path.c_str(), &m_wav_spec, &m_wav_buffer, &m_wav_length) == NULL)
			{
				std::cout << "Failed to load sound: " << m_path << std::endl;
				return;
			}

			m_loaded = true;

			m_wav_spec.callback = &callback;
			m_wav_spec.userdata = NULL;
			m_audio_pos = m_wav_buffer;
			m_audio_length = m_wav_length;

			if (SDL_OpenAudio(&m_wav_spec, NULL) < 0) 
			{
				std::cout << "Couldn't open audio sound: " << SDL_GetError() << std::endl;
				return;
			}

			SDL_PauseAudio(0);
		}
	}

	void play() 
	{
		SDL_PauseAudio(0);
	}


	static void callback(void* userdata, Uint8* stream, int length)
	{
		//if (m_audio_length == 0)
		//	return;

		//length = (Uint32)length > m_audio_length ? m_audio_length : length;
		//SDL_memcpy(stream, m_audio_pos, length);
		////SDL_MixAudio(stream, m_audio_pos, len, SDL_MIX_MAXVOLUME);

		//m_audio_pos += length;
		//m_audio_length -= length;
	}

	~Sound();

private:
	bool m_loaded;
	std::string m_path;
	Uint32 m_wav_length;
	Uint8* m_wav_buffer;
	SDL_AudioSpec m_wav_spec;
};
