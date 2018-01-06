#pragma once

#include <string>

#include <glm\glm.hpp>

#include "bitmapFont.h"

class Text
{
public:
	Text(const std::string& text, glm::vec3& color, int x, int y, CBitmapFont font);
	~Text();

	inline void setText(const std::string& text) { m_text = text; }
	inline void setSize(glm::vec2& size) { m_size = size; }
	void draw();

private:
	std::string m_text;
	glm::vec3 m_color;
	int m_x;
	int m_y;
	CBitmapFont m_font;
	glm::vec2 m_size = glm::vec2(1.0f, 1.0f);
};