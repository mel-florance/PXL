#include "guiRenderer.h"

GuiRenderer::GuiRenderer(GuiManager* guiManager, Display* window)
{
	m_guiManager = guiManager;
	m_window = window;
}

void GuiRenderer::updateWidget(Widget* widget, float delta)
{
	widget->setScreen(m_window->getSize());
	widget->update(delta);
	widget->draw(m_guiManager->getContext(), delta);

	for (unsigned int i = 0; i < widget->getChildren().size(); i++)
		this->updateWidget(widget->getChildren()[i], delta);
}

void GuiRenderer::render(Scene* scene, double delta)
{
	nvgBeginFrame(m_guiManager->getContext(), (int)m_window->getSize().x, (int)m_window->getSize().y, 1.0f);

	std::vector<class Layout*> layouts = m_guiManager->getLayouts();

	for (unsigned int i = 0; i < layouts.size(); i++)
	{
		std::vector<class Widget*> widgets = layouts[i]->getWidgets();

		for (unsigned int j = 0; j < widgets.size(); j++)
			this->updateWidget(widgets[j], delta);
	}

	nvgEndFrame(m_guiManager->getContext());
}

GuiRenderer::~GuiRenderer()
{

}
