#include "text.h"

Text::Text(const std::string& text, glm::vec3& color, int x, int y, CBitmapFont font) :
	m_text(text),
	m_color(color),
	m_x(x),
	m_y(y),
	m_font(font)
{

}

void Text::setScreen(Uint32 width, Uint32 height)
{
	m_screenWidth = width;
	m_screenHeight = height;
	m_font.Select();
	m_font.SetScreen(width, height);
}

void Text::draw()
{
	m_font.Select();
	m_font.SetColor(m_color.x, m_color.y, m_color.z);
	m_font.setScale(m_size);

	m_font.ezPrint(const_cast<char *>(m_text.c_str()), m_x * (1 / m_size.x), (m_screenHeight - m_y) * (1 / m_size.y));
}

Text::~Text()
{

}
