#include "button.h"

Button::Button(glm::vec2& position, glm::vec2& size, const std::string& font) : Widget(position, size)
{
	m_background = { 0, 0, 0, 16 };
	m_hightlight = { 255, 255, 255, 16 };
	m_borderRadius = 4.0f;

	m_margin = glm::vec4(
		8.0f, // Top
		5.0f, // Right
		8.0f, // Bottom
		5.0f  // Left
	);

	m_text.font = font;
	m_text.fontSize = 20.0f;
	m_text.blur = 0.0f;
	m_text.align = NVG_ALIGN_MIDDLE;
	m_text.color = { 0, 0, 0, 0 };

	m_icon.width = 0;
}

void Button::update(double delta)
{
	if (m_active)
	{
		m_background = { 255, 255, 255, 32 };
		m_hightlight = { 0, 0, 0, 32 };
	}
	else if (m_hovered)
	{
		m_background = { 0, 0, 0, 32 };
		m_hightlight = { 255, 255, 255, 32 };
	}
	else
	{
		m_background = { 0, 0, 0, 16 };
		m_hightlight = { 255, 255, 255, 16 };
	}
}

void Button::draw(NVGcontext* ctx, double delta)
{
	nvgSave(ctx);

	glm::vec2 position = this->getRelativePosition();

	this->drawBackground(ctx, position);
	this->drawText(ctx, position);

	nvgRestore(ctx);
}

void Button::drawBackground(NVGcontext* ctx, glm::vec2& position)
{
	NVGpaint bg;

	bg = nvgLinearGradient(ctx,
		position.x,
		position.y,
		position.x,
		position.y + this->getSize().y,
		nvgRGBA(m_hightlight.r, m_hightlight.g, m_hightlight.b, m_hightlight.a),
		nvgRGBA(m_background.r, m_background.g, m_background.b, m_background.a)
	);

	nvgBeginPath(ctx);
	nvgRoundedRect(ctx, 
		position.x + 1, 
		position.y + 1, 
		this->getSize().x - 2,
		this->getSize().y - 2,
		m_borderRadius - 1
	);
	nvgFillPaint(ctx, bg);
	nvgFill(ctx);

	nvgBeginPath(ctx);
	nvgRoundedRect(ctx,
		position.x + 0.5f,
		position.y + 0.5f,
		this->getSize().x - 1,
		this->getSize().y - 1,
		4 - 0.5f
	);

	nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 48));
	nvgStroke(ctx);
}

void Button::drawText(NVGcontext* ctx, glm::vec2& position)
{
	m_text.width = nvgTextBounds(ctx, position.x, position.y, m_text.text.c_str(), NULL, 0);

	nvgFontSize(ctx, m_text.fontSize);
	nvgFontFace(ctx, m_text.font.c_str());
	nvgTextAlign(ctx, m_text.align);
	nvgFontBlur(ctx, m_text.blur);
	nvgFillColor(ctx, m_text.color);

	nvgScissor(ctx, 
		position.x,
		position.y, 
		this->getSize().x, 
		this->getSize().y - m_margin.x
	);

	nvgText(ctx,
		position.x + this->getSize().x * 0.5f - m_text.width * 0.5f + m_icon.width * 0.25f, 
		position.y + this->getSize().y * 0.5f - 1,
		m_text.text.c_str(),
		NULL
	);

	nvgFillColor(ctx, nvgRGBA(255, 255, 255, 160));

	nvgText(ctx,
		position.x + this->getSize().x * 0.5f - m_text.width * 0.5f + m_icon.width * 0.25f,
		position.y + this->getSize().y * 0.5f,
		m_text.text.c_str(),
		NULL
	);
}

void Button::onTextInput(const SDL_Event& event)
{

}

void Button::onKeyDown(const SDL_Event& event)
{
	
}

void Button::onKeyUp(const SDL_Event& event)
{

}

void Button::onMouseMove(const SDL_Event& event)
{
	m_mouse = glm::vec2((float)event.motion.x, (float)event.motion.y);
	m_mouseRel = glm::vec2((float)event.motion.xrel, (float)event.motion.yrel);
	m_hovered = this->intersects(m_mouse);
}

void Button::onMouseDown(const SDL_Event& event)
{
	if(event.button.button == SDL_BUTTON_LEFT && m_hovered)
		this->setActive(true);
}

void Button::onMouseUp(const SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
		this->setActive(false);
}

void Button::onWindowResized(const SDL_Event& event)
{
	this->setScreen(glm::vec2(event.window.data1, event.window.data2));
}

void Button::onWindowSizeChanged(const SDL_Event& event)
{
	this->setScreen(glm::vec2(event.window.data1, event.window.data2));
}


Button::~Button()
{

}
