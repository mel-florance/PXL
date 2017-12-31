#pragma once

#include <string>
#include <iostream>

#include <SDL2\SDL.h>
#include <GL/glew.h>
#include <glm\glm.hpp>
#include <SDL2\SDL_ttf.h>
#include "stb_image.h"

#include "camera.h"

class Display
{
public:
	Display(Uint32 width, Uint32 height, const std::string& title, const std::string& icon);
	virtual ~Display();

	bool isClosed();
	void clear(float r, float g, float b, float a);
	void swapBuffers();

	inline Uint32 getWidth() { return m_width; }
	inline Uint32 getHeight() { return m_height; }
	inline float getAspect() { return (float)m_width / (float)m_height; }
	inline void setWidth(Uint32 width) { m_width = width; }
	inline void setHeight(Uint32 height) { m_width = height; }
	inline glm::vec2 getMouse() { return m_mouse; }
	inline glm::vec2 getMouseRel() { return m_mouseRel; }

	inline void setCamera(Camera* camera) {
		m_camera = camera;
	}

	inline SDL_Window* getWindow() { return m_window; };

	inline void setMouse(float x, float y) {
		this->m_mouse.x = x;
		this->m_mouse.y = y;
	}
	inline void setMouseRel(float x, float y) {
		this->m_mouseRel.x = x;
		this->m_mouseRel.y = y;
	}

	bool addIcon(const std::string& filename);

	void renderText(const std::string& message, SDL_Color color, int x, int y, int size);

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_GLContext m_glContext;
	Camera* m_camera;

	SDL_Texture* m_texture;

	bool m_isClosed;
	Uint32 m_width;
	Uint32 m_height;
	glm::vec2 m_mouse;
	glm::vec2 m_mouseRel;
};

