#include "FPSCamera.h"

FPSCamera::FPSCamera(glm::vec3& position, float fov, float aspect, float near, float far) : Camera(fov, aspect, near, far)
{
	m_position = position;
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_direction = glm::vec3(0.0f, 0.0f, 1.0f);
	m_velocity = glm::vec3(0.0f);
	m_friction = glm::vec3(0.85f, 0.85f, 0.85f);

	m_moveSpeed = 20.0f;
	m_maxSpeed = 5.0f,
	m_sensitivity = 7.0f;

	m_keys["FORWARD"] = 26;
	m_keys["BACKWARD"] = 22;
	m_keys["LEFT"] = 4;
	m_keys["RIGHT"] = 7;
	m_keys["UP"] = 44;
	m_keys["DOWN"] = 225;
	m_keys["SPEED_UP"] = 8;
	m_keys["SPEED_DOWN"] = 20;

	m_keys_states["FORWARD"] = false;
	m_keys_states["BACKWARD"] = false;
	m_keys_states["LEFT"] = false;
	m_keys_states["RIGHT"] = false;
	m_keys_states["UP"] = false;
	m_keys_states["DOWN"] = false;
	m_keys_states["SPEED_UP"] = false;
	m_keys_states["SPEED_DOWN"] = false;

	this->toggleCursor(false);
}

void FPSCamera::toggleCursor(bool value)
{
	SDL_ShowCursor(value == true ? SDL_ENABLE : SDL_DISABLE);
}

void FPSCamera::update(double delta)
{
	m_delta = delta;

	float speed = m_moveSpeed * (float)m_delta;

	if (m_keys_states["SPEED_DOWN"])
		speed = m_moveSpeed * (float)m_delta;
	if (m_keys_states["SPEED_UP"])
		speed = m_maxSpeed * (float)m_delta;

	if (m_keys_states["FORWARD"])
		m_position += m_direction * speed;
	if (m_keys_states["BACKWARD"])
		m_position += m_direction * -speed;
	if (m_keys_states["LEFT"])
		m_position += glm::cross(m_direction, m_up) * -speed;
	if (m_keys_states["RIGHT"])
		m_position += glm::cross(m_direction, m_up) * speed;

	if (m_keys_states["UP"])
		m_position += m_up * speed;
	if (m_keys_states["DOWN"])
		m_position += m_up * -speed;

	/*m_velocity += m_direction;
	m_velocity *= m_friction;
	m_position += m_velocity;*/
}

void FPSCamera::onKeyboard(const SDL_KeyboardEvent& event)
{
	for (const auto &key : m_keys)
		if (event.keysym.scancode == key.second)
			m_keys_states[key.first] = (event.type == SDL_KEYDOWN);
}

void FPSCamera::onMouse(const glm::vec2& mouse)
{
	m_rotation.x = -glm::radians(mouse.x) * (float)m_delta * m_sensitivity;
	m_rotation.y = -glm::radians(mouse.y) * (float)m_delta * m_sensitivity;

	m_direction = glm::mat3(glm::rotate(m_rotation.x, m_up)) * m_direction;
	m_direction = glm::mat3(glm::rotate(m_rotation.y, glm::cross(m_direction, m_up))) * m_direction;
}

FPSCamera::~FPSCamera()
{

}