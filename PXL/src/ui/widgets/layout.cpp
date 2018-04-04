#include "layout.h"

Layout::Layout(const std::string& name, Display* window, const glm::vec2& position, const glm::vec2& size)
{
	m_name = name;
	m_window = window;
}

void Layout::addWidget(Widget* widget)
{
	this->setWidgetWindow(widget);
	widget->setLayout(this);
	m_widgets.emplace_back(widget);
}

void Layout::setWidgetWindow(Widget* widget) 
{
	if (m_window != nullptr) 
	{
 		widget->setWindow(m_window);

		std::vector<class Widget*> childs = widget->getChildren();

		for (unsigned int i = 0; i < childs.size(); i++)
			this->setWidgetWindow(childs[i]);
	}
}

void Layout::removeWidget(Widget* widget)
{
	m_widgets.erase(std::remove(m_widgets.begin(), m_widgets.end(), widget), m_widgets.end());
}

Layout::~Layout()
{

}
