#pragma once

#include "../core/display.h"
#include "../scene/scene.h"
#include "../shaders/shaderManager.h"
#include "../shaders/shader.h"
#include "../assets/assetManager.h"
#include "../ui/core/guiManager.h"

#include "guiRenderer.h"
#include "entityRenderer.h"
#include "skyboxRenderer.h"

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

