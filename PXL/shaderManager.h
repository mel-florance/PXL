#pragma once

#include "shader.h"
#include <string>
#include <map>
#include <filesystem>
#include <iostream>


class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	void loadShaders(const std::string& path);
	void addShader(const std::string& name, Shader* shader) { m_shaders[name] = shader; }
	inline Shader* getShader(const std::string& name) { return m_shaders[name]; }

private:
	std::map<std::string, Shader*> m_shaders;
};

