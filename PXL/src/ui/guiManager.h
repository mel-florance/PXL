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

class GuiManager
{
public:
	GuiManager(FontManager* fontManager);
	~GuiManager();

	NVGcontext* getContext() { return m_ctx; }

	inline std::vector<class Layout*> getLayouts() { return m_layouts; }
	void addLayout(Layout* layout);
	void removeLayout(Layout* layout);

	void handleEvent(const std::string& name, const SDL_Event& event);

private:
	NVGcontext* m_ctx;
	FontManager* m_fontManager;
	std::vector<class Layout*> m_layouts;
};

