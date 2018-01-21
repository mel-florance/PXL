#pragma once

#include <string>
#include <iostream>

#include <glm\glm.hpp>
#include <SDL2\SDL.h>

#include "bitmapFont.h"

class Text
{
public:
	Text(const std::string& text, glm::vec3& color, int x, int y, CBitmapFont font);
	~Text();

	inline void setText(const std::string& text) { m_text = text; }
	inline void setSize(glm::vec2& size) { m_size = size; }
	void setScreen(Uint32 width, Uint32 height);
	void draw();

private:
	std::string m_text;
	glm::vec3 m_color;
	int m_x;
	int m_y;
	Uint32 m_screenWidth;
	Uint32 m_screenHeight;
	CBitmapFont m_font;
	glm::vec2 m_size = glm::vec2(1.0f, 1.0f);
};