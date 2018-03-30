#include "text.h"
#include <iostream>

Text::Text(const std::string& text, glm::vec4& color, glm::vec2& position, const std::string& font) : Widget(position, glm::vec2(0.0f))
{
	m_text = text;
	m_color = color;
	m_font = font;
	m_fontSize = 20.0f;
	m_blur = 0.1f;
	m_align = NVG_ALIGN_LEFT;
}

void Text::draw(NVGcontext* ctx, double delta)
{
	nvgFontSize(ctx, m_fontSize);
	nvgFontFace(ctx, m_font.c_str());
	nvgTextAlign(ctx, m_align);
	nvgFontBlur(ctx, m_blur);
	nvgFillColor(ctx, nvgRGBA(
		(unsigned char)m_color.r,
		(unsigned char)m_color.g,
		(unsigned char)m_color.b,
		(unsigned char)m_color.a)
	);

	float x = this->getPosition().x;
	float y = this->getPosition().y;

	if (this->getParent() != nullptr) 
	{
		x = this->getParent()->getPosition().x + x;
		y = this->getParent()->getPosition().y + y;
	}

	nvgText(ctx, x, y, m_text.c_str(), NULL);
}

Text::~Text()
{

}
