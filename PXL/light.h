#pragma once

#include <glm\glm.hpp>

class Light
{
public:
	Light(const glm::vec4& position = glm::vec4(), const glm::vec3& color = glm::vec3(1.0f)):
		m_position(position), 
		m_color(color), 
		m_attenuation(glm::vec3(1.0f, 0.01f, 0.002f))
	{};

	~Light();

	virtual inline const glm::vec4& getPosition() { return m_position; }
	virtual inline void setPosition(glm::vec4& position) { m_position = position; }

	virtual inline const glm::vec3& getColor() { return m_color; }
	virtual inline void setColor(glm::vec3& color) { m_color = color; }

	virtual inline glm::vec3& getAttenuation() { return m_attenuation; }
	virtual inline void setAttenuation(glm::vec3& attenuation) { m_attenuation = attenuation; }

private:
	glm::vec4 m_position; // 4th component is the light type.
	glm::vec3 m_color;
	glm::vec3 m_attenuation;
	float m_coneAngle;
	float m_coneDirection;
};