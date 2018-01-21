#pragma once

#include "scene.h"
#include "shaderManager.h"
#include "shader.h"
#include "entityRenderer.h"
#include "guiRenderer.h"
#include "skyboxRenderer.h"
#include "display.h"

class Renderer
{
public:
	Renderer(Display* window, Loader* loader, ShaderManager* shaderManager, AssetManager* assetManager);
	~Renderer();

	void render(Scene* scene, double delta);

private:
	Display* m_window;
	Loader* m_loader;
	EntityRenderer* m_entityRenderer;
	GuiRenderer* m_guiRenderer;
	SkyboxRenderer* m_skyboxRenderer;
};

