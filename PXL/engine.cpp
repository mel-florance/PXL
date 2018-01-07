#include "engine.h"
#include "game.h"

#include <chrono>

using namespace std::chrono;

#define WIDTH 1280
#define HEIGHT 720

Engine::Engine() : m_running(false)
{
	std::cout << "Engine started!" << std::endl;
	m_window = new Display(WIDTH, HEIGHT, "PXL Engine", "./res/textures/icon.png");
	m_clock = new Clock();
	m_loader = new Loader();
	m_sceneManager = new SceneManager();
	m_shaderManager = new ShaderManager();
	m_assetManager = new AssetManager(m_loader, m_shaderManager, m_sceneManager);
	m_fontManager = new FontManager();
	m_renderer = new Renderer(m_shaderManager, m_assetManager);
	m_game = new Game(this);

	m_frameStart = 0;
	m_frameEnd = 0;
	m_deltaTime = 0;
}

void Engine::start()
{
	if (m_running)
		return;

	m_running = true;

	while (m_running)
	{
		if (m_deltaTime < 1)
		{
			m_frameStart = m_clock->getTime();
			SDL_Delay(1);
			m_frameEnd = m_clock->getTime();
			m_deltaTime = m_frameEnd - m_frameStart;
		}

		m_frameStart = m_clock->getTime();
		Scene* scene = m_sceneManager->getCurrentScene();

		if (scene != nullptr)
		{
			m_window->update();

			if (m_window->isClosed())
				this->stop();

			scene->getActiveCamera()->update(m_deltaTime);

			if (m_game != nullptr)
				m_game->update(m_deltaTime);

			m_window->clear(scene->getClearColor());
			m_renderer->render(scene);
			m_window->swapBuffers();
		}

		m_frameEnd = m_clock->getTime();
		m_deltaTime = m_frameEnd - m_frameStart;
	}
}

void Engine::stop()
{
	m_running = false;
}

Engine::~Engine()
{
	delete m_window;
	delete m_clock;
	delete m_game;
	delete m_sceneManager;
	delete m_shaderManager;
	delete m_assetManager;
	delete m_fontManager;
	delete m_renderer;
	delete m_loader;
}
