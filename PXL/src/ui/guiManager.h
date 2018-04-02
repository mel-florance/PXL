#pragma once

#include <map>
#include <set>
#include <vector>
#include <string>
#include <functional>	
#include <iostream>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "nanovg.h"
#include "fontManager.h"
#include "layout.h"
#include "widget.h"

#include "../core/display.h"

class GuiManager
{
public:
	GuiManager(Display* window, FontManager* fontManager);
	~GuiManager();

	NVGcontext* getContext() { return m_ctx; }

	inline std::vector<class Layout*> getLayouts() { return m_layouts; }
	Layout* createLayout(const std::string& name, const glm::vec2& position = glm::vec2(0.0f, 0.0f), const glm::vec2& size = glm::vec2(0.0f, 0.0f));

	Layout* addLayout(Layout* layout);
	void removeLayout(Layout* layout);

	void handleWidgetEvent(Widget* widget, const SDL_Event& event, const std::string& name);
	void handleEvent(const std::string& name, const SDL_Event& event);

private:
	NVGcontext* m_ctx;
	Display* m_window;
	FontManager* m_fontManager;
	std::vector<class Layout*> m_layouts;
};

