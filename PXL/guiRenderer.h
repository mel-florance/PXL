#pragma once

#include "mesh.h"
#include "meshFactory.h"
#include "loader.h"
#include "widget.h"
#include "assetManager.h"

class GuiRenderer
{
public:
	GuiRenderer(AssetManager* assetManager);
	~GuiRenderer();

	void render(Scene* scene);

private:
	Mesh* m_quad;
	AssetManager* m_assetManager;
};