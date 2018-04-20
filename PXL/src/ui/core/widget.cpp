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

	switch (this->getPositionModeX())
	{
	case LAYOUT:
		pos.x = this->getLayout()->getComputedPosition().x;
		break;
	case PARENT:
		pos.x = this->getParent()->getComputedPosition().x;
		break;
	case FIXED:
		pos.x = this->getPosition().x;
		break;
	}

	switch (this->getPositionModeY())
	{
	case LAYOUT:
		pos.y = this->getLayout()->getComputedPosition().y;
		break;
	case PARENT:
		pos.y = this->getParent()->getComputedPosition().y;
		break;
	case FIXED:
		pos.y = this->getPosition().y;
		break;
	}

	return pos;
}

glm::vec2 Widget::getRelativeSize()
{
	glm::vec2 size = this->getSize();

	switch (this->getExpandModeX())
	{
	case LAYOUT:
		size.x = this->getLayout()->getComputedSize().x;
		break;
	case PARENT:
		size.x = this->getParent()->getSize().x;
		break;
	case FIXED:
		size.x = this->getSize().x;
		break;
	}

	switch (this->getExpandModeY())
	{
	case LAYOUT:
		size.y = this->getLayout()->getComputedSize().y;
		break;
	case PARENT:
		size.y = this->getParent()->getSize().y;
		break;
	case FIXED:
		size.y = this->getSize().y;
		break;
	}

	return size;
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
		&& point.x < pos.x + this->getRelativeSize().x
		&& point.y > pos.y
		&& point.y < pos.y + this->getRelativeSize().y;
}

void Widget::addChild(Widget* child)
{
	child->setParent(this);
	child->setState("visible", true);
	m_children.push_back(child);
}

void Widget::computePosition()
{
	this->setComputedPosition((this->getPosition() * this->getParent()->getSize()) / 100.0f);
}

void Widget::computeSize()
{
	glm::vec2 parentSize = this->getParent()->getRelativeSize();
	glm::vec2 size = (parentSize * this->getSize()) / 100.0f;

	if (m_minWidth != NULL) {
		if (size.x < m_minWidth) size.x = m_minWidth;
	}
	else if (m_maxWidth != NULL) {
		if (size.x > m_maxWidth) size.x = m_maxWidth;
	}
	else if (m_minHeight != NULL) {
		if (size.y < m_minHeight) size.y = m_minHeight;
	}
	else if (m_maxHeight != NULL) {
		if (size.y > m_maxHeight) size.y = m_maxHeight;
	}

	this->setComputedSize(size);
}

Widget::~Widget()
{
	delete m_icon;
}