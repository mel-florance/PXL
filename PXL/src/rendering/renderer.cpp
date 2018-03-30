#include "renderer.h"

Renderer::Renderer(Display* window, Loader* loader, ShaderManager* shaderManager, AssetManager* assetManager, GuiManager* guiManager)
{
	m_window = window;
	m_loader = loader;

	m_entityRenderer = new EntityRenderer(shaderManager);
	m_skyboxRenderer = new SkyboxRenderer(m_loader, shaderManager);
	m_guiRenderer = new GuiRenderer(guiManager, window);

	glEnable(GL_MULTISAMPLE);
}

void Renderer::render(Scene* scene, double delta)
{
	m_skyboxRenderer->render(scene, delta);
	m_entityRenderer->render(scene, delta);
	m_guiRenderer->render(scene, delta);
}

Renderer::~Renderer()
{
	delete m_entityRenderer;
	delete m_skyboxRenderer;
	delete m_guiRenderer;
}
