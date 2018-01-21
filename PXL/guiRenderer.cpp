#include "guiRenderer.h"
#include "display.h"

GuiRenderer::GuiRenderer(Display* window, AssetManager* assetManager, ShaderManager* shaderManager)
{
	m_window = window;
	m_assetManager = assetManager;
	m_shaderManager = shaderManager;
	m_guiShader = m_shaderManager->getShader("gui");
	m_quad = assetManager->getLoader()->loadToVAO("gui_quad", MeshFactory::getQuad());
}

void GuiRenderer::render(Scene* scene)
{
	m_guiShader->bind();

	glBindVertexArray(m_quad->getVao());
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	for (unsigned int i = 0; i < scene->getWidgets().size(); i++)
	{
		m_guiShader->setUniformMat4fv("mTransform", scene->getWidgets()[i]->getTransform()->getTransformation());
		scene->getWidgets()[i]->getMaterial()->preUpdate(scene);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, m_quad->getVertexCount());
		scene->getWidgets()[i]->getMaterial()->postUpdate();
	}

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	m_guiShader->unbind();

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	for (unsigned int i = 0; i < scene->getTexts().size(); i++)
	{
		scene->getTexts()[i]->setScreen(m_window->getWidth(), m_window->getHeight());
		scene->getTexts()[i]->draw();
	}
}

GuiRenderer::~GuiRenderer()
{

}
