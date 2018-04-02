#pragma once

#include <map>
#include <string>

class Widget;

struct CallbackData {
	Widget* sender;
};

class EventListener
{
public:
	EventListener();
	~EventListener();

	typedef void(*EventListenerFnPtr)(CallbackData);

	inline void addEventListener(std::string name, EventListenerFnPtr callback) {
		m_listeners[name] = callback; 
	}

	inline void handleEventListener(std::string name, CallbackData data)
	{
		EventListenerFnPtr fn = m_listeners[name];

		if (fn != 0)
			return (*fn)(data);
	}

private:
	std::map<std::string, EventListenerFnPtr> m_listeners;
};
