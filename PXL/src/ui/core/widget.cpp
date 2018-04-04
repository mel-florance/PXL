#include "widget.h"
#include "../widgets/icon.h"

Widget::Widget(const glm::vec2& position = glm::vec2(0.0f, 0.0f), const glm::vec2& size = glm::vec2(250.0f, 250.0f))
{
	m_rect = new Rect(position, size);
}

glm::vec2 Widget::getRelativePosition()
{
	glm::vec2 pos = this->getPosition();

	if (this->getParent() != nullptr)
		pos += this->getParent()->getRelativePosition();

	return pos;
}

void Widget::setIcon(Icon* icon)
{
	icon->setParent(this);
	m_icon = icon;
}


Icon* Widget::getIcon() 
{
	return m_icon;
}

void Widget::setCentered()
{
	Display* window = this->getWindow();

	if (window != nullptr)
	{
		glm::vec2 size = this->getSize();
		glm::vec2 position = (window->getSize() - size) * 0.5f;
		this->setPosition(position);
	}
}

bool Widget::intersects(const glm::vec2& point)
{
	glm::vec2 pos = this->getRelativePosition();

	return point.x > pos.x
		&& point.x < pos.x + this->getSize().x
		&& point.y > pos.y
		&& point.y < pos.y + this->getSize().y;
}

void Widget::addChild(Widget* child)
{
	child->setParent(this);
	m_children.push_back(child);
}

Widget::~Widget()
{
	delete m_rect;
}