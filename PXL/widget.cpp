#include "widget.h"

Widget::Widget(const std::string& name, Shader* shader) : m_name(name)
{
	m_transform = new Transform();
	m_material = new GuiMaterial("gui_mat", shader);
}

Widget::~Widget()
{
	if(m_transform != nullptr)
		delete m_transform;

	if (m_material != nullptr)
		delete m_material;
}
