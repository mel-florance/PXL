#include "icon.h"

Icon::Icon(const std::string& name, const glm::vec2& position, const glm::vec2& size) : Widget(position, size)
{
	m_icons["CHECK"] = 0x2713;
	m_icons["LOGIN"] = 0xE740;
	m_icons["TRASH"] = 0xE729;
	m_icons["SEARCH"] = 0x1F50D;
	m_icons["CIRCLED_CROSS"] = 0x2716;
	m_icons["CHEVRON_RIGHT"] = 0xE75E;

	this->setSymbol(name);
}

void Icon::onMouseMove(const SDL_Event& event)
{
	
}

char* Icon::get()
{
	return Utils::cpToUTF8(m_symbol, m_str);
}

Icon::~Icon() 
{

}