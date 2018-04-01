#pragma once

#include <string>

#include "widget.h"

class Input : public Widget
{
public:
	Input(glm::vec2& position, glm::vec2& size, const std::string& font);
	~Input();

	void setBackground(const glm::vec4& color) { m_background = color; }
	glm::vec4& getBackground() { return m_background; }
	
	void setMargin(const glm::vec4& margin) { m_margin = margin; }
	glm::vec4& getMargin() { return m_margin; }

	void setText(const std::string& text) { m_text.text = text; }
	const std::string& getText() { return m_text.text; }

	void setCaretPosition(glm::vec2& position) { m_caret.position = position; }
	glm::vec2 getCaretPosition() { return m_caret.position; }

	void setCaretSize(glm::vec2& size) { m_caret.size = size; }
	glm::vec2& getCaretSize() { return m_caret.size; }

	void setCaretBackground(glm::vec4& background) { m_caret.background = background; }
	glm::vec4& getCaretBackground() { return m_caret.background; }

	void update(double delta);
	void draw(NVGcontext* ctx, double delta);
	void drawBackground(NVGcontext* ctx, glm::vec2& position);
	void drawText(NVGcontext* ctx, glm::vec2& position);
	void drawCaret(NVGcontext* ctx, glm::vec2& position);

	void onKeyDown(const SDL_Event& event);
	void onTextInput(const SDL_Event& event);
	void onKeyUp(const SDL_Event& event);
	void onMouseMove(const SDL_Event& event);
	void onMouseDown(const SDL_Event& event);
	void onMouseUp(const SDL_Event& event);
	void onWindowResized(const SDL_Event& event);
	void onWindowSizeChanged(const SDL_Event& event);

private:
	glm::vec4 m_background;
	glm::vec4 m_margin;

	struct Caret {
		glm::vec2 position;
		glm::vec2 size;
		glm::vec4 background;
		Uint32 blinkStart;
		Uint32 blinkSpeed;
	} m_caret;

	struct InputText {
		std::string text;
		NVGalign align;
		std::string font;
		glm::vec4 color;
		float fontSize;
		float blur;
		float width;
	} m_text;
};
