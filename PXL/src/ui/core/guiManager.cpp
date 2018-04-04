#include "guiManager.h"

#include "../nanovg/nanovg.h"
#define NANOVG_GL3_IMPLEMENTATION
#include "../nanovg/nanovg_gl.h"

GuiManager::GuiManager(Display* window, FontManager* fontManager) : Manager()
{
	m_window = window;
	m_ctx = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
	m_fontManager = fontManager;
	m_layerManager = new LayerManager();

	if (m_ctx == NULL)
		std::cout << "Could not init nanovg." << std::endl;
	else
	{
		m_fontManager->setContext(m_ctx);
		m_fontManager->loadFonts("./res/fonts/");
		std::cout << "Nanovg initialized." << std::endl;
	}
}

void GuiManager::handleWidgetEvent(Widget* widget, const SDL_Event& event, const std::string& name)
{
	widget->handleEvent(name, event);

	std::vector<class Widget*> childs = widget->getChildren();

	for (unsigned int i = 0; i < childs.size(); i++)
		this->handleWidgetEvent(childs[i], event, name);
}

void GuiManager::handleEvent(const std::string& name, const SDL_Event& event)
{
	for (unsigned int i = 0; i < m_layouts.size(); i++)
	{

		std::vector<class Widget*> widgets = m_layouts[i]->getWidgets();

		for (unsigned int j = 0; j < widgets.size(); j++)
			this->handleWidgetEvent(widgets[j], event, name);
	}
}

Layout* GuiManager::createLayout(const std::string& name, const glm::vec2& position, const glm::vec2& size)
{
	return this->addLayout(new Layout(name, m_window, position, size));
}

Layout* GuiManager::addLayout(Layout* layout)
{
	std::vector<class Widget*> widgets = layout->getWidgets();

	for (unsigned int j = 0; j < widgets.size(); j++)
		widgets[j]->setWindow(m_window);

	m_layouts.emplace_back(layout);
	return layout;
}

void GuiManager::removeLayout(Layout* layout)
{
	m_layouts.erase(std::remove(m_layouts.begin(), m_layouts.end(), layout), m_layouts.end());
}

GuiManager::~GuiManager()
{
}
