#include "shaderManager.h"
#include <dirent.h>

ShaderManager::ShaderManager()
{
	this->loadShaders("./res/shaders/");
}

void ShaderManager::loadShaders(const std::string& path)
{
	DIR *dir;
	struct dirent* directory;
	dir = opendir(path.c_str());

	if (dir)
	{
		while ((directory = readdir(dir)) != NULL)
		{
			std::string filename = directory->d_name;
			
			if (filename.at(0) != '.')
			{
				std::string shaderName = filename.substr(0, filename.size() - 3);


				std::cout << shaderName << std::endl;
			}
		}

		closedir(dir);
	}
}

ShaderManager::~ShaderManager()
{

}
