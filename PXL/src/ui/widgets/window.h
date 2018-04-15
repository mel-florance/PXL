#pragma once

#include "../core/widget.h"

class Window : public Widget
{
public:
	Window(const std::string& text, const glm::vec2& position, const glm::vec2& size, const std::string& font);
	~Window();

	void onKeyDown(const SDL_Event& event);
	void onTextInput(const SDL_Event& event);
	void onKeyUp(const SDL_Event& event);
	void onMouseMove(const SDL_Event& event);
	void onMouseDown(const SDL_Event& event);
	void onMouseUp(const SDL_Event& event);
	void onWindowResized(const SDL_Event& event);
	void onWindowSizeChanged(const SDL_Event& event);

	static void onClosed(CallbackData data);

	void drawBackground(NVGcontext* ctx, glm::vec2& position);
	void drawShadow(NVGcontext* ctx, glm::vec2& position);
	void drawHeader(NVGcontext* ctx, glm::vec2& position);
	void drawHeaderText(NVGcontext* ctx, glm::vec2& position);
	void drawIcon(NVGcontext* ctx, glm::vec2& position);

	void draw(NVGcontext* ctx, double delta);
	void update(double delta);

	void setDrawingShadow(bool state) { m_drawingShadow = state; }
	bool isDrawingShadow() { return m_drawingShadow; }

	void setOpacity(float value) { m_opacity = value; }
	float getOpacity() { return m_opacity; }

	void setHeaderFixedBottom(bool state) { m_header.isFixedBottom = state; }
	bool getHeaderFixedBottom() { return m_header.isFixedBottom; }

private:
	NVGpaint m_shadowPaint;
	NVGpaint m_headerPaint;
	bool m_drawingShadow;
	float m_opacity;

	struct WindowHeader {
		Rect* rect;
		std::string text;
		NVGalign align;
		std::string font;
		float fontSize;
		float blur;
		NVGcolor color;
		bool isFixedBottom;
	} m_header;

	NVGcolor m_background;
	float m_borderRadius;
};