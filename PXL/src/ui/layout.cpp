#include "layout.h"

Layout::Layout(const std::string& name) : m_name(name)
{

}

void Layout::addWidget(Widget* widget)
{
	std::vector<class Widget*> childs;
	size_t size = childs.size();

	if (size > 0)
		for (unsigned int i = 0; i < size; i++)
			this->addWidget(childs[i]);

	m_widgets.emplace_back(widget);
}

void Layout::removeWidget(Widget* widget)
{
	m_widgets.erase(std::remove(m_widgets.begin(), m_widgets.end(), widget), m_widgets.end());
}

Layout::~Layout()
{

}
