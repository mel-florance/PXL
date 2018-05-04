#pragma once

#include <iostream>

#include <SDL2\SDL.h>
#include <glm\glm.hpp>

#include "display.h"
#include "../cameras/camera.h"
#include "../scene/sceneManager.h"
#include "../ui/core/guiManager.h"

class InputManager : public Manager
{
public:
	InputManager(Display* window, GuiManager* guiManager, SceneManager* sceneManager);
	~InputManager();

	inline glm::vec2& getMouse() { return m_mouse; }
	inline glm::vec2& getMouseRel() { return m_mouseRel; }

	inline void setMouse(float x, float y) {
		this->m_mouse.x = x;
		this->m_mouse.y = y;
	}

	inline void setMouseRel(float x, float y) {
		this->m_mouseRel.x = x;
		this->m_mouseRel.y = y;
	}

	inline void setCamera(Camera* camera) { m_camera = camera; }
	inline Camera* getCamera() { return m_camera; }

	void update();

private:
	SceneManager* m_sceneManager;
	GuiManager* m_guiManager;
	Display* m_window;
	Camera* m_camera;

	glm::vec3 m_mouseStates;
	glm::vec2 m_mouse;
	glm::vec2 m_mouseRel;

	std::map<std::string, int> m_keys;
	std::map<std::string, bool> m_keys_states;
};
