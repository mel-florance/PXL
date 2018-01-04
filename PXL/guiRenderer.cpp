#include "guiRenderer.h"

GuiRenderer::GuiRenderer(Loader* loader)
{
	this->m_loader = loader;
	this->m_quad = m_loader->loadToVAO("gui_quad", MeshFactory::getQuad());
}

GuiRenderer::~GuiRenderer()
{

}
