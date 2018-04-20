#include "soundManager.h"

SoundManager::SoundManager()
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		std::cout << "Failed to initialize SoundManager." << std::endl;
	else
		std::cout << "SoundManager initialized." << std::endl;

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		std::cout << "Failed to initialize SoundManager." << std::endl;
	else
		std::cout << "SoundManager mixer initialized." << std::endl;
}

void SoundManager::play()
{
	while (Mix_PlayingMusic());
}

bool SoundManager::loadSound(const std::string& name, const std::string& path)
{
	Mix_Chunk* sound = Mix_LoadWAV(path.c_str());

	if (sound != NULL)
	{
		m_sounds[name] = sound;
		std::cout << "Loaded sound: '" << name << "', '" << path << "'"  << std::endl;
		return true;
	}

	std::cout << "Failed to load sound: '" << path << "'" << std::endl;
	return false;
}

void SoundManager::playSound(const std::string& name, int channel, int loop)
{
	Mix_PlayChannel(channel, m_sounds[name], loop);
	std::cout << "Playing sound: " << name << std::endl;
}

SoundManager::~SoundManager()
{
	//Mix_FreeMusic(music);

	std::map<std::string, Mix_Chunk*>::iterator it;

	for (it = m_sounds.begin(); it != m_sounds.end(); it++) {
		Mix_FreeChunk(it->second);
	}

	Mix_CloseAudio();
}
