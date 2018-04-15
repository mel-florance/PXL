#include "treeView.h"
#include "layout.h"

TreeView::TreeView(const glm::vec2& position, const glm::vec2& size, const std::string& font = "segoeui") : Widget(position, size)
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
	m_color = nvgRGBA(255, 255, 255, 100);
	m_background = nvgRGB(35, 35, 35);
	m_borderRadius = 0.0f;
	m_opacity = 1.0f;
}

void TreeView::draw(NVGcontext* ctx, double delta)
{
	nvgSave(ctx);

	glm::vec2 position = this->getRelativePosition();
	glm::vec2 size = this->getSize();

	switch (this->getExpandModeX())
	{
	case ExpandMode::LAYOUT:
		size.x = this->getLayout()->getComputedSize().x;
		break;
	case ExpandMode::PARENT:
		size.x = this->getParent()->getSize().x;
		break;
	case ExpandMode::FIXED:
		size.x = this->getSize().x;
		break;
	}

	switch (this->getExpandModeY())
	{
	case ExpandMode::LAYOUT:
		size.y = this->getLayout()->getComputedSize().y;
		break;
	case ExpandMode::PARENT:
		size.y = this->getParent()->getSize().y;
		break;
	case ExpandMode::FIXED:
		size.y = this->getSize().y;
		break;
	}

	switch (this->getPositionModeX())
	{
	case ExpandMode::LAYOUT:
		position.x = this->getLayout()->getComputedPosition().x;
		break;
	case ExpandMode::PARENT:
		position.x = this->getParent()->getPosition().x;
		break;
	case ExpandMode::FIXED:
		position.x = this->getPosition().x;
		break;
	}

	switch (this->getPositionModeY())
	{
	case ExpandMode::LAYOUT:
		position.y = this->getLayout()->getComputedPosition().y;
		break;
	case ExpandMode::PARENT:
		position.y = this->getParent()->getPosition().y;
		break;
	case ExpandMode::FIXED:
		position.y = this->getPosition().y;
		break;
	}

	nvgBeginPath(ctx);
	nvgRoundedRect(ctx,
		position.x,
		position.y + 30.0f,
		size.x,
		size.y - 30.0f,
		m_borderRadius
	);

	nvgFillColor(ctx, nvgRGBAf(m_background.r, m_background.g, m_background.b, m_opacity));
	nvgFill(ctx);

	nvgFontSize(ctx, m_fontSize);
	nvgFontFace(ctx, m_font.c_str());
	nvgTextAlign(ctx, m_align);
	nvgFontBlur(ctx, m_blur);
	nvgFillColor(ctx, m_color);

	int i = 0;
	int lh = 20;
	for (auto& directory : m_directories)
	{
		i++;
		float y = position.y + (lh * i);

		nvgText(ctx,
			position.x + 15.0f,
			y + 35.0f,
			directory->m_name.c_str(),
			NULL
		);
	}

	nvgRestore(ctx);
}

void TreeView::update(double delta)
{

}

TreeView::~TreeView()
{
	
}