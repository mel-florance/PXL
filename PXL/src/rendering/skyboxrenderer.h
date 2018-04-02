#pragma once

#include "../assets/loader.h"
#include "../scene/scene.h"
#include "../mesh/mesh.h"
#include "../mesh/meshFactory.h"
#include "../shaders/shaderManager.h"
#include "../materials/skyboxMaterial.h"

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
