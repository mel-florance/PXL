#include "guiManager.h"

#include "nanovg.h"
#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg_gl.h"

GuiManager::GuiManager()
{
	m_ctx = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);

	if (m_ctx == NULL)
		std::cout << "Could not init nanovg.\n" << std::endl;
	else
		this->loadFonts("./res/fonts/");
}

void GuiManager::loadFonts(char* path)
{
	DIR *dir;
	struct dirent* directory;
	dir = opendir(path);

	if (dir)
	{
		while ((directory = readdir(dir)) != NULL)
		{
			std::string filename = directory->d_name;
			std::string name = filename.substr(0, filename.size() - 4);

			if (filename.at(0) != '.')
			{
				std::string fullpath = path + filename;
				nvgCreateFont(m_ctx, name.c_str(), fullpath.c_str());

				std::cout << "Loaded font " << name << std::endl;
			}
		}

		closedir(dir);
	}
}

GuiManager::~GuiManager()
{

}
