#include "widget.h"

Widget::Widget(const glm::vec2& position, const glm::vec2& size)
{
	m_rect = new Rect(position, size);
	m_dragged = false;
	m_draggable = false;

	m_events.emplace("onKeyDown", &Widget::onKeyDown);
	m_events.emplace("onTextInput", &Widget::onTextInput);
	m_events.emplace("onKeyUp", &Widget::onKeyUp);
	m_events.emplace("onMouseMove", &Widget::onMouseMove);
	m_events.emplace("onMouseDown", &Widget::onMouseDown);
	m_events.emplace("onMouseUp", &Widget::onMouseUp);
	m_events.emplace("onWindowResized", &Widget::onWindowResized);
	m_events.emplace("onWindowSizeChanged", &Widget::onWindowSizeChanged);
}

void Widget::handleEvent(const std::string& name, const SDL_Event& event)
{
	EventFnPtr fn = m_events[name];
	if(fn != 0)
		return (this->*fn)(event);
}

void Widget::onTextInput(const SDL_Event& event)
{

}

void Widget::onKeyDown(const SDL_Event& event)
{

}

void Widget::onKeyUp(const SDL_Event& event)
{
}

void Widget::onMouseMove(const SDL_Event& event)
{
	m_mouse = glm::vec2((float)event.motion.x, (float)event.motion.y);
	m_mouseRel = glm::vec2((float)event.motion.xrel, (float)event.motion.yrel);
	m_hovered = this->intersects(m_mouse);
}

void Widget::onMouseDown(const SDL_Event& event)
{
}

void Widget::onMouseUp(const SDL_Event& event)
{
}

void Widget::onWindowResized(const SDL_Event& event)
{
	this->setScreen(glm::vec2(event.window.data1, event.window.data2));
}

void Widget::onWindowSizeChanged(const SDL_Event& event)
{
	this->setScreen(glm::vec2(event.window.data1, event.window.data2));
}

Widget::~Widget()
{
	delete m_rect;
}