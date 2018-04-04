#include "label.h"

Label::Label(glm::vec2& position, glm::vec2& size, const std::string& text, const std::string& font) : Widget(position, size)
{
	m_text = text;
	m_margin = glm::vec4(
		8.0f, // Top
		5.0f, // Right
		8.0f, // Bottom
		5.0f  // Left
	);

	m_font = font;
	m_fontSize = 20.0f;
	m_blur = 0.0f;
	m_align = NVG_ALIGN_LEFT;
	m_color = glm::vec4(255.0f, 255.0f, 255.0f, 255.0f);
}

Label::~Label()
{

}

void Label::update(double delta)
{

}

void Label::draw(NVGcontext* ctx, double delta)
{
	nvgSave(ctx);

	glm::vec2 pos = this->getRelativePosition();

	nvgScissor(ctx, pos.x, pos.y, this->getSize().x, this->getSize().y - m_margin.x);

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

	nvgText(ctx,
		pos.x,
		pos.y + (this->getSize().y * 0.5f) + 5,
		m_text.c_str(),
		NULL
	);

	nvgRestore(ctx);
}
