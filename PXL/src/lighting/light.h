#pragma once

#include <glm\glm.hpp>

class Light
{
public:
	Light(const glm::vec3& position = glm::vec3(), const glm::vec3& color = glm::vec3(1.0f)):
		m_position(position), 
		m_color(color),
		m_type(DIRECTIONAL),
		m_attenuation(glm::vec3(1.0f, 0.0f, 0.0f))
	{};

	~Light();

	enum LightType { DIRECTIONAL, POINT, SPOT };

	virtual inline glm::vec3& getPosition() { return m_position; }
	virtual inline void setPosition(const glm::vec3& position) { m_position = position; }

	virtual inline glm::vec3& getColor() { return m_color; }
	virtual inline void setColor(const glm::vec3& color) { m_color = color; }

	virtual inline glm::vec3& getAttenuation() { return m_attenuation; }
	virtual inline void setAttenuation(const glm::vec3& attenuation) { m_attenuation = attenuation; }

	virtual inline LightType& getType() { return m_type; }
	virtual inline void setType(const LightType& type) { m_type = type; }

private:
	glm::vec3 m_position;
	glm::vec3 m_color;
	glm::vec3 m_attenuation;
	LightType m_type;
	float m_coneAngle;
	float m_coneDirection;
};