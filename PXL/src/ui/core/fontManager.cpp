
#include "fontManager.h"

 FontManager::FontManager() {


}

void FontManager::loadFonts(char & path) {

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

 FontManager::~FontManager() {


}

