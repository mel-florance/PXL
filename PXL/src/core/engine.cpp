#include "engine.h"
#include "../editor/editor.h"

Engine::Engine(glm::vec2& windowSize) : m_running(false), m_frameTime(1.0 / 60.0)
{
	m_windowSize = windowSize;
	m_window = new Display(m_windowSize, "PXL Engine", "./res/textures/icon.png");
	m_clock = new Clock();
	m_loader = new Loader();

	m_soundManager = new SoundManager();
	m_fontManager = new FontManager();
	m_sceneManager = new SceneManager();
	m_shaderManager = new ShaderManager();
	m_assetManager = new AssetManager(m_loader, m_shaderManager, m_sceneManager);
	m_guiManager = new GuiManager(m_window, m_fontManager, m_assetManager, m_sceneManager);
	m_inputManager = new InputManager(m_window, m_guiManager, m_sceneManager);
	m_sceneManager->setGuiManager(m_guiManager);

	m_renderer = new Renderer(m_window, m_loader, m_shaderManager, m_assetManager, m_guiManager);
	m_profiler = new Profiler(m_clock);

	m_profiler->addTimer("frame");
	m_profiler->addTimer("input");
	m_profiler->addTimer("editor");
	m_profiler->addTimer("render");
	m_profiler->addTimer("swapBuffer");
	m_profiler->addTimer("sleep");

	m_editor = new Editor(this);

	EditorComponent* viewport = m_editor->getComponentByName("viewport");

	if (viewport != nullptr)
		m_renderer->setViewport((Viewport*)viewport);
}

void Engine::start()
{
	if (m_running) 
		return;

	m_running = true;

	double lastTime = m_clock->getTime();
	double frameCounter = 0;
	double unprocessedTime = 0;
	int frames = 0;

	while (m_running)
	{
		if (m_window->isClosed())
			this->stop();

		Scene* scene = m_sceneManager->getCurrentScene();
		
		if (scene != nullptr)
		{
			bool render = false;
			double startTime = m_clock->getTime();

			m_passedTime = startTime - lastTime;
			lastTime = startTime;

			unprocessedTime += m_passedTime;
			frameCounter += m_passedTime;

			if (frameCounter >= 0.3f)
			{
				m_fps = 1.0 / m_passedTime;
				frames = 0;
				frameCounter = 0;
			}

			m_profiler->startTimer("frame");

			while (unprocessedTime > m_frameTime)
			{
				m_profiler->startTimer("input");
					scene->getActiveCamera()->update(m_frameTime);
					m_inputManager->setCamera(scene->getActiveCamera());
					m_inputManager->update();
				m_profiler->stopTimer("input");

				m_profiler->startTimer("editor");
					if (m_editor != nullptr)
						m_editor->update(m_frameTime);
				m_profiler->stopTimer("editor");

				render = true;
				unprocessedTime -= m_frameTime;
			}

			if (render)
			{
				m_profiler->startTimer("render");
					m_renderer->clear(scene->getClearColor());
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
					SDL_Delay(0);
				m_profiler->stopTimer("sleep");
			}

			m_profiler->stopTimer("frame");
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
	delete m_editor;
	delete m_sceneManager;
	delete m_shaderManager;
	delete m_assetManager;
	delete m_guiManager;
	delete m_inputManager;
	delete m_renderer;
	delete m_loader;
	delete m_profiler;
}
