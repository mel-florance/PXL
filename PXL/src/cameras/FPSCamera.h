#pragma once

#include "camera.h"

class FPSCamera : public Camera
{
public:
	FPSCamera(Display* window, glm::vec3& position, float fov, float aspect, float near, float far);
	~FPSCamera();

	inline glm::vec3& getPosition() { return m_position; }
	inline void setPosition(const glm::vec3& position) { m_position = position; }

	inline glm::vec3& getRotation() { return m_rotation; }
	inline void setRotation(const glm::vec3& rotation) { m_rotation = rotation; }

	inline glm::vec3& getDirection() { return m_direction; }
	inline void setDirection(const glm::vec3& direction) { m_direction = direction; }

	void setPitch(float degrees);
	void setYaw(float degrees);
	void move(Direction dir);

	void onKeyDown(const SDL_Keycode& keycode);
	void onKeyUp(const SDL_Keycode& keycode);
	void onMouseMove(const glm::vec2& mouse);
	void onMouseDown(Uint8 button);
	void onMouseUp(Uint8 button);
	void onMouseWheel(const SDL_Event& event);

	void lockCursor(bool value);
	void update(double delta);

private:
	glm::vec3 m_up;
	glm::vec3 m_position;
	glm::vec3 m_positionDelta;
	glm::vec3 m_direction;
	glm::vec3 m_target;
	glm::vec3 m_rotation;

	float m_velocity;
	float m_viewFriction;
	float m_moveFriction;

	float m_pitch;
	float m_yaw;

	float m_sensitivity;
	float m_moveSpeed;
	float m_maxSpeed;
	double m_delta;
	bool m_cursorLocked;

	std::map<std::string, int> m_keys;
	std::map<std::string, bool> m_keys_states;
};
