#pragma once

#include "mesh.h"
#include "loader.h"
#include "meshFactory.h"
#include "shaderManager.h"
#include "skyboxMaterial.h"
#include "scene.h"

class SkyboxRenderer
{
public:
	SkyboxRenderer(Loader* loader, ShaderManager* shaderManager);
	~SkyboxRenderer();

	void render(Scene* scene, double delta);

private:
	Loader* m_loader;
	Mesh* m_mesh;
	SkyboxMaterial* m_material;
	ShaderManager* m_shaderManager;
	Shader* m_skyboxShader;
};

