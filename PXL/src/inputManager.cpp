#include "inputManager.h"

InputManager::InputManager(Display* window, SceneManager* sceneManager)
{
	m_window = window;
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

		if (e.type == SDL_KEYDOWN)
		{
			if (m_camera != nullptr)
				m_camera->onKeyDown(e.key.keysym.sym);

			for (unsigned int i = 0; i < scene->getWidgets().size(); i++)
				scene->getWidgets()[i]->onKeyDown(e);
		}

		if (e.type == SDL_KEYUP)
		{
			if (m_camera != nullptr)
				m_camera->onKeyUp(e.key.keysym.sym);

			for (unsigned int i = 0; i < scene->getWidgets().size(); i++)
				scene->getWidgets()[i]->onKeyUp(e);
		}

		if (e.type == SDL_TEXTINPUT)
		{
			for (unsigned int i = 0; i < scene->getWidgets().size(); i++)
				scene->getWidgets()[i]->onTextInput(e);
		}

		if (e.type == SDL_WINDOWEVENT) 
		{
			switch (e.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				m_window->setSize(glm::vec2(e.window.data1, e.window.data2));
				break;
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				m_window->setSize(glm::vec2(e.window.data1, e.window.data2));
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

		if (e.type == SDL_MOUSEMOTION)
		{
			setMouse((float)e.motion.x, (float)e.motion.y);
			setMouseRel((float)e.motion.xrel, (float)e.motion.yrel);

			if (m_camera != nullptr)
				m_camera->onMouseMove(getMouseRel());

			for (unsigned int i = 0; i < scene->getWidgets().size(); i++)
				scene->getWidgets()[i]->onMouseMove(getMouse(), getMouseRel());
		}

		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (m_camera != nullptr)
				m_camera->onMouseDown(e.button.button);

			for (unsigned int i = 0; i < scene->getWidgets().size(); i++)
				scene->getWidgets()[i]->onMouseDown(e.button.button);
		}
		
		if (e.type == SDL_MOUSEBUTTONUP)
		{
			if (m_camera != nullptr)
				m_camera->onMouseUp(e.button.button);

			for (unsigned int i = 0; i < scene->getWidgets().size(); i++)
				scene->getWidgets()[i]->onMouseUp(e.button.button);
		}
	}
}

InputManager::~InputManager()
{

}
