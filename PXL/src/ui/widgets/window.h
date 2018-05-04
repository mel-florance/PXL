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

	inline void setDrawingShadow(bool state) { m_drawingShadow = state; }
	inline bool isDrawingShadow() { return m_drawingShadow; }

	inline void setOpacity(float value) { m_opacity = value; }
	inline float getOpacity() { return m_opacity; }

	inline void setHeaderFixedBottom(bool state) { m_header.isFixedBottom = state; }
	inline bool getHeaderFixedBottom() { return m_header.isFixedBottom; }

	inline void setMargin(const glm::vec4& margin) { m_margin = margin; }
	inline glm::vec4& getMargin() { return m_margin; }

	inline void setMarginTop(float value) { m_margin.x = value; }
	inline float getMarginTop() { return m_margin.x; }

	inline void setMarginRight(float value) { m_margin.y = value; }
	inline float getMarginRight() { return m_margin.y; }

	inline void setMarginBottom(float value) { m_margin.z = value; }
	inline float getMarginBottom() { return m_margin.z; }

	inline void setMarginLeft(float value) { m_margin.w = value; }
	inline float getMarginLeft() { return m_margin.w; }

private:
	NVGpaint m_shadowPaint;
	NVGpaint m_headerPaint;
	bool m_drawingShadow;
	float m_opacity;

	glm::vec4 m_margin;
	glm::vec2 m_windowDragOffset;

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
