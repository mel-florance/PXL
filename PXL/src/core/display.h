#pragma once

#include <map>
#include <string>
#include <iostream>
#include <algorithm>

#include <SDL2\SDL.h>
#include <GL/glew.h>
#include <glm\glm.hpp>

#include "../stb/stb_image.h"

class Display
{
public:
	Display(glm::vec2& size, const std::string& title, const std::string& icon);
	virtual ~Display();

	bool isClosed();
	inline void setIsClosed(bool value) { m_isClosed = value; }

	inline bool isFullscreen() { return m_isFullscreen; }
	inline void setIsFullscreen(bool state) { m_isFullscreen = state; }

	void swapBuffers();

	inline glm::vec2 getSize() { return m_size; }
	inline void setSize(glm::vec2 size) { m_size = size; }
	inline double getAspect() { return (double)m_size.x / (double)m_size.y; }

	inline SDL_Window* getWindow() { return m_window; };
	bool addIcon(const std::string& filename);

	inline void setCurrentCursor(const std::string& name) 
	{
		m_currentCursor = m_cursors[name];
		SDL_SetCursor(m_cursors[name]);
	}

	SDL_Cursor* getMCursor(const std::string& name);

	inline SDL_Cursor* getCurrentMouseCursor() { return m_currentCursor; }
	glm::vec2 m_size;

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;

	std::map<std::string, SDL_Cursor*> m_cursors;
	SDL_Cursor* m_currentCursor;

	bool m_isClosed;
	bool m_isFullscreen;
};

