#pragma once

#include "../core/widget.h"

class Slider : public Widget
{
public:
	Slider(const glm::vec2& position, const glm::vec2& size);
	~Slider();

private:
	float m_min;
	float m_max;
	float m_step;
};