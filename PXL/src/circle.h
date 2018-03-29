#pragma once

#include <glm\glm.hpp>

class Circle
{
public:
	Circle(const glm::vec2& position, float radius);
	~Circle();

	inline void setPosition(const glm::vec2& position) { m_position = position; }
	inline glm::vec2& getPosition() { return m_position; }

	inline void setRadius(float radius) { m_radius = radius; }
	inline float& getRadius() { return m_radius; }

	bool intersects(const glm::vec2& point);

private:
	glm::vec2 m_position;
	float m_radius;
};

