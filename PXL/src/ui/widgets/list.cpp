#include "list.h"

List::List(const glm::vec2& position, const glm::vec2& size, const std::string& font) : Widget(position, size)
{

	m_margin = glm::vec4(
		8.0f, // Top
		5.0f, // Right
		8.0f, // Bottom
		5.0f  // Left
	);

	m_font = font;
	m_fontSize = 20.0f;
	m_blur = 0.0f;
	m_align = NVG_ALIGN_LEFT;
	m_color = glm::vec4(255.0f, 255.0f, 255.0f, 255.0f);
	m_background = nvgRGBA(40, 40, 40, 255);
}

void List::update(double delta)
{

}

void List::addItem(const std::string& name)
{
	m_list.push_back(name);
}

void List::draw(NVGcontext* ctx, double delta)
{
	nvgSave(ctx);

	glm::vec2 pos = this->getRelativePosition();

	nvgBeginPath(ctx);
	nvgRect(ctx,
		pos.x,
		pos.y,
		this->getSize().x,
		this->getSize().y
	);

	nvgFillColor(ctx, m_background);
	nvgFill(ctx);

	nvgFontSize(ctx, m_fontSize);
	nvgFontFace(ctx, m_font.c_str());
	nvgTextAlign(ctx, m_align);
	nvgFontBlur(ctx, m_blur);
	nvgFillColor(ctx, nvgRGBA(
		(unsigned char)m_color.r,
		(unsigned char)m_color.g,
		(unsigned char)m_color.b,
		(unsigned char)m_color.a)
	);

	int i = 0;
	int lh = 20;
	for (auto& child : m_list)
	{
		i++;
		float y = pos.y + (lh * i);

		nvgText(ctx,
			pos.x,
			y,
			child.c_str(),
			NULL
		);

	}

	nvgRestore(ctx);
}

List::~List()
{

}
