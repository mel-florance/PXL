#include "guiRenderer.h"

GuiRenderer::GuiRenderer(GuiManager* guiManager, Display* window)
{
	m_guiManager = guiManager;
	m_window = window;
}

void GuiRenderer::render(Scene* scene, double delta)
{
	nvgBeginFrame(m_guiManager->getContext(), (int)m_window->getSize().x, (int)m_window->getSize().y, 1.0f);

	std::vector<class Layout*> layouts = m_guiManager->getLayouts();

	for (unsigned int i = 0; i < layouts.size(); i++)
	{
		std::vector<class Widget*> widgets = layouts[i]->getWidgets();

		for (unsigned int i = 0; i < widgets.size(); i++) {

			widgets[i]->setScreen(m_window->getSize());
			widgets[i]->update(delta);
			widgets[i]->draw(m_guiManager->getContext(), delta);

			for (unsigned int j = 0; j < widgets[i]->getChildren().size(); j++)
			{
				widgets[i]->getChildren()[j]->setScreen(m_window->getSize());
				widgets[i]->getChildren()[j]->update(delta);
				widgets[i]->getChildren()[j]->draw(m_guiManager->getContext(), delta);
			}
		}

	}

	nvgEndFrame(m_guiManager->getContext());
}

GuiRenderer::~GuiRenderer()
{

}
