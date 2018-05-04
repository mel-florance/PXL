#pragma once

#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Sound
{
public:
	Sound(const std::string& name, const std::string& path, Mix_Chunk* data);
	
	inline void setLoaded(bool state) { m_loaded = state; }
	inline bool isloaded() { return m_loaded; }

	inline void setPlaying(bool state) { m_playing = state; }
	inline bool isPlaying() { return m_playing; }

	inline void setPath(const std::string& path) { m_path = path; }
	inline std::string& getPath() { return m_path; }

	inline void setName(const std::string& name) { m_name = name; }
	inline std::string& getName() { return m_name; }

	inline void setData(Mix_Chunk* data) { m_data = data; }
	inline Mix_Chunk* getData() { return m_data; }

	~Sound();

private:
	bool m_loaded;
	bool m_playing;
	std::string m_path;
	std::string m_name;
	Mix_Chunk* m_data;
};
