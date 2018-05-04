#pragma once
#include <iterator>
#include <vector>
#include <algorithm>
#include "../scene/scene.h"
#include "../core/display.h"
#include "../ui/core/guiManager.h"

class GuiRenderer
{
public:
	GuiRenderer(GuiManager* guiManager, Display* window);
	~GuiRenderer();

	void updateWidget(Widget* widget, double delta);
	void render(Scene* scene, double delta);
	void renderLayout(Layout* layout, Layout* previous, unsigned int index, unsigned int depth, double delta);
	void renderLayoutSplitter(Layout* layout, unsigned int index, double delta);

private:
	bool m_drawLayouts;
	Display* m_window;
	GuiManager* m_guiManager;
};