#pragma once

#include "mesh.h"
#include "meshFactory.h"
#include "loader.h"
#include "widget.h"
#include "assetManager.h"
#include "shader.h"

class GuiRenderer
{
public:
	GuiRenderer(AssetManager* assetManager, ShaderManager* shaderManager);
	~GuiRenderer();

	void render(Scene* scene);

private:
	Mesh* m_quad;
	Shader* m_guiShader;
	AssetManager* m_assetManager;
	ShaderManager* m_shaderManager;
};