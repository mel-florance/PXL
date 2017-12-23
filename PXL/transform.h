#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

public:
	Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
		m_position(position),
		m_rotation(rotation),
		m_scale(scale) {};

	virtual ~Transform() {};

	inline glm::mat4 getModel() const
	{
		glm::mat4 positionMatrix = glm::translate(m_position);
		glm::mat4 rotationXMatrix = glm::rotate(m_rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 rotationYMatrix = glm::rotate(m_rotation.y, glm::vec3(1, 1, 0));
		glm::mat4 rotationZMatrix = glm::rotate(m_rotation.z, glm::vec3(0, 0, 1));
		glm::mat4 scaleMatrix = glm::scale(m_scale);

		glm::mat4 rotationMatrix = rotationZMatrix * rotationYMatrix * rotationXMatrix;

		return positionMatrix * rotationMatrix * scaleMatrix;
	}

	inline glm::vec3& getPosition() { return m_position; }
	inline glm::vec3& getRotation() { return m_rotation; }
	inline glm::vec3& getScale() { return m_scale; }

	inline void setPosition(glm::vec3& position) { m_position = position; }
	inline void setRotation(glm::vec3& rotation) { m_rotation = rotation; }
	inline void setScale(glm::vec3& scale) { m_scale = scale; }
};

