#include <iostream>

#include "engine.h"
#include "sceneManager.h"


#define WIDTH 1280
#define HEIGHT 720

Engine::Engine()
{
	m_window = new Display(WIDTH, HEIGHT, "PXL Engine", "./res/textures/icon.png");
	m_clock = new Clock();
	m_sceneManager = new SceneManager();
	m_shaderManager = new ShaderManager();
}

void Engine::render(std::function<void()> callback)
{
	if (m_window != nullptr) {
		while (!m_window->isClosed()) {
			m_clock->update();
			m_window->clear(0.15f, 0.15f, 0.15f, 1.0f);

			m_window->swapBuffers();
			callback();

			SDL_Delay(1);
		}
	}
}

Display * Engine::getWindow()
{
	 return m_window;
}

Engine::~Engine()
{
	delete m_window;
	delete m_clock;
	delete m_sceneManager;
	delete m_shaderManager;
}
