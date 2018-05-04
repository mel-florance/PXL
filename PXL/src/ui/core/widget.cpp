
#include "widget.h"
#include "display.h"
#include "layout.h"
#include "icon.h"

 Widget::Widget(const glm::vec2 & position, const glm::vec2 & size) {

	m_name = "";
	m_units = "px";
	m_alignment = Alignment::TOP_LEFT;
	m_expandModeX = ExpandMode::LAYOUT;
	m_expandModeY = ExpandMode::LAYOUT;
	m_positionModeX = ExpandMode::LAYOUT;
	m_positionModeY = ExpandMode::LAYOUT;
}

 Widget::~Widget() {

	delete m_icon;
}

glm::vec2 Widget::getRelativePosition() {

	glm::vec2 pos = this->getPosition();
	glm::vec2 size = this->getRelativeSize();

	switch (this->getPositionModeX())
	{
		case LAYOUT:
			switch (m_alignment)
			{
				case TOP:
				case BOTTOM:
					pos.x = this->getLayout()->getComputedPosition().x + (this->getLayout()->getComputedSize().x * 0.5f) - (size.x * 0.5f);
					break;
				case TOP_RIGHT:
				case RIGHT:
				case BOTTOM_RIGHT: 
					pos.x += this->getLayout()->getComputedPosition().x + this->getLayout()->getComputedSize().x - (size.x * 2.0f);
					break;
				case TOP_LEFT:
				case BOTTOM_LEFT:
				case LEFT:
					pos.x = this->getLayout()->getComputedPosition().x;
					break;
			}
		break;

		case PARENT:
			if (this->getParent() != nullptr)
			{
				switch (m_alignment)
				{
				case TOP:
				case BOTTOM:
					pos.x += this->getParent()->getRelativePosition().x + (this->getParent()->getRelativeSize().x * 0.5f) - (size.x * 0.5f);
					break;
				case TOP_RIGHT:
				case RIGHT:
				case BOTTOM_RIGHT:
					pos.x += this->getParent()->getRelativePosition().x + this->getParent()->getRelativeSize().x - (size.x);
					break;
				case TOP_LEFT:
				case BOTTOM_LEFT:
				case LEFT:
					pos.x += this->getParent()->getRelativePosition().x;
					break;
				}
			}
				
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
			if (this->getParent() != nullptr) {
				pos.y += this->getParent()->getRelativePosition().y;
			}
			break;
		case FIXED:
			pos.y = this->getPosition().y;
			break;
	}

	return pos;
}

glm::vec2 Widget::getRelativeSize() {

	glm::vec2 size = this->getSize();

	switch (this->getExpandModeX())
	{
	case LAYOUT:
		size.x = this->getLayout()->getComputedSize().x;
		break;
	case PARENT:
		size.x = this->getParent()->getRelativeSize().x;
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
		size.y = this->getParent()->getRelativeSize().y;
		break;
	case FIXED:
		size.y = this->getSize().y;
		break;
	}

	return size;
}

void Widget::setCentered() {

	Display* window = this->getWindow();

	if (window != nullptr)
	{
		glm::vec2 size = this->getRelativeSize();
		glm::vec2 position = (window->getSize() - size) * 0.5f;
		this->setComputedPosition(position);
	}
}

bool Widget::intersects(const glm::vec2 & point) {

	glm::vec2 pos = this->getRelativePosition();

	return point.x > pos.x
		&& point.x < pos.x + this->getRelativeSize().x
		&& point.y > pos.y
		&& point.y < pos.y + this->getRelativeSize().y;
}

void Widget::addChild(Widget & child) {

	child->setParent(this);
	child->setState("visible", true);
	m_children.push_back(child);
}

void Widget::onClosed(const CallbackData & data)
{

	data.sender->getLayout()->removeWidget(data.sender);
}

void Widget::setIcon(Icon & icon) {

	icon->setParent(this);
	m_icon = icon;
}

Icon Widget::getIcon() {

	return m_icon;
}

void Widget::computePosition() {

	this->setComputedPosition((this->getPosition() * this->getParent()->getSize()) / 100.0f);
}

void Widget::computeSize() {

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

