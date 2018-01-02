#include <iostream>

#include "engine.h"
#include "sceneManager.h"

#define WIDTH 1280
#define HEIGHT 720

Engine::Engine()
{
	std::cout << "Engine started!" << std::endl;
	m_window = new Display(WIDTH, HEIGHT, "PXL Engine", "./res/textures/icon.png");
	m_clock = new Clock();
	m_sceneManager = new SceneManager();
	m_shaderManager = new ShaderManager();
	m_assetManager = new AssetManager();
	m_renderer = new Renderer();
}

void Engine::render(std::function<void()> callback)
{
	Scene* scene = m_sceneManager->getCurrentScene();

	if (m_window != nullptr) 
	{
		while (!m_window->isClosed())
		{
			m_clock->update();
			m_window->clear(scene->getClearColor());

			scene->getActiveCamera()->update(m_clock->m_deltaTime);

			callback();

			m_renderer->render(scene);
			m_window->swapBuffers();

			SDL_Delay(1);
		}
	}
}

Engine::~Engine()
{
	delete m_window;
	delete m_clock;
	delete m_sceneManager;
	delete m_shaderManager;
	delete m_assetManager;
	delete m_renderer;
}
