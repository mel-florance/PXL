#include "camera.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <SDL2\SDL.h>
#include <string>

Camera::Camera(const glm::vec3& position, float fov, float aspect, float near, float far)
{
	m_position = position;
	m_up = glm::vec3(0, 1, 0);
	m_direction = glm::vec3(0, 0, 1);
	m_friction = glm::vec3(0.85f, 0.85f, 0.85f);
	m_projMatrix = glm::perspective(fov, aspect, near, far);
	m_moveSpeed = 5.0f;
	m_sensitivity = 50.0f;

	m_keys["FORWARD"] = 26;
	m_keys["BACKWARD"] = 22;
	m_keys["LEFT"] = 4;
	m_keys["RIGHT"] = 7;
	m_keys["UP"] = 44;
	m_keys["DOWN"] = 225;

	m_keys_states["FORWARD"] = false;
	m_keys_states["BACKWARD"] = false;
	m_keys_states["LEFT"] = false;
	m_keys_states["RIGHT"] = false;
	m_keys_states["UP"] = false;
	m_keys_states["DOWN"] = false;

	SDL_ShowCursor(SDL_DISABLE);
}

void Camera::update(float delta)
{
	m_delta = delta;

	if (m_keys_states["FORWARD"])
		m_position += m_moveSpeed * m_delta * m_direction;
	if (m_keys_states["BACKWARD"])
		m_position += -m_moveSpeed * m_delta * m_direction;
	if (m_keys_states["LEFT"])
		m_position += -m_moveSpeed * m_delta * glm::cross(m_direction, m_up);
	if (m_keys_states["RIGHT"])
		m_position += m_moveSpeed * m_delta * glm::cross(m_direction, m_up);
	if (m_keys_states["UP"])
		m_position += m_moveSpeed * m_delta * m_up;
	if (m_keys_states["DOWN"])
		m_position += -m_moveSpeed * m_delta * m_up;
}

void Camera::onMouseMove(const glm::vec2& mouse)
{
	m_mouse = mouse;

	m_rotation.x = -glm::radians(m_mouse.x) * m_delta * m_sensitivity;
	m_rotation.y = -glm::radians(m_mouse.y) * m_delta * m_sensitivity;

	m_direction = glm::mat3(glm::rotate(m_rotation.x, m_up)) * m_direction;
	m_direction = glm::mat3(glm::rotate(m_rotation.y, glm::cross(m_direction, m_up))) * m_direction;

	m_oldMouse = mouse;
}


void Camera::onKeyboard(const SDL_KeyboardEvent& event)
{
	for (const auto &key : m_keys) {
		if (event.keysym.scancode == key.second) {
			m_keys_states[key.first] = (event.type == SDL_KEYDOWN);
		}
	}
}

Camera::~Camera()
{
	SDL_ShowCursor(SDL_ENABLE);
}
