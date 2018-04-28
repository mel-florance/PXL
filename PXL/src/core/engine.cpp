#include "engine.h"
#include "../editor/editor.h"
#include <windows.h>

Engine::Engine(glm::vec2& windowSize)
{
	m_windowSize = windowSize;
	m_window = new Display(m_windowSize, "PXL Engine", "./res/textures/icon.png");
	m_loader = new Loader();

	m_gameLoop = new GameLoop(this);
	m_gameLoop->setUpdateCallback(&Engine::update);
	m_gameLoop->setRenderCallback(&Engine::render);

	m_soundManager = new SoundManager();
	m_fontManager = new FontManager();
	m_sceneManager = new SceneManager();
	m_shaderManager = new ShaderManager();
	m_assetManager = new AssetManager(m_loader, m_shaderManager, m_sceneManager);
	m_guiManager = new GuiManager(m_window, m_fontManager, m_assetManager, m_sceneManager);
	m_inputManager = new InputManager(m_window, m_guiManager, m_sceneManager);
	m_sceneManager->setGuiManager(m_guiManager);

	m_renderer = new Renderer(m_window, m_loader, m_shaderManager, m_assetManager, m_guiManager);
	m_editor = new Editor(this);

	EditorComponent* viewport = m_editor->getComponentByName("viewport");

	if (viewport != nullptr)
		m_renderer->setViewport((Viewport*)viewport);

	Scene* scene = m_sceneManager->getCurrentScene();
	m_inputManager->setCamera(scene->getActiveCamera());
}

void Engine::update(GameLoop* loop, Engine* self)
{
	if (self->m_window->isClosed())
		loop->stop();

	Scene* scene = self->m_sceneManager->getCurrentScene();

	if (scene != nullptr)
	{
		scene->getActiveCamera()->update(loop->getFrameTime());
		self->m_inputManager->update();
	}

	if (self->m_editor != nullptr)
		self->m_editor->update(loop->getFrameTime());
}

void Engine::render(GameLoop* loop, Engine* self)
{
	Scene* scene = self->m_sceneManager->getCurrentScene();

	if (scene != nullptr)
	{
		self->m_renderer->clear(scene->getClearColor());
		self->m_renderer->render(scene, loop->getPassedTime());
		self->m_window->swapBuffers();
	}
}

void Engine::start()
{
	m_gameLoop->start();
}

void Engine::stop()
{
	m_gameLoop->stop();
}

Engine::~Engine()
{
	delete m_window;
	delete m_editor;
	delete m_sceneManager;
	delete m_shaderManager;
	delete m_assetManager;
	delete m_guiManager;
	delete m_inputManager;
	delete m_renderer;
	delete m_loader;
}
