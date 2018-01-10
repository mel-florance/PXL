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

	inline Uint32 getWidth() { return m_width; }
	inline Uint32 getHeight() { return m_height; }
	inline float getAspect() { return (float)m_width / (float)m_height; }
	inline void setWidth(Uint32 width) { m_width = width; }
	inline void setHeight(Uint32 height) { m_width = height; }

	inline SDL_Window* getWindow() { return m_window; };

	bool addIcon(const std::string& filename);

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;

	bool m_isClosed;
	Uint32 m_width;
	Uint32 m_height;
};

