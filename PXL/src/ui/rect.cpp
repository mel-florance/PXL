#include "rect.h"

Rect::Rect(glm::vec2& position, glm::vec2& size) : m_position(position), m_size(size)
{

}

bool Rect::intersects(const glm::vec2& point)
{
	return point.x > m_position.x
		&& point.x < m_position.x + m_size.x
		&& point.y > m_position.y
		&& point.y < m_position.y + m_size.y;
}

Rect::~Rect()
{

}
