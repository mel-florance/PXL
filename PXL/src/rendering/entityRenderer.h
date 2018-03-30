#pragma once

#include "../shaders/shaderManager.h"
#include "../mesh/mesh.h"


class EntityRenderer
{
public:
	EntityRenderer(ShaderManager* shaderManager);
	~EntityRenderer();

	void render(Scene* scene, double delta);

private:
	ShaderManager* m_shaderManager;
	Shader* m_basicShader;
};

