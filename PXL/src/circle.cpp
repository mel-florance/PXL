#include "circle.h"

Circle::Circle(const glm::vec2& position, float radius) : m_position(position), m_radius(radius)
{

}

bool Circle::intersects(const glm::vec2& point)
{
	return false;
}

Circle::~Circle()
{

}
