#include "guiManager.h"

#include "nanovg.h"
#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg_gl.h"

GuiManager::GuiManager(FontManager* fontManager)
{
	m_ctx = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
	m_fontManager = fontManager;

	if (m_ctx == NULL)
		std::cout << "Could not init nanovg." << std::endl;
	else
	{
		m_fontManager->setContext(m_ctx);
		m_fontManager->loadFonts("./res/fonts/");
		std::cout << "Nanovg initialized." << std::endl;
	}
}

void GuiManager::addLayout(Layout* layout)
{
	m_layouts.emplace_back(layout);
}

void GuiManager::removeLayout(Layout* layout)
{
	m_layouts.erase(std::remove(m_layouts.begin(), m_layouts.end(), layout), m_layouts.end());
}

void GuiManager::onKeyDown(const SDL_Event& event)
{
	for (unsigned int i = 0; i < m_layouts.size(); i++) 
	{
		std::vector<class Widget*> widgets = m_layouts[i]->getWidgets();

		for (unsigned int i = 0; i < widgets.size(); i++)
			widgets[i]->onKeyDown(event);
	}
}

void GuiManager::onTextInput(const SDL_Event& event)
{
	for (unsigned int i = 0; i < m_layouts.size(); i++)
	{
		std::vector<class Widget*> widgets = m_layouts[i]->getWidgets();

		for (unsigned int i = 0; i < widgets.size(); i++)
			widgets[i]->onTextInput(event);
	}
}

void GuiManager::onKeyUp(const SDL_Event& event)
{
	for (unsigned int i = 0; i < m_layouts.size(); i++)
	{
		std::vector<class Widget*> widgets = m_layouts[i]->getWidgets();

		for (unsigned int i = 0; i < widgets.size(); i++)
			widgets[i]->onKeyUp(event);
	}
}

void GuiManager::onMouseMove(const glm::vec2& mouse, const glm::vec2 & rel)
{
	for (unsigned int i = 0; i < m_layouts.size(); i++)
	{
		std::vector<class Widget*> widgets = m_layouts[i]->getWidgets();

		for (unsigned int i = 0; i < widgets.size(); i++)
			widgets[i]->onMouseMove(mouse, rel);
	}

}

void GuiManager::onMouseDown(Uint8 button)
{
	for (unsigned int i = 0; i < m_layouts.size(); i++)
	{
		std::vector<class Widget*> widgets = m_layouts[i]->getWidgets();

		for (unsigned int i = 0; i < widgets.size(); i++)
			widgets[i]->onMouseDown(button);
	}
}

void GuiManager::onMouseUp(Uint8 button)
{
	for (unsigned int i = 0; i < m_layouts.size(); i++)
	{
		std::vector<class Widget*> widgets = m_layouts[i]->getWidgets();

		for (unsigned int i = 0; i < widgets.size(); i++)
			widgets[i]->onMouseUp(button);
	}
}

GuiManager::~GuiManager()
{
}
