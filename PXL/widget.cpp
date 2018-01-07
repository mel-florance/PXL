#include "widget.h"

Widget::Widget()
{
	m_transform = new Transform();
}

Widget::~Widget()
{
	if(m_transform != nullptr)
		delete m_transform;

	if(m_texture != nullptr)
		delete m_texture;
}
