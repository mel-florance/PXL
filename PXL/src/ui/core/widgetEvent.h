#pragma once

#include <map>
#include <string>

#include <SDL2\SDL.h>

class WidgetEvent
{
public:
	WidgetEvent();

	typedef void (WidgetEvent::*EventFnPtr)(const SDL_Event& event);

	void handleEvent(const std::string& name, const SDL_Event& event);

	virtual void onKeyDown(const SDL_Event& event) {}
	virtual void onTextInput(const SDL_Event& event) {}
	virtual void onKeyUp(const SDL_Event& event) {}
	virtual void onMouseWheel(const SDL_Event& event) {}
	virtual void onMouseMove(const SDL_Event& event) {}
	virtual void onMouseDown(const SDL_Event& event) {}
	virtual void onMouseUp(const SDL_Event& event) {}
	virtual void onWindowResized(const SDL_Event& event) {}
	virtual void onWindowSizeChanged(const SDL_Event& event) {}

	~WidgetEvent();

private:
	std::map<std::string, EventFnPtr> m_events;
};

