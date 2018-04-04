#pragma once

#include <string>

#include "../core/widget.h"

class Text : public Widget
{
public:
	Text(const std::string& text, glm::vec4& color, glm::vec2& position, const std::string& font);
	~Text();

	inline void setText(const std::string& text) { m_text = text; }
	inline std::string& getText() { return m_text; }

	inline void setFontSize(float& size) { m_fontSize = size; }
	inline float& getFontsize() { return m_fontSize; }

	void draw(NVGcontext* ctx, double delta);

	void onKeyDown(const SDL_Event& event) {}
	void onTextInput(const SDL_Event& event) {}
	void onKeyUp(const SDL_Event& event) {}
	void onMouseMove(const SDL_Event& event) {}
	void onMouseDown(const SDL_Event& event) {}
	void onMouseUp(const SDL_Event& event) {}

private:
	glm::vec4 m_color;
	std::string m_text;
	std::string m_font;
	float m_fontSize;
	float m_blur;
	Uint32 m_align;
};