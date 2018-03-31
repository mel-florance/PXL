#pragma once

#include <iostream>
#include <filesystem>
#include <dirent.h>

#include "nanovg.h"

class FontManager
{
public:
	FontManager();

	inline void setContext(NVGcontext* ctx) { m_ctx = ctx; }
	void loadFonts(char* path);

	virtual ~FontManager();

private:
	NVGcontext* m_ctx;
};

