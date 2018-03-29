#include "guiRenderer.h"

GuiRenderer::GuiRenderer(GuiManager* guiManager, Display* window)
{
	m_guiManager = guiManager;
	m_window = window;


}

void GuiRenderer::render(Scene* scene, double delta)
{
	nvgBeginFrame(m_guiManager->getContext(), (int)m_window->getSize().x, (int)m_window->getSize().y, 1.0f);

	for (unsigned int i = 0; i < scene->getWidgets().size(); ++i)
	{
		scene->getWidgets()[i]->setScreen(m_window->getSize());
		scene->getWidgets()[i]->update(delta);
		scene->getWidgets()[i]->draw(m_guiManager->getContext(), delta);

		for (unsigned int j = 0; j < scene->getWidgets()[i]->getChildren().size(); j++)
		{
			scene->getWidgets()[i]->getChildren()[j]->setScreen(m_window->getSize());
			scene->getWidgets()[i]->getChildren()[j]->update(delta);
			scene->getWidgets()[i]->getChildren()[j]->draw(m_guiManager->getContext(), delta);
		}
	}

	nvgEndFrame(m_guiManager->getContext());
}

GuiRenderer::~GuiRenderer()
{

}
