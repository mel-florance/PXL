#pragma once

#include <vector>
#include <string>
#include <algorithm>

#include "../core/widget.h"

class Layout
{
public:
	Layout(const std::string& name, Display* window, const glm::vec2& position, const glm::vec2& size);

	inline std::vector<class Widget*> getWidgets() { return m_widgets; }
	virtual void addWidget(Widget* widget);
	void Layout::setWidgetWindow(Widget* widget);
	virtual void removeWidget(Widget* widget);

	~Layout();

private:
	std::string m_name;
	Display* m_window;
	std::vector<class Widget*> m_widgets;
};

