
#include "soundManager.h"
#include "sound.h"

 SoundManager::SoundManager() {

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		std::cout << "Failed to initialize SoundManager." << std::endl;
	else
		std::cout << "SoundManager initialized." << std::endl;

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		std::cout << "Failed to initialize SoundManager." << std::endl;
	else
		std::cout << "SoundManager mixer initialized." << std::endl;
}

void SoundManager::play() {

	while (Mix_PlayingMusic());
}

Sound SoundManager::loadSound(const std::string & name, const std::string & path) {

	Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());

	if (chunk != NULL && name.size() > 0 )
	{
		Sound* sound = new Sound(name, path, chunk);

		m_sounds[name] = sound;
		std::cout << "Loaded sound: '" << name << "', '" << path << "'"  << std::endl;
		return sound;
	}

	std::cout << "Failed to load sound: '" << path << "'" << std::endl;
	return nullptr;
}

void SoundManager::playSound(const std::string & name, int channel, int loop) {

	Mix_PlayChannel(channel, m_sounds[name]->getData(), loop);
	std::cout << "Playing sound: " << name << std::endl;
}

 SoundManager::~SoundManager() {

	//Mix_FreeMusic(music);

	std::map<std::string, Sound*>::iterator it;

	for (it = m_sounds.begin(); it != m_sounds.end(); it++)
		Mix_FreeChunk(it->second->getData());

	Mix_CloseAudio();
}

