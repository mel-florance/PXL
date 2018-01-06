#pragma once

#include "scene.h"
#include "shaderManager.h"
#include "shader.h"

class Renderer
{
public:
	Renderer(ShaderManager* shaderManager);
	~Renderer();

	void render(Scene* scene);

private:
	ShaderManager* m_shaderManager;
	Shader* m_basicShader;
};

