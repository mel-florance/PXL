#pragma once

#include <map>
#include <algorithm>
#include <string>

class WidgetState
{
public:
	WidgetState();

	inline void addState(const std::string& name, bool state = false) { m_states[name] = state; }
	inline bool getState(const std::string& name) { return m_states[name]; }
	inline void setState(const std::string& name, bool value) { m_states[name] = value; }

	virtual ~WidgetState();

private:
	std::map<std::string, bool> m_states;
};
