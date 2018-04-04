#include "inputManager.h"

InputManager::InputManager(Display* window, GuiManager* guiManager, SceneManager* sceneManager) : Manager()
{
	m_window = window;
	m_guiManager = guiManager;
	m_sceneManager = sceneManager;
}

void InputManager::update()
{
	SDL_Event e;
	Scene* scene = m_sceneManager->getCurrentScene();

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			m_window->setIsClosed(true);

		if (e.type == SDL_TEXTINPUT)
			m_guiManager->handleEvent("onTextInput", e);

		if (e.type == SDL_KEYDOWN) {

			if (m_camera != nullptr)
				m_camera->onKeyDown(e.key.keysym.sym);

			m_guiManager->handleEvent("onKeyDown", e);
		}

		if (e.type == SDL_KEYUP)
		{
			if (m_camera != nullptr)
				m_camera->onKeyUp(e.key.keysym.sym);

			m_guiManager->handleEvent("onKeyUp", e);
		}

		if (e.type == SDL_MOUSEMOTION)
		{
			m_guiManager->handleEvent("onMouseMove", e);
			setMouse((float)e.motion.x, (float)e.motion.y);
			setMouseRel((float)e.motion.xrel, (float)e.motion.yrel);

			if (m_camera != nullptr)
				m_camera->onMouseMove(getMouseRel());
		}

		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (m_camera != nullptr)
				m_camera->onMouseDown(e.button.button);

			m_guiManager->handleEvent("onMouseDown", e);
		}

		if (e.type == SDL_MOUSEBUTTONUP)
		{
			if (m_camera != nullptr)
				m_camera->onMouseUp(e.button.button);

			m_guiManager->handleEvent("onMouseUp", e);
		}

		if (e.type == SDL_WINDOWEVENT) 
		{
			switch (e.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				m_window->setSize(glm::vec2(e.window.data1, e.window.data2));
				m_guiManager->handleEvent("windowResized", e);
				break;
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				m_window->setSize(glm::vec2(e.window.data1, e.window.data2));
				m_guiManager->handleEvent("windowSizeChanged", e);
				glViewport(0, 0, e.window.data1, e.window.data2);
				break;
			case SDL_WINDOWEVENT_SHOWN:
			case SDL_WINDOWEVENT_HIDDEN:
			case SDL_WINDOWEVENT_EXPOSED:
			case SDL_WINDOWEVENT_MOVED:
			case SDL_WINDOWEVENT_MINIMIZED:
			case SDL_WINDOWEVENT_MAXIMIZED:
			case SDL_WINDOWEVENT_RESTORED:
			case SDL_WINDOWEVENT_ENTER:
			case SDL_WINDOWEVENT_LEAVE:
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			case SDL_WINDOWEVENT_FOCUS_LOST:
			case SDL_WINDOWEVENT_CLOSE:
				break;
			}
		}
	}
}

InputManager::~InputManager()
{

}
