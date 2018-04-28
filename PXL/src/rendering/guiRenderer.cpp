#include "guiRenderer.h"
#include "../ui/widgets/layout.h"

GuiRenderer::GuiRenderer(GuiManager* guiManager, Display* window)
{
	m_guiManager = guiManager;
	m_window = window;
	m_drawLayouts = false;
}

void GuiRenderer::updateWidget(Widget* widget, double delta)
{
	if (widget->getState("visible"))
	{
		widget->setScreen(m_window->getSize());
		widget->update(delta);
		widget->draw(m_guiManager->getContext(), delta);

		for (const auto& child : widget->getChildren())
			this->updateWidget(child, delta);
	}
}

void GuiRenderer::renderLayout(Layout* layout, Layout* previous, unsigned int index, unsigned int depth, double delta)
{
	NVGcontext* ctx = m_guiManager->getContext();

	if (layout->needRecomputeStackDirection())
		layout->computeStackDirection(previous, index);

	if (m_drawLayouts)
		layout->draw(ctx);

	auto childs = layout->getChildren();

	for (unsigned int i = 0; i < childs.size(); i++)
	{
		Layout* previous = nullptr;

		if(i > 0)
			previous = childs[i - 1];

		this->renderLayout(childs[i], previous, i, depth, delta);
	}

	for (const auto& widget : layout->getWidgets())
		this->updateWidget(widget, delta);

	depth++;
}

void GuiRenderer::renderLayoutSplitter(Layout* layout, unsigned int index, double delta)
{
	layout->updateSplitter(delta, index);
	layout->drawSplitter(m_guiManager->getContext(), delta);

	auto childs = layout->getChildren();

	for (unsigned int i = 0; i < childs.size(); i++)
		this->renderLayoutSplitter(childs[i], i, delta);
}

void GuiRenderer::render(Scene* scene, double delta)
{
	nvgBeginFrame(m_guiManager->getContext(), (int)m_window->getSize().x, (int)m_window->getSize().y, 1.0f);

	this->renderLayout(m_guiManager->getMainLayout(), nullptr, 0, 0, delta);
	this->renderLayoutSplitter(m_guiManager->getMainLayout(), 0, delta);

	for (auto layer : m_guiManager->getLayerManager()->getLayers())
	{
		std::vector<Widget*> widgets = layer.second;

		for (unsigned i = widgets.size() - 1; widgets.size() > i; --i)
			this->updateWidget(widgets[i], delta);
	}

	nvgEndFrame(m_guiManager->getContext());
}

GuiRenderer::~GuiRenderer()
{

}
