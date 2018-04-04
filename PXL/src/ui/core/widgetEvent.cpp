#include "widgetEvent.h"

WidgetEvent::WidgetEvent()
{
	m_events.emplace("onKeyDown", &WidgetEvent::onKeyDown);
	m_events.emplace("onTextInput", &WidgetEvent::onTextInput);
	m_events.emplace("onKeyUp", &WidgetEvent::onKeyUp);
	m_events.emplace("onMouseMove", &WidgetEvent::onMouseMove);
	m_events.emplace("onMouseDown", &WidgetEvent::onMouseDown);
	m_events.emplace("onMouseUp", &WidgetEvent::onMouseUp);
	m_events.emplace("onWindowResized", &WidgetEvent::onWindowResized);
	m_events.emplace("onWindowSizeChanged", &WidgetEvent::onWindowSizeChanged);
}

void WidgetEvent::handleEvent(const std::string& name, const SDL_Event& event)
{
	EventFnPtr fn = m_events[name];

	if (fn != 0)
		return (this->*fn)(event);
}

WidgetEvent::~WidgetEvent()
{
}
