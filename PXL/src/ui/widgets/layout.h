#pragma once

#include <vector>
#include <string>
#include <algorithm>

#include "../core/widget.h"

class GuiManager;
class AssetManager;

typedef enum { HORIZONTAL, VERTICAL } StackDirection;

class Layout
{
public:
	Layout(const std::string& name, Display* window, const glm::vec2& position, const glm::vec2& size);

	inline std::vector<class Widget*> getWidgets() { return m_widgets; }
	virtual void addWidget(Widget* widget);
	void setWidgetWindow(Widget* widget);
	void setWidgetLayout(Widget* widget);
	virtual void removeWidget(Widget* widget);

	void setGuiManager(GuiManager* guiManager) { m_guiManager = guiManager; }
	inline GuiManager* getGuiManager() { return m_guiManager; }

	void setDirection(StackDirection direction) { m_direction = direction; }
	StackDirection getDirection() { return m_direction; }

	void update(double delta);
	void draw(NVGcontext* ctx, double delta);

	void toggleAllWidgets();

	~Layout();

private:
	GuiManager* m_guiManager;
	StackDirection m_direction;
	std::string m_name;
	Display* m_window;
	std::vector<class Widget*> m_widgets;
};

