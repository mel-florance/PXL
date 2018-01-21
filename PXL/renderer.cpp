#include "renderer.h"

Renderer::Renderer(Display* window, Loader* loader, ShaderManager* shaderManager, AssetManager* assetManager)
{
	m_window = window;
	m_loader = loader;

	m_entityRenderer = new EntityRenderer(shaderManager);
	m_guiRenderer = new GuiRenderer(window, assetManager, shaderManager);
	m_skyboxRenderer = new SkyboxRenderer(m_loader, shaderManager);

	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
}

void Renderer::render(Scene* scene, double delta)
{
	m_skyboxRenderer->render(scene, delta);
	m_entityRenderer->render(scene);
	m_guiRenderer->render(scene);
}

Renderer::~Renderer()
{
	delete m_entityRenderer;
	delete m_guiRenderer;
	delete m_skyboxRenderer;
}
