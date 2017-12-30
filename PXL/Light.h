#pragma once;

#include "glm\glm.hpp"

class Light
{
public:
	Light();
	virtual ~Light();

	virtual inline glm::vec3& getPosition() { return m_position; }
	virtual inline glm::vec3& getColor() { return m_color; }

private:
	glm::vec3 m_position;
	glm::vec3 m_color;
};
