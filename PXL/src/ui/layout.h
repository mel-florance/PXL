#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include "widget.h"

class Layout
{
public:
	Layout(const std::string& name);

	inline std::vector<class Widget*> getWidgets() { return m_widgets; }
	virtual void addWidget(Widget* widget);
	virtual void removeWidget(Widget* widget);

	~Layout();

private:
	std::string m_name;
	std::vector<class Widget*> m_widgets;
};

