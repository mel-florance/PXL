#pragma once

#include <glm\glm.hpp>

#include "../core/widget.h"

class Checkbox : public Widget
{
public:
	Checkbox(const glm::vec2& position, const glm::vec2& size);

	void onMouseMove(const SDL_Event& event);
	void onMouseDown(const SDL_Event& event);
	void onMouseUp(const SDL_Event& event);

	void update(double delta);
	void draw(NVGcontext* ctx, double delta);

	~Checkbox();

private:
	NVGcolor m_background;
	float m_borderRadius;
};
