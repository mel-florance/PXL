#pragma once

#include "mesh.h"
#include "camera.h"

class TPSCamera : public Camera
{
public:
	TPSCamera(Mesh* target, const glm::vec3& position, const glm::vec3& rotation, float fov, float aspect, float near, float far);
	~TPSCamera();

	void onMouseMove(const glm::vec2& mouse);
	void onKeyboard(const SDL_KeyboardEvent& event);
	void update(double delta);

	inline glm::vec3& getPosition() { return m_position; }
	inline void setPosition(const glm::vec3& position) { m_position = position; }

	inline glm::vec3& getRotation() { return m_rotation; }
	inline void setRotation(const glm::vec3& rotation) { m_rotation = rotation; }

private:
	Mesh* m_target;
	glm::vec3 m_position;
	glm::vec3 m_rotation;

	glm::vec2 m_mouse;
	glm::vec2 m_oldMouse;

	double m_sensitivity;
	double m_delta;

	std::map<std::string, int> m_keys;
	std::map<std::string, bool> m_keys_states;
};

