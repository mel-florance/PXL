#pragma once

#include <map>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <SDL2/SDL.h>
#include "../core/display.h"
#include "../editor/components/viewport.h"

class Camera
{
public:
	Camera(Display* windown, float fov, float aspect, float near, float far);
	virtual ~Camera();

	enum Mode { ORTHOGRAPHIC, PERSPECTIVE };
	enum Direction { UP, DOWN, LEFT, RIGHT, FORWARD, BACKWARD };

	inline float& getFov() { return m_fov; }
	inline void setFov(float value) { m_fov = value; }

	inline void setViewport(Viewport* viewport) { m_viewport = viewport; }
	inline Viewport* getViewport() { return m_viewport; }

	inline float getAspect() { return m_aspect; }
	inline void setAspect(float value) { m_aspect = value; }

	inline float getNear() { return m_near; }
	inline void setNear(float value) { m_near = value; }

	inline float getFar() { return m_far; }
	inline void setFar(float value) { m_far = value; }

	inline Mode getMode() { return m_mode; }
	inline void setMode(Mode mode) { m_mode = mode; }

	virtual inline const glm::mat4& getProjectionMatrix() { return m_projMatrix; }
	virtual inline void setProjectionMatrix(const glm::mat4& matrix) { m_projMatrix = matrix; }

	virtual inline const glm::mat4 getViewMatrix() { return m_viewMatrix; };
	virtual inline void setViewMatrix(const glm::mat4& matrix) { m_viewMatrix = matrix; }

	virtual inline glm::vec3& getPosition() { return m_position; };
	virtual inline void setPosition(const glm::vec3& position) { m_position = position; };
	
	virtual inline bool& isActive() { return m_active; }
	virtual inline void setActive(bool value) { m_active = value; }

	virtual inline void onMouseMove(const glm::vec2& mouse) {}
	virtual inline void onMouseDown(Uint8 button) {}
	virtual inline void onMouseUp(Uint8 button) {}
	virtual inline void onKeyDown(const SDL_Keycode& keycode) {}
	virtual inline void onKeyUp(const SDL_Keycode& keycode) {}
	virtual inline void onMouseWheel(const SDL_Event& event) {}
	virtual inline void onWindowResized(const SDL_Event& event);
	virtual inline void onWindowSizeChanged(const SDL_Event& event);

	virtual inline Display* getWindow() { return m_window; }
	virtual inline void update(double delta) {}

private:
	bool m_active;
	Display* m_window;
	Viewport* m_viewport;
	glm::vec3 m_position;

	Mode m_mode;
	float m_fov;
	float m_aspect;
	float m_near;
	float m_far;

	glm::mat4 m_projMatrix;
	glm::mat4 m_viewMatrix;
};