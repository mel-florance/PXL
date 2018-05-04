#pragma once

#include "../core/widget.h"

class Label : public Widget
{
public:
	Label(glm::vec2& position, glm::vec2& size, const std::string& text, const std::string& font);
	~Label();

	void draw(NVGcontext* ctx, double delta);
	void update(double delta);

private:
	glm::vec4 m_margin;
	std::string m_text;
	NVGalign m_align;
	std::string m_font;
	float m_fontSize;
	float m_blur;
	glm::vec4 m_color;
};
