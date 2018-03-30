#pragma once

#include "../mesh/mesh.h"
#include "../core/loader.h"
#include "../mesh/meshFactory.h"
#include "../shaders/shaderManager.h"
#include "../materials/skyboxMaterial.h"
#include "../scene/scene.h"

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
