#pragma once

#include <glm\glm.hpp>

#include "../core/widget.h"

class Scrollbar : public Widget
{
public:
	Scrollbar(const glm::vec2& position, const glm::vec2& size);

	void update(double delta);
	void draw(NVGcontext* ctx, double delta);

	void onKeyDown(const SDL_Event& event);
	void onTextInput(const SDL_Event& event);
	void onKeyUp(const SDL_Event& event);
	void onMouseMove(const SDL_Event& event);
	void onMouseDown(const SDL_Event& event);
	void onMouseUp(const SDL_Event& event);
	void onWindowResized(const SDL_Event& event);
	void onWindowSizeChanged(const SDL_Event& event);

	void computeHandleHeight(float parentHeight, float scrollMax);
	inline float getHandleDragOffset() { return m_handleDragOffset; }

	~Scrollbar();
private:
	NVGcolor m_background;
	NVGcolor m_handleBackground;
	glm::vec4 m_margin;

	float m_handleHeight;

	Icon* m_firstIcon;
	Icon* m_secondIcon;
	Rect* m_handle;

	bool m_handleDragged;
	float m_handleDragOffset;
};
