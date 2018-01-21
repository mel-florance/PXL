#include "inputManager.h"

InputManager::InputManager(Display* window)
{
	m_window = window;
}

void InputManager::update()
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			m_window->setIsClosed(true);

		if (e.type == SDL_WINDOWEVENT) 
		{
			switch (e.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				m_window->setWidth(e.window.data1);
				m_window->setHeight(e.window.data2);
				break;
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				m_window->setWidth(e.window.data1);
				m_window->setHeight(e.window.data2);
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
			SDL_WarpMouseInWindow(m_window->getWindow(), m_window->getWidth() / 2, m_window->getHeight() / 2);
			setMouse((float)e.motion.x - (m_window->getWidth() / 2), (float)e.motion.y - (m_window->getHeight() / 2));
			setMouseRel((float)e.motion.xrel, (float)e.motion.yrel);

			if (m_camera != nullptr)
				m_camera->onMouse(getMouseRel());
		}

		if (m_camera != nullptr)
			m_camera->onKeyboard(e.key);
	}
}

InputManager::~InputManager()
{

}
