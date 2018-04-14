#pragma once

#include <map>
#include <string>
#include <iostream>

#include <SDL2\SDL.h>
#include <GL/glew.h>
#include <glm\glm.hpp>

#include "../stb/stb_image.h"

class Display
{
public:
	Display(Uint32 width, Uint32 height, const std::string& title, const std::string& icon);
	virtual ~Display();

	bool isClosed();
	inline void setIsClosed(bool value) { m_isClosed = value; }

	inline bool isFullscreen() { return m_isFullscreen; }
	inline void setIsFullscreen(bool state) { m_isFullscreen = state; }

	void clear(const glm::vec4& color);
	void swapBuffers();

	inline glm::vec2& getSize() { return m_size; }
	inline void setSize(glm::vec2& size) { m_size = size; }
	inline double getAspect() { return (double)m_size.x / (double)m_size.y; }

	inline SDL_Window* getWindow() { return m_window; };
	bool addIcon(const std::string& filename);

	inline void setCurrentCursor(const std::string& name) 
	{
		m_currentCursor = m_cursors[name];
		SDL_SetCursor(m_cursors[name]);
	}

	inline SDL_Cursor* getCursor(const std::string& name) { return m_cursors[name]; }
	inline SDL_Cursor* getCurrentCursor() { return m_currentCursor; }

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;

	std::map<std::string, SDL_Cursor*> m_cursors;
	SDL_Cursor* m_currentCursor;

	bool m_isClosed;
	bool m_isFullscreen;
	glm::vec2 m_size;
};

