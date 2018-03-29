#pragma once

#include <map>
#include <set>
#include <string>
#include <filesystem>
#include <iostream>

#include <dirent.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "nanovg.h"

class GuiManager
{
public:
	GuiManager();
	~GuiManager();

	void loadFonts(char* path);
	NVGcontext* getContext() { return m_ctx; }

private:
	NVGcontext* m_ctx;
};

