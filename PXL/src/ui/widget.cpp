#include "widget.h"

Widget::Widget(glm::vec2& position, glm::vec2& size)
{
	m_rect = new Rect(position, size);
	m_dragged = false;
}

Widget::~Widget()
{
	delete m_rect;
}