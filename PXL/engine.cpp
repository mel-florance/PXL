#include "engine.h"

#define WIDTH 1280
#define HEIGHT 720

Engine::Engine()
{
	std::cout << "Engine started!" << std::endl;
	m_window = new Display(WIDTH, HEIGHT, "PXL Engine", "./res/textures/icon.png");
	m_clock = new Clock();
	m_loader = new Loader();
	m_sceneManager = new SceneManager();
	m_shaderManager = new ShaderManager();
	m_assetManager = new AssetManager(m_loader, m_shaderManager, m_sceneManager);
	m_fontManager = new FontManager();
	m_renderer = new Renderer(m_shaderManager);
}

void Engine::render()
{
	Scene* scene = m_sceneManager->getCurrentScene();
	m_clock->update();
	m_window->clear(scene->getClearColor());

	scene->getActiveCamera()->update(m_clock->m_deltaTime);

	m_renderer->render(scene);
	m_window->swapBuffers();

	SDL_Delay(0);
}

Engine::~Engine()
{
	delete m_window;
	delete m_clock;
	delete m_sceneManager;
	delete m_shaderManager;
	delete m_assetManager;
	delete m_fontManager;
	delete m_renderer;
	delete m_loader;
}
