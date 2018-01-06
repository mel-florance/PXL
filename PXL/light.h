#pragma once

#include <glm\glm.hpp>

class Light
{
public:
	Light(const glm::vec3& position = glm::vec3(), const glm::vec3& color = glm::vec3(1.0f))
		: m_position(position), m_color(color) {};

	~Light();

	virtual inline const glm::vec3& getPosition() { return m_position; }
	virtual inline void setPosition(glm::vec3& position) { m_position = position; }

	virtual inline const glm::vec3& getColor() { return m_color; }
	virtual inline void setColor(glm::vec3& color) { m_color = color; }

private:
	glm::vec3 m_position;
	glm::vec3 m_color;
};