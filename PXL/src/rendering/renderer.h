#pragma once

#include "../scene/scene.h"
#include "../shaders/shaderManager.h"
#include "../shaders/shader.h"
#include "../mesh/assetManager.h"
#include "../ui/guiManager.h"
#include "../core/display.h"

#include "skyboxRenderer.h"
#include "guiRenderer.h"
#include "entityRenderer.h"


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

