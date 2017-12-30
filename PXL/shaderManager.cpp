#include "shaderManager.h"


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
				m_shadersList.emplace(shaderName);
			}
		}

		std::set<std::string>::iterator i;

		for (i = m_shadersList.begin(); i != m_shadersList.end(); ++i) {
			std::string filename = m_shadersDir + *i;
			Shader* shader = new Shader(filename);
			m_shaders[*i] = shader;
			std::cout << "Loaded shader: " << *i << std::endl;
		}

		closedir(dir);
	}
}

ShaderManager::~ShaderManager()
{
	std::set<std::string>::iterator i;
	for (i = m_shadersList.begin(); i != m_shadersList.end(); ++i) {
		delete m_shaders[*i];
	}
}
