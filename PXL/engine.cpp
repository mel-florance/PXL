#include "engine.h"
#include "game.h"

#include <chrono>

using namespace std::chrono;

#define WIDTH 1280
#define HEIGHT 720

Engine::Engine() : m_running(false), m_frameTime(1.0 / 500)
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
}

void Engine::start()
{
	if (m_running)
		return;

	double lastTime = m_clock->getTime();
	double frameCounter = 0;
	double unprocessedTime = 0;
	int frames = 0;

	m_running = true;

	while (m_running)
	{
		bool render = false;
		Scene* scene = m_sceneManager->getCurrentScene();

		if (scene != nullptr)
		{
			double startTime = m_clock->getTime();
			double passedTime = startTime - lastTime;

		
			if (startTime < m_clock->getTime() - 0.001)
			{
				std::cout << m_clock->getTime() << std::endl;
			}

			lastTime = startTime;

			unprocessedTime += passedTime;
			frameCounter += passedTime;

			if (frameCounter >= 1.0)
			{
				frames = 0;
				frameCounter = 0;
			}

			while (unprocessedTime > m_frameTime)
			{
				m_window->update();

				if (m_window->isClosed())
					this->stop();

				scene->getActiveCamera()->update(passedTime);

				if (m_game != nullptr)
					m_game->update(passedTime);

				render = true;
				unprocessedTime -= m_frameTime;
			}

			if (render)
			{
				m_window->clear(scene->getClearColor());
				m_renderer->render(scene);
				m_window->swapBuffers();
				frames++;
			}
			else
				SDL_Delay(1);
		}
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
