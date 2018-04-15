#include "widget.h"
#include "../widgets/icon.h"
#include "../widgets/layout.h"

Widget::Widget(const glm::vec2& position, const glm::vec2& size) : Rect(position, size)
{
	m_name = "";
	m_units = "px";
	m_expandModeX = ExpandMode::LAYOUT;
	m_expandModeY = ExpandMode::LAYOUT;
	m_positionModeX = ExpandMode::LAYOUT;
	m_positionModeY = ExpandMode::LAYOUT;
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

void Widget::onClosed(CallbackData data)
{
	data.sender->getLayout()->removeWidget(data.sender);
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
	child->setState("visible", true);
	m_children.push_back(child);
}

Widget::~Widget()
{
	delete m_icon;
}