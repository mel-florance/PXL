#include "renderer.h"

Renderer::Renderer(ShaderManager* shaderManager, AssetManager* assetManager)
{
	m_entityRenderer = new EntityRenderer(shaderManager);
	m_guiRenderer = new GuiRenderer(assetManager, shaderManager);

	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
}

void Renderer::render(Scene* scene)
{
	m_entityRenderer->render(scene);
	m_guiRenderer->render(scene);
}

Renderer::~Renderer()
{
	delete m_entityRenderer;
	delete m_guiRenderer;
}
