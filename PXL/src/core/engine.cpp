#include "engine.h"
#include "../game.h"

#define WIDTH 1280
#define HEIGHT 720

Engine::Engine() : m_running(false), m_frameTime(1.0 / 60)
{
	m_window = new Display(WIDTH, HEIGHT, "PXL Engine", "./res/textures/icon.png");
	m_clock = new Clock();
	m_loader = new Loader();
	m_sceneManager = new SceneManager();
	m_shaderManager = new ShaderManager();
	m_assetManager = new AssetManager(m_loader, m_shaderManager, m_sceneManager);
	m_guiManager = new GuiManager();
	m_inputManager = new InputManager(m_window, m_guiManager, m_sceneManager);
	m_renderer = new Renderer(m_window, m_loader, m_shaderManager, m_assetManager, m_guiManager);
	m_game = new Game(this);
	m_profiler = new Profiler(m_clock);

	std::cout << "Engine started!" << std::endl;
}

void Engine::start()
{
	if (m_running) 
		return;

	m_running = true;

	m_profiler->addTimer("input");
	m_profiler->addTimer("game");
	m_profiler->addTimer("render");
	m_profiler->addTimer("swapBuffer");
	m_profiler->addTimer("sleep");

	double lastTime = m_clock->getTime();
	double frameCounter = 0;
	double unprocessedTime = 0;
	int frames = 0;

	while (m_running)
	{
		Scene* scene = m_sceneManager->getCurrentScene();
		
		if (scene != nullptr)
		{
			bool render = false;
			double startTime = m_clock->getTime();
			m_passedTime = startTime - lastTime;
			lastTime = startTime;

			unprocessedTime += m_passedTime;
			frameCounter += m_passedTime;

			if (frameCounter >= 0.25f)
			{
				m_fps = 1.0 / m_passedTime;
				frames = 0;
				frameCounter = 0;
			}

			while (unprocessedTime > m_frameTime)
			{
				m_profiler->startTimer("input");
				scene->getActiveCamera()->update(m_frameTime);
				m_inputManager->setCamera(scene->getActiveCamera());
				m_inputManager->update();
				m_profiler->stopTimer("input");

				if (m_window->isClosed())
					this->stop();

				m_profiler->startTimer("game");


				if (m_game != nullptr)
					m_game->update(m_frameTime);
				m_profiler->stopTimer("game");

				render = true;

				unprocessedTime -= m_frameTime;
			}

			if (render)
			{
				m_profiler->startTimer("render");
				m_window->clear(scene->getClearColor());
				m_renderer->render(scene, m_passedTime);
				m_profiler->stopTimer("render");

				m_profiler->startTimer("swapBuffer");
				m_window->swapBuffers();
				m_profiler->stopTimer("swapBuffer");

				frames++;
			}
			else 
			{
				m_profiler->startTimer("sleep");
				SDL_Delay(1);
				m_profiler->stopTimer("sleep");
			}
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
	delete m_guiManager;
	delete m_inputManager;
	delete m_renderer;
	delete m_loader;
	delete m_profiler;
}
