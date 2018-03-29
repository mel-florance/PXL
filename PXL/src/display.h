#pragma once

#include <string>
#include <iostream>

#include <SDL2\SDL.h>
#include <GL/glew.h>
#include <glm\glm.hpp>

#include "stb_image.h"

class Display
{
public:
	Display(Uint32 width, Uint32 height, const std::string& title, const std::string& icon);
	virtual ~Display();

	bool isClosed();
	inline void setIsClosed(bool value) { m_isClosed = value; }

	void clear(const glm::vec4& color);
	void swapBuffers();

	inline glm::vec2& getSize() { return m_size; }
	inline void setSize(glm::vec2& size) { m_size = size; }
	inline double getAspect() { return (double)m_size.x / (double)m_size.y; }

	inline SDL_Window* getWindow() { return m_window; };
	bool addIcon(const std::string& filename);

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;

	bool m_isClosed;
	glm::vec2 m_size;
};

