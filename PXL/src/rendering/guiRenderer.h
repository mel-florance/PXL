#pragma once

#include "../scene/scene.h"
#include "../core/display.h"
#include "../ui/guiManager.h"

class GuiRenderer
{
public:
	GuiRenderer(GuiManager* guiManager, Display* window);
	~GuiRenderer();

	void updateWidget(Widget* widget, float delta);
	void render(Scene* scene, double delta);

private:
	Display* m_window;
	GuiManager* m_guiManager;
};