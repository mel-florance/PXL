#pragma once

#include <string>
#include <iostream>

#include "widget.h"

class Button : public Widget
{
public:
	Button(glm::vec2& position, glm::vec2& size, const std::string& font);
	~Button();

	void setBackground(NVGcolor& color) { m_background = color; }
	NVGcolor& getBackground() { return m_background; }

	void setMargin(const glm::vec4& margin) { m_margin = margin; }
	glm::vec4& getMargin() { return m_margin; }

	void setText(const std::string& text) { m_text.text = text; }
	const std::string& getText() { return m_text.text; }

	void update(double delta);
	void draw(NVGcontext* ctx, double delta);
	void drawBackground(NVGcontext* ctx, glm::vec2& position);
	void drawText(NVGcontext* ctx, glm::vec2& position);

	void onKeyDown(const SDL_Event& event);
	void onTextInput(const SDL_Event& event);
	void onKeyUp(const SDL_Event& event);
	void onMouseMove(const SDL_Event& event);
	void onMouseDown(const SDL_Event& event);
	void onMouseUp(const SDL_Event& event);
	void onWindowResized(const SDL_Event& event);
	void onWindowSizeChanged(const SDL_Event& event);

private:
	NVGcolor m_background;
	NVGcolor m_hightlight;

	float m_borderRadius;
	glm::vec4 m_margin;

	struct ButtonIcon {
		float width;
	} m_icon;

	struct ButtonText {
		std::string text;
		std::string font;
		NVGalign align;
		NVGcolor color;
		NVGcolor shadow;
		float fontSize;
		float blur;
		float width;
	} m_text;

};
