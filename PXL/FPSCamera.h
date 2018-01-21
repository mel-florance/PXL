#pragma once

#include "camera.h"

class FPSCamera : public Camera
{
public:
	FPSCamera(glm::vec3& position, float fov, float aspect, float near, float far);
	~FPSCamera();

	inline const glm::mat4 getViewMatrix() { return glm::lookAt(m_position, m_position + m_direction, m_up); }

	inline glm::vec3& getPosition() { return m_position; }
	inline void setPosition(const glm::vec3& position) { m_position = position; }

	inline glm::vec3& getRotation() { return m_rotation; }
	inline void setRotation(const glm::vec3& rotation) { m_rotation = rotation; }

	inline glm::vec3& getDirection() { return m_direction; }
	inline void setDirection(const glm::vec3& direction) { m_direction = direction; }

	void toggleCursor(bool value);
	void update(double delta);
	void onKeyboard(const SDL_KeyboardEvent& event);
	void onMouse(const glm::vec2& mouse);

private:
	glm::vec3 m_up;
	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec3 m_rotation;
	glm::vec3 m_velocity;
	glm::vec3 m_friction;

	float m_sensitivity;
	float m_moveSpeed;
	float m_maxSpeed;
	double m_delta;

	std::map<std::string, int> m_keys;
	std::map<std::string, bool> m_keys_states;
};
