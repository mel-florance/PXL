#pragma once

#include <vector>
#include <string>
#include <algorithm>

#include "widget.h"

class Layout : public Widget
{
public:
	Layout(const std::string& name, const glm::vec2& position, const glm::vec2& size);

	inline std::vector<class Widget*> getWidgets() { return m_widgets; }
	virtual void addWidget(Widget* widget);
	void Layout::setWidgetWindow(Widget* widget);
	virtual void removeWidget(Widget* widget);

	~Layout();

private:
	std::string m_name;
	std::vector<class Widget*> m_widgets;
};

