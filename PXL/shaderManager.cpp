#include "shaderManager.h"
#include <dirent.h>

ShaderManager::ShaderManager()
{
	this->loadShaders("./res/shaders");
}


ShaderManager::~ShaderManager()
{
}

void ShaderManager::loadShaders(const std::string& path)
{
	DIR *dirp;
	struct dirent* directory;
	dirp = opendir(path.c_str());

	if (dirp)
	{
		while ((directory = readdir(dirp)) != NULL)
		{
			printf("%s\n", directory->d_name);
		}

		closedir(dirp);
	}
}
