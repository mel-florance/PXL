#pragma once

#include <string>

#include "../core/widget.h"

class Input : public Widget
{
public:
	Input(glm::vec2& position, glm::vec2& size, const std::string& font);
	~Input();

	typedef struct {
		std::string text;
		NVGalign align;
		std::string font;
		NVGcolor color;
		float fontSize;
		float blur;
		float width;
		std::string placeholder;
		bool drawPlaceholder;
	} InputText;

	typedef struct {
		glm::vec2 position;
		glm::vec2 size;
		NVGcolor background;
		Uint32 blinkStart;
		Uint32 blinkSpeed;
		bool blinking;
	} InputCaret;

	inline void setPlaceholder(const std::string& placeholder) { m_text.placeholder = placeholder; }
	const std::string& getPlaceholder() { return m_text.placeholder; }

	inline void setBackground(const NVGcolor& color) { m_background = color; }
	inline const NVGcolor& getBackground() { return m_background; }
	
	inline void setMargin(const glm::vec4& margin) { m_margin = margin; }
	inline glm::vec4& getMargin() { return m_margin; }

	inline void setText(const std::string& text) { m_text.text = text; }

	inline void setCaretPosition(glm::vec2& position) { m_caret->position = position; }
	inline glm::vec2 getCaretPosition() { return m_caret->position; }

	inline void setCaretSize(glm::vec2& size) { m_caret->size = size; }
	inline glm::vec2& getCaretSize() { return m_caret->size; }

	inline void setCaretBackground(const NVGcolor& background) { m_caret->background = background; }
	inline const NVGcolor& getCaretBackground() { return m_caret->background; }


	inline const std::string getText() { return m_text.text; }

	void update(double delta);
	void draw(NVGcontext* ctx, double delta);
	void drawBackground(NVGcontext* ctx, glm::vec2& position);
	void drawText(NVGcontext* ctx, glm::vec2& position);
	void drawCaret(NVGcontext* ctx, glm::vec2& position);
	void drawIcon(NVGcontext* ctx, glm::vec2& position);

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
	glm::vec4 m_margin;

	InputCaret* m_caret;
	InputText m_text;
};
