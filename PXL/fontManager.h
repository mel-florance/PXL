#pragma once

#include <string>
#include <map>
#include <filesystem>
#include <iostream>
#include <set>
#include <dirent.h>

#include "bitmapFont.h"

class FontManager
{
public:
	FontManager();
	~FontManager();

	void loadFonts(char* path);
	inline void addFont(const std::string& name, CBitmapFont font) { m_fonts[name] = font; }
	inline CBitmapFont getFont(const std::string& name) { return m_fonts[name]; }

private:
	std::map<std::string, CBitmapFont> m_fonts;
};

