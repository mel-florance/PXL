#include "icon.h"

Icon::Icon(const std::string& name, const glm::vec2& position, const glm::vec2& size) : Widget(position, size)
{
	m_icons["CHECK"] = 0x2713;
	m_icons["LOGIN"] = 0xE740;
	m_icons["TRASH"] = 0xE729;
	m_icons["SEARCH"] = 0x1F50D;
	m_icons["ICON_CANCEL"] = 0x2715; //Fixme: Not working, why??
	m_icons["CIRCLED_CROSS"] = 0x2716;
	m_icons["CANCEL_SQUARED"] = 0x274e;
	m_icons["CHEVRON_RIGHT"] = 0xE75E;
	m_icons["NEW_DOCUMENT"] = 0xe730;
	m_icons["FORWARD"] = 0x27a6;
	m_icons["FOLDER_OPENED"] = 0x1f4c1;
	m_icons["FLOPPY_DISK"] = 0x1f4be;
	m_icons["REPLY"] = 0xe712;
	m_icons["EXIT"] = 0xe741;
	m_icons["HELP_CIRCLED"] = 0xe704;
	m_icons["RESIZE_FULL"] = 0xe744;
	m_icons["PLUS_CIRCLED"] = 0x2795;
	m_icons["RIGHT_DIR"] = 0x25b8;
	m_icons["DOWN_DIR"] = 0x25be;
	m_icons["TOP_DIR"] = 0x25b4;
	m_icons["COG"] = 0x2699;

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