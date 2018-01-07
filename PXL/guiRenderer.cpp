#include "guiRenderer.h"

GuiRenderer::GuiRenderer(AssetManager* assetManager)
{
	this->m_assetManager = assetManager;
	this->m_quad = assetManager->getLoader()->loadToVAO("gui_quad", MeshFactory::getQuad());
}

void GuiRenderer::render(Scene* scene)
{
	for (unsigned int i = 0; i < scene->getTexts().size(); i++)
	{
		scene->getTexts()[i]->draw();
	}
}

GuiRenderer::~GuiRenderer()
{

}
