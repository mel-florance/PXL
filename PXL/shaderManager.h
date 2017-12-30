#pragma once

#include <string>
#include <map>
#include <filesystem>
#include <iostream>
#include <set>

#include <dirent.h>

#include "shader.h"

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	void loadShaders(const std::string& path);
	void addShader(const std::string& name, Shader* shader) { m_shaders[name] = shader; }
	inline Shader* getShader(const std::string& name) { return m_shaders[name]; }

private:
	std::string m_shadersDir = "./res/shaders/";
	std::map<std::string, Shader*> m_shaders;
	std::set<std::string> m_shadersList;
};

