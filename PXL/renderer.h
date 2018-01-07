#pragma once

#include "scene.h"
#include "shaderManager.h"
#include "shader.h"
#include "entityRenderer.h"
#include "guiRenderer.h"

class Renderer
{
public:
	Renderer(ShaderManager* shaderManager, AssetManager* assetManager);
	~Renderer();

	void render(Scene* scene);

private:
	EntityRenderer* m_entityRenderer;
	GuiRenderer* m_guiRenderer;
};

