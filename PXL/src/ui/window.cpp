#include "window.h"
#include <iostream>

Window::Window(const std::string& text, glm::vec2& position, glm::vec2& size, const std::string& font) : Widget(position, size)
{
	m_header.text = text;
	m_header.font = font;
	m_header.fontSize = 20.0f;
	m_header.blur = 0.0f;
	m_header.align = NVG_ALIGN_CENTER;
	m_header.color = glm::vec4(255.0f, 255.0f, 255.0f, 225.0f);
	m_header.rect = new Rect(glm::vec2(position.x + 1, position.y + 1), glm::vec2(size.x - 2, 30));

	m_background = glm::vec4(28.0f, 30.0f, 34.0f, 192.0f);
	m_borderRadius = 0.0f;
}

void Window::update(double delta)
{
	//m_background = m_hovered
	//	? glm::vec4(28.0f, 30.0f, 34.0f, 255.0f)
	//	: glm::vec4(28.0f, 30.0f, 34.0f, 192.0f);

	if (m_dragged && m_draggable)
	{
		glm::vec2 pos = this->getPosition();
		glm::vec2 offset = m_mouse - pos;
		this->setPosition(pos + offset);
	}
}

void Window::draw(NVGcontext* ctx, double delta)
{
	nvgSave(ctx);

	// Window
	nvgBeginPath(ctx);
	nvgRoundedRect(ctx, 
		this->getPosition().x,
		this->getPosition().y,
		this->getSize().x,	
		this->getSize().y, 
		m_borderRadius
	);

	nvgFillColor(ctx, nvgRGBA(
		(unsigned char)m_background.r,
		(unsigned char)m_background.g, 
		(unsigned char)m_background.b,
		(unsigned char)m_background.a)
	);
	nvgFill(ctx);

	// Shadow
	m_shadowPaint = nvgBoxGradient(
		ctx, 
		this->getPosition().x,
		this->getPosition().y + 2,
		this->getSize().x, 
		this->getSize().y, 
		m_borderRadius * 2, 
		10, 
		nvgRGBA(0, 0, 0, 255),
		nvgRGBA(0, 0, 0, 0)
	);

	nvgBeginPath(ctx);
	nvgRect(ctx,
		this->getPosition().x - 10, 
		this->getPosition().y - 10,
		this->getSize().x + 20, 
		this->getSize().y + 30
	);

	nvgRoundedRect(ctx,
		this->getPosition().x, 
		this->getPosition().y, 
		this->getSize().x, 
		this->getSize().y,
		m_borderRadius
	);

	nvgPathWinding(ctx, NVG_HOLE);
	nvgFillPaint(ctx, m_shadowPaint);
	nvgFill(ctx);

	m_header.rect->setPosition(glm::vec2(
		this->getPosition().x + 1, 
		this->getPosition().y + 1)
	);
	m_header.rect->setSize(glm::vec2(this->getSize().x - 2, 30));

	// Header
	m_headerPaint = nvgLinearGradient(ctx, 
		this->getPosition().x, 
		this->getPosition().y, 
		this->getPosition().x, 
		this->getPosition().y + 15, 
		nvgRGBA(255, 255, 255, 16), 
		nvgRGBA(0, 0, 0, 16)
	);

	nvgBeginPath(ctx);
	nvgRoundedRect(ctx, 
		m_header.rect->getPosition().x, 
		m_header.rect->getPosition().y,
		m_header.rect->getSize().x,
		m_header.rect->getSize().y,
		m_borderRadius - 1
	);
	nvgFillPaint(ctx, m_headerPaint);
	nvgFill(ctx);
	nvgBeginPath(ctx);
	nvgMoveTo(ctx, 
		this->getPosition().x + 0.5f,
		this->getPosition().y + 0.5f + 30
	);
	nvgLineTo(ctx,
		this->getPosition().x + 0.5f + this->getSize().x - 1,
		this->getPosition().y + 0.5f + 30
	);
	nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 32));
	nvgStroke(ctx);

	// Header text
	nvgFontSize(ctx, m_header.fontSize);
	nvgFontFace(ctx, m_header.font.c_str());
	nvgTextAlign(ctx, m_header.align);
	nvgFontBlur(ctx, m_header.blur);
	nvgFillColor(ctx, nvgRGBA(
		(unsigned char)m_header.color.r,
		(unsigned char)m_header.color.g, 
		(unsigned char)m_header.color.b,
		(unsigned char)m_header.color.a)
	);

	nvgText(ctx, 
		this->getPosition().x + this->getSize().x * 0.5f, 
		this->getPosition().y + 16 + 1, 
		m_header.text.c_str(),
		NULL
	);

	nvgRestore(ctx);
}

void Window::onKeyDown(const SDL_Event& event)
{

}

void Window::onKeyUp(const SDL_Event& event)
{

}

void Window::onMouseMove(const SDL_Event& event)
{
	m_mouse = glm::vec2((float)event.motion.x, (float)event.motion.y);
	m_mouseRel = glm::vec2((float)event.motion.xrel, (float)event.motion.yrel);
	m_hovered = this->getRect()->intersects(m_mouse) ? true : false;
}

void Window::onMouseDown(const SDL_Event& event)
{
	m_hovered = this->getRect()->intersects(m_mouse) ? true : false;

	if(m_draggable)
		if (m_header.rect->intersects(m_mouse)) 
			m_dragged = event.button.button == SDL_BUTTON_LEFT ? true : false;
}

void Window::onMouseUp(const SDL_Event& event)
{
	m_dragged = false;
	m_hovered = this->getRect()->intersects(m_mouse) ? true : false;
}

Window::~Window()
{
	delete m_header.rect;
}
