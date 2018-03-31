#pragma once

#include <map>
#include <set>
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

#include <dirent.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "nanovg.h"
#include "layout.h"
#include "widget.h"

class GuiManager
{
public:
	GuiManager();
	~GuiManager();

	void loadFonts(char* path);
	NVGcontext* getContext() { return m_ctx; }

	inline std::vector<class Layout*> getLayouts() { return m_layouts; }
	void addLayout(Layout* layout);
	void removeLayout(Layout* layout);

	void onKeyDown(const SDL_Event& event);
	void onTextInput(const SDL_Event& event);
	void onKeyUp(const SDL_Event& event);

	void onMouseMove(const glm::vec2& mouse, const glm::vec2& rel);
	void onMouseDown(Uint8 button);
	void onMouseUp(Uint8 button);

private:
	NVGcontext* m_ctx;
	std::vector<class Layout*> m_layouts;
};

