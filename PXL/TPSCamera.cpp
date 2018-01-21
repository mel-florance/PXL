#include "TPSCamera.h"

TPSCamera::TPSCamera(Mesh* target, const glm::vec3& position, const glm::vec3& rotation, float fov, float aspect, float near, float far) : Camera(fov, aspect, near, far)
{
	m_target = target;
	m_position = position;
	m_rotation = rotation;
	m_sensitivity = 7.0;

	m_keys["FORWARD"] = 26;
	m_keys["BACKWARD"] = 22;
	m_keys["LEFT"] = 4;
	m_keys["RIGHT"] = 7;

	m_keys_states["FORWARD"] = false;
	m_keys_states["BACKWARD"] = false;
	m_keys_states["LEFT"] = false;
	m_keys_states["RIGHT"] = false;
}

void TPSCamera::onMouseMove(const glm::vec2& mouse)
{
	m_mouse = mouse;
}

void TPSCamera::onKeyboard(const SDL_KeyboardEvent& event)
{
	for (const auto &key : m_keys) {
		if (event.keysym.scancode == key.second) {
			m_keys_states[key.first] = (event.type == SDL_KEYDOWN);
		}
	}
}

void TPSCamera::update(double delta)
{
	m_delta = delta;
}

TPSCamera::~TPSCamera()
{

}
