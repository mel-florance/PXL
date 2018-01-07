#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <map>

class Camera {
public:
	Camera() {};
	Camera(glm::vec3& position, float fov, float aspect, float near, float far);

	inline const glm::mat4 getViewMatrix() { return glm::lookAt(m_position, m_position + m_direction, m_up); }
	inline const glm::mat4& getProjectionMatrix() { return m_projMatrix; }

	void onMouseMove(const glm::vec2& mouse);
	void onKeyboard(const SDL_KeyboardEvent& event);
	void update(double delta);

	virtual ~Camera();

private:
	glm::vec3 m_up;
	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec3 m_rotation;

	glm::vec3 m_velocity;
	glm::vec3 m_friction;

	glm::mat4 m_projMatrix;
	glm::mat4 m_viewMatrix;

	glm::vec2 m_mouse;
	glm::vec2 m_oldMouse;

	float m_sensitivity;
	float m_moveSpeed;
	float m_maxSpeed;
	float m_delta;

	std::map<std::string, int> m_keys;
	std::map<std::string, bool> m_keys_states;
};