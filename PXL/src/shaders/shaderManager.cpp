#include "shaderManager.h"

ShaderManager::ShaderManager() : Manager()
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
				m_shadersList.emplace(filename.substr(0, filename.size() - 8));
		}

		std::set<std::string>::iterator i;

		for (i = m_shadersList.begin(); i != m_shadersList.end(); ++i) {
			std::string filename = path + *i;
			Shader* shader = new Shader(filename);
			m_shaders[*i] = shader;
			std::cout << "Loaded shader: " << path + *i << std::endl;
		}

		closedir(dir);
	}
}

ShaderManager::~ShaderManager()
{
	std::set<std::string>::iterator i;
	for (i = m_shadersList.begin(); i != m_shadersList.end(); ++i)
		delete m_shaders[*i];
}
