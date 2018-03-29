#pragma once

#include "scene.h"
#include "shaderManager.h"
#include "shader.h"
#include "entityRenderer.h"
#include "assetManager.h"
#include "skyboxRenderer.h"
#include "guiRenderer.h"
#include "guiManager.h"
#include "display.h"

class Renderer
{
public:
	Renderer(Display* window, Loader* loader, ShaderManager* shaderManager, AssetManager* assetManager, GuiManager* guiManager);
	~Renderer();

	void render(Scene* scene, double delta);

private:
	Display* m_window;
	Loader* m_loader;
	EntityRenderer* m_entityRenderer;
	SkyboxRenderer* m_skyboxRenderer;
	GuiRenderer* m_guiRenderer;
};

