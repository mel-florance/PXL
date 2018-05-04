#pragma once

#include <map>
#include <algorithm>
#include <string>

#include <glm\glm.hpp>
#include "../core/widget.h"
#include "../../core/util.h"

class Icon : public Widget
{
public:
	typedef std::map<std::string, int> SymbolsMap;

	Icon(const std::string& name, const glm::vec2& position, const glm::vec2& size);

	void onMouseMove(const SDL_Event& event);

	inline void setSymbol(const std::string& name) { m_symbol = m_icons[name]; }
	virtual char* get();
	inline int getSymbol() { return m_symbol; }

	~Icon();

private:
	int m_symbol;
	char m_str[8];
	SymbolsMap m_icons;
};
