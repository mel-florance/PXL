
#include "text.h"

 Text::Text(const std::string & text, NVGcolor & color, glm::vec2 & position, const std::string & font) {

	m_text = text;
	m_color = color;
	m_font = font;
	m_fontSize = 20.0f;
	m_blur = 0.0f;
	m_align = NVG_ALIGN_LEFT;
}

 Text::~Text() {


}

void Text::draw(NVGcontext & ctx, double delta) {

	nvgFontSize(ctx, m_fontSize);
	nvgFontFace(ctx, m_font.c_str());
	nvgTextAlign(ctx, m_align);
	nvgFontBlur(ctx, m_blur);
	nvgFillColor(ctx, m_color);

	glm::vec2 pos = this->getRelativePosition();

	nvgText(ctx, pos.x, pos.y, m_text.c_str(), NULL);
}

