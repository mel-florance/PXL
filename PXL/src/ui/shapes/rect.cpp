
#include "rect.h"

 Rect::Rect(const glm::vec2 & position, const glm::vec2 & size) {


}

 Rect::~Rect() {


}

bool Rect::intersects(const glm::vec2 & point) {

	return point.x > m_position.x
		&& point.x < m_position.x + m_size.x
		&& point.y > m_position.y
		&& point.y < m_position.y + m_size.y;
}

bool Rect::intersects(Rect & rect) {

	glm::vec2 pos = rect.getPosition();
	glm::vec2 size = rect.getSize();

	bool x = m_position.x + m_size.x >= pos.x 
		&& pos.x + size.x >= m_position.x;

	bool y = m_position.y + m_size.y >= pos.y
		&& pos.y + size.y >= m_position.y;

	return x && y;
}

