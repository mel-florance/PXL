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
#include "../editor/components/viewport.h"

class Renderer
{
public:
	Renderer(Display* window, Loader* loader, ShaderManager* shaderManager, AssetManager* assetManager, GuiManager* guiManager);
	~Renderer();

	void setViewport(Viewport* viewport) { m_viewport = viewport; }

	void render(Scene* scene, double delta);

private:
	Display* m_window;
	Loader* m_loader;
	Viewport* m_viewport;
	EntityRenderer* m_entityRenderer;
	SkyboxRenderer* m_skyboxRenderer;
	GuiRenderer* m_guiRenderer;
};

