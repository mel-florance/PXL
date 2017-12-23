#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera {
public:
	Camera(const glm::vec3& position, float fov, float aspect, float near, float far) {
		m_position = position;
		m_forward = glm::vec3(0, 0, 1);
		m_up = glm::vec3(0, 1, 0);
		m_perspective = glm::perspective(fov, aspect, near, far);
	};

	inline glm::mat4 getViewProjection() const {
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
	}

	virtual ~Camera() {};

private:
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
	glm::mat4 m_perspective;
};