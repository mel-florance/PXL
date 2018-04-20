#include "layout.h"
#include "../../assets/assetManager.h"
#include "../widgets/splitter.h"

Layout::Layout(const std::string& name, Display* window = nullptr, const glm::vec2& position = glm::vec2(0.0f), const glm::vec2& size = glm::vec2(100.0f, 100.0f))
{
	m_name = name;
	m_window = window;
	m_direction = VERTICAL;
	m_parent = nullptr;
	m_position = m_computedPosition = position;
	m_size = m_computedSize = size;
	m_expandModeX = m_expandModeY = m_positionModeX = m_positionModeY = PARENT;
	m_background = nvgRGBA(rand() % 255, rand() % 255, rand() % 255, 127);
	m_minWidth = m_maxWidth = m_minHeight = m_maxHeight = NULL;

	m_needRecomputeStackDirection = true;
	m_splitter = new Splitter(glm::vec2(0.0f), glm::vec2(0.0f));
	m_splitter->setLayout(this);
}

glm::vec2 Layout::getRelativePosition()
{
	glm::vec2 pos = this->getPosition();

	switch (this->getPositionModeX())
	{
	case WINDOW:
		pos.x = 0.0f;
		break;
	case PARENT:
		pos.x = this->getParent()->getComputedPosition().x;
		break;
	case FIXED:
		break;
	}

	switch (this->getPositionModeY())
	{
	case WINDOW:
		pos.y = 0.0f;
		break;
	case PARENT:
		pos.y = this->getParent()->getComputedPosition().y;
		break;
	case FIXED:
		break;
	}

	return pos;
}

glm::vec2 Layout::getRelativeSize()
{
	glm::vec2 size = this->getSize();

	switch (this->getExpandModeX())
	{
	case WINDOW:
		if (m_window != nullptr) {
			size.x = this->getWindow()->getSize().x;
		}
		break;
	case PARENT:
		size.x = this->getComputedSize().x;
		break;
	case FIXED:
		break;
	}

	switch (this->getExpandModeY())
	{
	case WINDOW:
		if (m_window != nullptr)
			size.y = this->getWindow()->getSize().y;
		break;
	case PARENT:
		size.y = this->getComputedSize().y;
		break;
	case FIXED:
		break;
	}

	return size;
}

void Layout::addWidget(Widget* widget)
{
	this->setWidgetLayout(widget);
	this->setWidgetWindow(widget);
	widget->setState("visible", true);
	m_widgets.emplace_back(widget);
}

void Layout::update(double delta)
{

}

void Layout::draw(NVGcontext* ctx, Layout* previous, unsigned int index, unsigned int depth, double delta)
{
	nvgSave(ctx);

	glm::vec2 pos = this->getRelativePosition();
	glm::vec2 size = this->getRelativeSize();
	
	nvgBeginPath(ctx);
	nvgRect(ctx, pos.x, pos.y, size.x, size.y);
	nvgFillColor(ctx, m_background);
	nvgFill(ctx);

	nvgRestore(ctx);
}

void Layout::drawSplitter(NVGcontext* ctx, unsigned int index, double delta)
{
	glm::vec2 pos = this->getComputedPosition();
	glm::vec2 size = this->getComputedSize();

	Layout* parent = this->getParent();
	StackDirection direction = this->getDirection();

	if (parent != nullptr)
	{
		if (index != parent->getChildren().size())
		{
			glm::vec2 splitterPos = glm::vec2(0.0f);
			glm::vec2 splitterSize = glm::vec2(0.0f);
			m_splitter->setExpandModeX(Widget::ExpandMode::FIXED);
			m_splitter->setExpandModeY(Widget::ExpandMode::FIXED);
			m_splitter->setPositionModeX(Widget::ExpandMode::FIXED);
			m_splitter->setPositionModeY(Widget::ExpandMode::FIXED);

			if (direction == VERTICAL)
			{
				splitterPos.x = pos.x;
				splitterPos.y = pos.y + size.y - 1.0f;
				splitterSize.x = size.x;
				splitterSize.y = 2.0f;

			}
			else if (direction == HORIZONTAL)
			{
				splitterPos.x = pos.x + size.x - 1.0f;
				splitterPos.y = pos.y;
				splitterSize.x = 2.0f;
				splitterSize.y = size.y;
			}

			m_splitter->setPosition(splitterPos);
			m_splitter->setSize(splitterSize);
			m_splitter->draw(ctx, delta);
		}
	}
}

void Layout::computeStackDirection(Layout* previous, unsigned int index)
{
	glm::vec2 pos = this->getRelativePosition();
	glm::vec2 size = this->getRelativeSize();

	if (previous != nullptr)
	{
		if (this->getDirection() == VERTICAL)
		{
			pos.y = previous->getComputedSize().y;
		}
		else if (this->getDirection() == HORIZONTAL)
		{
			pos.x = previous->getComputedSize().x;
		}
	}

	if (index > 0 && this->getParent() != nullptr) {
		Layout* PP = this->getParent()->getParent();

		if (PP != nullptr)
		{
			Layout* previous = this->getGuiManager()->getPrevious(PP);

			if (previous != nullptr) 
			{
				pos.y += previous->getComputedSize().y;
			}
		}
	}

	this->setComputedPosition(glm::vec2(pos.x, pos.y));
	this->setNeedRecomputeStackDirection(false);
}

void Layout::addChild(Layout* layout)
{
	layout->setParent(this);
	layout->computeSize();
	layout->computePosition();

	m_children.emplace_back(layout);
}

void Layout::toggleAllWidgets()
{
	for (unsigned int i = 0; i < m_widgets.size(); i++)
		m_widgets[i]->setState("visible", m_widgets[i]->getState("visible") != false);
}

void Layout::onWindowResized(const SDL_Event& event)
{

}

void Layout::computePosition()
{
	this->setComputedPosition((this->getPosition() * this->getParent()->getSize()) / 100.0f);
}

void Layout::computeSize()
{
	glm::vec2 parentSize = this->getParent()->getRelativeSize();
	glm::vec2 size = (parentSize * this->getSize()) / 100.0f;

	if (m_minWidth != NULL) {
		if (size.x < m_minWidth) size.x = m_minWidth;
	} else if (m_maxWidth != NULL) {
		if (size.x > m_maxWidth) size.x = m_maxWidth;
	} else if (m_minHeight != NULL) {
		if (size.y < m_minHeight) size.y = m_minHeight;
	} else if (m_maxHeight != NULL) {
		if (size.y > m_maxHeight) size.y = m_maxHeight;
	}

	this->setComputedSize(size);
}

void Layout::onWindowSizeChanged(const SDL_Event& event)
{
	Layout* root = this->getRoot();

	if (root == this) {
		this->setSize(glm::vec2(event.window.data1, event.window.data2));
	}
	else if (root != nullptr)
	{
		this->computeSize();
		this->computePosition();
	}

	this->setNeedRecomputeStackDirection(true);
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

void Layout::setWidgetLayout(Widget* widget)
{
	widget->setLayout(this);

	std::vector<class Widget*> childs = widget->getChildren();

	for (unsigned int i = 0; i < childs.size(); i++)
		this->setWidgetLayout(childs[i]);
}

void Layout::removeWidget(Widget* widget)
{
	m_widgets.erase(std::remove(m_widgets.begin(), m_widgets.end(), widget), m_widgets.end());
}

Layout::~Layout()
{
	delete m_splitter;
}
