#pragma once

#include <string>
#include <SDL2\SDL.h>


class Display
{
public:
	Display(float width, float height, const std::string& title);
	virtual ~Display();

	bool isClosed();
	void clear(float r, float g, float b, float a);
	void swapBuffers();

	inline float getWidth() { return m_width; }
	inline float getHeight() { return m_height; }
	inline float getAspect() { return m_width / m_height; }
	inline void setWidth(float width) { m_width = width; }
	inline void setHeight(float height) { m_width = height; }

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;
	float m_width;
	float m_height;
};

