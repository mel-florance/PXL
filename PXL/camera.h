#pragma once

#include <map>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <SDL2/SDL.h>

class Camera
{
public:
	Camera(float fov, float aspect, float near, float far);

	virtual inline const glm::mat4& getProjectionMatrix() { return m_projMatrix; }
	virtual inline const glm::mat4 getViewMatrix() { return m_viewMatrix; };

	virtual inline glm::vec3& getPosition() { return m_position; };
	virtual inline void setPosition(const glm::vec3& position) { m_position = position; };

	virtual inline void update(double delta) {}
	virtual inline void onMouse(const glm::vec2& mouse) {}
	virtual inline void onKeyboard(const SDL_KeyboardEvent& event) {}

	~Camera();

private:
	glm::vec3 m_position;

	glm::mat4 m_projMatrix;
	glm::mat4 m_viewMatrix;
};