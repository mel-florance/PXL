#pragma once

#include <glm\glm.hpp>
#include <iostream>

class Rect
{
public:
	Rect(const glm::vec2& position, const glm::vec2& size);
	~Rect();

	inline void setPosition(const glm::vec2& position) { m_position = position; }
	inline void incrementPosition(const glm::vec2& position) { m_position += position; }
	inline glm::vec2& getPosition() { return m_position; }

	inline void setSize(const glm::vec2& size) { m_size = size; }
	inline glm::vec2& getSize() { return m_size; }

	bool intersects(const glm::vec2& point);

	inline void print() { 
		std::cout << 
			"x: "      << this->getPosition().x << "\n" <<  
			"y: "      << this->getPosition().y << "\n" << 
			"width: "  << this->getSize().x     << "\n" << 
			"height: " << this->getSize().y     << "\n"
		<< std::endl;
	}

private:
	glm::vec2 m_position;
	glm::vec2 m_size;
};
