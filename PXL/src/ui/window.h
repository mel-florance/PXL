#pragma once

#include "widget.h"

class Window : public Widget
{
public:
	Window(const std::string& text, glm::vec2& position, glm::vec2& size, const std::string& font);
	~Window();

	void onKeyDown(const SDL_Keycode& keycode);
	void onKeyUp(const SDL_Keycode& keycode);
	void onMouseMove(const glm::vec2& mouse, const glm::vec2& rel);
	void onMouseDown(Uint8 button);
	void onMouseUp(Uint8 button);

	void draw(NVGcontext* ctx, double delta);
	void update(double delta);

private:
	NVGpaint m_shadowPaint;
	NVGpaint m_headerPaint;

	struct WindowHeader {
		Rect* rect;
		std::string text;
		NVGalign align;
		std::string font;
		float fontSize;
		float blur;
		glm::vec4 color;
	} m_header;

	glm::vec4 m_background;
	float m_borderRadius;
};