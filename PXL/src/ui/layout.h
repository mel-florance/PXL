#pragma once

#include <vector>
#include <algorithm>
#include "widget.h"

class Layout
{
public:
	Layout();

	inline std::vector<class Widget*> getWidgets() { return m_widgets; }
	virtual void addWidget(Widget* widget);
	virtual void removeWidget(Widget* widget);

	~Layout();

private:
	std::vector<class Widget*> m_widgets;
};

