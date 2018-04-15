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
	m_textHoverColor = nvgRGB(47, 124, 202);
	m_background = nvgRGB(35, 35, 35);
	m_backgroundHoverColor = nvgRGB(50, 50, 50);
	m_borderRadius = 0.0f;
	m_opacity = 1.0f;
}

void TreeView::update(double delta)
{

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

	int i = 0;
	float lh = 20.0f;
	for (auto& directory : m_directories)
	{
		i++;
		float y = position.y + (lh * i);

		if (directory->m_hovered) 
		{
			nvgBeginPath(ctx);
			nvgRect(ctx,
				position.x,
				y + lh,
				size.x,
				lh
			);

			nvgFillColor(ctx, m_backgroundHoverColor);
			nvgFill(ctx);
		}

		if (directory->m_icon != nullptr)
		{
			nvgFontSize(ctx, 34.0f);
			nvgFontFace(ctx, "entypo");
			nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

			nvgFillColor(ctx, directory->m_hovered ? m_textHoverColor : m_color);

			if (directory->m_opened) 
			{
				nvgSave(ctx);
				nvgRotate(ctx, (float)(M_PI / 2.0f));
				nvgRestore(ctx);
			}

			nvgText(ctx,
				position.x + 20.0f,
				y + 30.0f,
				directory->m_icon->get(),
				NULL
			);
		}
	
		nvgFontSize(ctx, m_fontSize);
		nvgFontFace(ctx, m_font.c_str());
		nvgTextAlign(ctx, m_align);
		nvgFontBlur(ctx, m_blur);
		nvgFillColor(ctx, directory->m_hovered ? m_textHoverColor : m_color);

		nvgText(ctx,
			position.x + 30.0f,
			y + 35.0f,
			directory->m_name.c_str(),
			NULL
		);
	}

	nvgRestore(ctx);
}

void TreeView::onKeyDown(const SDL_Event & event)
{

}

void TreeView::onTextInput(const SDL_Event & event)
{

}

void TreeView::onKeyUp(const SDL_Event & event)
{

}

void TreeView::onMouseMove(const SDL_Event & event)
{
	m_mouse = glm::vec2((float)event.motion.x, (float)event.motion.y);
	this->setState("hovered", this->intersects(m_mouse));

	unsigned int i = 0;
	int lh = 20;
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

	for (auto& directory : m_directories)
	{
		i++;
		float y = position.y + (lh * i);

		Rect rect(glm::vec2(position.x, y + lh), glm::vec2(size.x, lh));
		directory->m_hovered = rect.intersects(m_mouse);
	}
}

void TreeView::onMouseDown(const SDL_Event& event)
{

}

void TreeView::onMouseUp(const SDL_Event& event)
{

}

void TreeView::onWindowResized(const SDL_Event& event)
{

}

void TreeView::onWindowSizeChanged(const SDL_Event& event)
{

}

TreeView::~TreeView()
{
	
}
