#pragma once

#include "shaderManager.h"
#include "mesh.h"


class EntityRenderer
{
public:
	EntityRenderer(ShaderManager* shaderManager);
	~EntityRenderer();

	void render(Scene* scene);

private:
	ShaderManager* m_shaderManager;
	Shader* m_basicShader;
};

