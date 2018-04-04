#include "window.h"
#include "layout.h"
#include "icon.h"
#include <iostream>

Window::Window(const std::string& text = "window", glm::vec2& position = glm::vec2(), glm::vec2& size = glm::vec2(250.0f, 250.0f), const std::string& font = "segoeui") : Widget(position, size)
{
	m_header.text = text;
	m_header.font = font;
	m_header.fontSize = 20.0f;
	m_header.blur = 0.0f;
	m_header.align = NVG_ALIGN_CENTER;
	m_header.color = nvgRGBA(255.0f, 255.0f, 255.0f, 230.0f);
	m_header.rect = new Rect(glm::vec2(position.x + 1, position.y + 1), glm::vec2(size.x - 2, 30));

	m_background = nvgRGBA(28.0f, 28.0f, 28.0f, 230.0f);
	m_drawingShadow = false;
	m_borderRadius = 0.0f;

	const glm::vec2 iconPosition = glm::vec2(
		position.x + m_header.rect->getSize().x - m_header.rect->getSize().y * 0.55f,
		position.y + m_header.rect->getSize().y * 0.55f
	);
	const glm::vec2 iconSize = glm::vec2(m_header.rect->getSize().x * 0.15f, m_header.rect->getSize().x * 0.15f);
	Icon* icon = new Icon("CIRCLED_CROSS", iconPosition, iconSize);
	this->setIcon(icon);
}

void Window::update(double delta)
{
	if (this->getState("draggable") && this->getState("dragged"))
	{
		glm::vec2 pos = this->getRelativePosition();
		this->setPosition(pos + (m_mouse - pos));
	}
}

void Window::draw(NVGcontext* ctx, double delta)
{
	nvgSave(ctx);

	glm::vec2 position = this->getRelativePosition();

	// Window
	nvgBeginPath(ctx);
	nvgRoundedRect(ctx,
		position.x,
		position.y,
		this->getSize().x,
		this->getSize().y,
		m_borderRadius
	);

	nvgFillColor(ctx, m_background);
	nvgFill(ctx);

	if (this->isDrawingShadow())
	{
		// Shadow
		m_shadowPaint = nvgBoxGradient(
			ctx,
			position.x,
			position.y + 2,
			this->getSize().x,
			this->getSize().y,
			m_borderRadius * 2,
			10,
			nvgRGBA(0, 0, 0, 255),
			nvgRGBA(0, 0, 0, 0)
		);

		nvgBeginPath(ctx);
		nvgRect(ctx,
			position.x - 10,
			position.y - 10,
			this->getSize().x + 20,
			this->getSize().y + 30
		);

		nvgRoundedRect(ctx,
			position.x,
			position.y,
			this->getSize().x,
			this->getSize().y,
			m_borderRadius
		);

		nvgPathWinding(ctx, NVG_HOLE);
		nvgFillPaint(ctx, m_shadowPaint);
		nvgFill(ctx);
	}
	

	m_header.rect->setPosition(glm::vec2(
		position.x + 1,
		position.y + 1)
	);
	m_header.rect->setSize(glm::vec2(this->getSize().x - 2, 30));


	if (this->hasIcon())
	{
		nvgFontSize(ctx, m_header.rect->getSize().x * 0.15f);
		nvgFontFace(ctx, "entypo");
		nvgFillColor(ctx, nvgRGBA(255, 255, 255, 32));
		nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
		nvgText(ctx,
			position.x + m_header.rect->getSize().x - m_header.rect->getSize().y * 0.48f,
			position.y + m_header.rect->getSize().y * 0.55f,
			this->getIcon()->get(),
			NULL
		);

		nvgBeginPath(ctx);
		nvgRoundedRect(ctx,
			position.x + m_header.rect->getSize().x - m_header.rect->getSize().y * 1.0f,
			position.y,
			m_header.rect->getSize().y,
			m_header.rect->getSize().y,
			m_borderRadius
		);

		nvgFillColor(ctx, nvgRGBA(0.32f, 0.32f, 0.32f, 32.0f));
		nvgFill(ctx);
	}

	// Header
	m_headerPaint = nvgLinearGradient(ctx,
		position.x,
		position.y,
		position.x,
		position.y + 15,
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
		position.x + 0.5f,
		position.y + 0.5f + 30
	);
	nvgLineTo(ctx,
		position.x + 0.5f + this->getSize().x - 1,
		position.y + 0.5f + 30
	);
	nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 32));
	nvgStroke(ctx);

	// Header text
	nvgFontSize(ctx, m_header.fontSize);
	nvgFontFace(ctx, m_header.font.c_str());
	nvgTextAlign(ctx, m_header.align);
	nvgFontBlur(ctx, m_header.blur);
	nvgFillColor(ctx, m_header.color);

	nvgText(ctx,
		position.x + this->getSize().x * 0.5f,
		position.y + m_header.rect->getSize().y * 0.66f,
		m_header.text.c_str(),
		NULL
	);

	nvgRestore(ctx);
}

void Window::onKeyDown(const SDL_Event& event)
{

}

void Window::onTextInput(const SDL_Event & event)
{

}

void Window::onKeyUp(const SDL_Event& event)
{

}

void Window::onMouseMove(const SDL_Event& event)
{
	m_mouse = glm::vec2((float)event.motion.x, (float)event.motion.y);
	this->setState("hovered", this->getRect()->intersects(m_mouse));

}

void Window::onMouseDown(const SDL_Event& event)
{
	this->setState("hovered", this->getRect()->intersects(m_mouse));

	if (this->getState("draggable")) {
		if (m_header.rect->intersects(m_mouse)) {

			glm::vec2 position = this->getRelativePosition();
			glm::vec2 pos = glm::vec2(position.x + m_header.rect->getSize().x - m_header.rect->getSize().y * 1.0f, position.y);
			glm::vec2 size = glm::vec2(m_header.rect->getSize().y, m_header.rect->getSize().y);
			Rect rect(pos, size);
			
			if (rect.intersects(m_mouse)) {
				this->setState("dragged", false);
			}
			else
				this->setState("dragged", event.button.button == SDL_BUTTON_LEFT);
		}
	}
}

void Window::onMouseUp(const SDL_Event& event)
{
	this->setState("dragged", false);
	this->setState("hovered", this->getRect()->intersects(m_mouse));
}

void Window::onWindowResized(const SDL_Event& event)
{

}

void Window::onWindowSizeChanged(const SDL_Event& event)
{

}

Window::~Window()
{
	delete m_header.rect;
}
