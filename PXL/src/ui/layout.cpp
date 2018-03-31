#include "layout.h"

Layout::Layout()
{

}

void Layout::addWidget(Widget* widget)
{
	m_widgets.emplace_back(widget);
}

void Layout::removeWidget(Widget* widget)
{
	m_widgets.erase(std::remove(m_widgets.begin(), m_widgets.end(), widget), m_widgets.end());
}

Layout::~Layout()
{

}
