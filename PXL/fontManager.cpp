#include "fontManager.h"


FontManager::FontManager()
{
	this->loadFonts("./res/fonts/");
}

void FontManager::loadFonts(char* path)
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
				CBitmapFont font;
				std::string fullpath = path + filename;

				char* p = const_cast<char *>(fullpath.c_str());

				if (!font.Load(p))
					std::cout << "Error loading font: " << p << std::endl;
				else {
					m_fonts[name] = font;
					std::cout << "Loaded font: " << p << std::endl;
				}
			}
		}

		closedir(dir);
	}
}

FontManager::~FontManager()
{

}
