#pragma once

#include "scene.h"
#include "display.h"
#include "guiManager.h"

class GuiRenderer
{
public:
	GuiRenderer(GuiManager* guiManager, Display* window);
	~GuiRenderer();

	void render(Scene* scene, double delta);

private:
	Display* m_window;
	GuiManager* m_guiManager;
};