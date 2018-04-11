#include "window.h"
#include "layout.h"
#include "icon.h"
#include "../core/guiManager.h"
#include <iostream>

Window::Window(const std::string& text = "window", glm::vec2& position = glm::vec2(), glm::vec2& size = glm::vec2(250.0f, 250.0f), const std::string& font = "segoeui") : Widget(position, size)
{
	m_header.text = text;
	m_header.font = font;
	m_header.fontSize = 20.0f;
	m_header.blur = 0.0f;
	m_header.align = NVG_ALIGN_LEFT;
	m_header.color = nvgRGBA(255, 255, 255, 128);
	m_header.rect = new Rect(glm::vec2(position.x + 1, position.y + 1), glm::vec2(size.x - 2, 30));

	m_drawingShadow = true;
	m_opacity = 1.0f;
	m_background = nvgRGB(28, 28, 28);
	m_borderRadius = 0.0f;

	const glm::vec2 iconPosition = glm::vec2(
		position.x + m_header.rect->getSize().x - m_header.rect->getSize().y * 0.55f,
		position.y + m_header.rect->getSize().y * 0.55f
	);
	const glm::vec2 iconSize = glm::vec2(m_header.rect->getSize().x * 0.15f, m_header.rect->getSize().x * 0.15f);
	Icon* icon = new Icon("CANCEL_SQUARED", iconPosition, iconSize);
	icon->addEventListener("onClosed", &Window::onClosed);
	this->setIcon(icon);
}

void Window::update(double delta)
{
	if (this->getState("dragged"))
	{
		this->incrementPosition(m_mouse - this->getRelativePosition());
	}	
}

void Window::draw(NVGcontext* ctx, double delta)
{
	nvgSave(ctx);

	glm::vec2 position = this->getRelativePosition();

	nvgBeginPath(ctx);
	nvgRoundedRect(ctx,
		position.x,
		position.y,
		this->getSize().x,
		this->getSize().y,
		m_borderRadius
	);

	nvgFillColor(ctx, nvgRGBAf(m_background.r, m_background.g, m_background.b, m_opacity));
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
			8.0f,
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

	// Header
	m_headerPaint = nvgLinearGradient(ctx,
		position.x,
		position.y,
		position.x,
		position.y + 30,
		nvgRGBA(60, 60, 60, 255),
		nvgRGBA(20, 20, 20, 255)
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
		position.x + 10.0f,
		position.y + m_header.rect->getSize().y * 0.66f,
		m_header.text.c_str(),
		NULL
	);


	if (this->hasIcon() && this->getState("closable"))
	{
		nvgBeginPath(ctx);
		nvgRoundedRect(ctx,
			position.x + m_header.rect->getSize().x - m_header.rect->getSize().y * 1.0f,
			position.y,
			m_header.rect->getSize().y,
			m_header.rect->getSize().y,
			m_borderRadius
		);

		if (this->getIcon()->getState("hovered"))
			nvgFillColor(ctx, nvgRGBA(125, 0, 0, 128));
		else
			nvgFillColor(ctx, nvgRGBA(32, 32, 32, 64));

		nvgFill(ctx);

		nvgFontSize(ctx, 32.0f);
		nvgFontFace(ctx, "entypo");
		nvgFillColor(ctx, nvgRGBA(255, 255, 255, 128));
		nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);


		nvgText(ctx,
			position.x + m_header.rect->getSize().x - m_header.rect->getSize().y * 0.48f,
			position.y + m_header.rect->getSize().y * 0.55f,
			this->getIcon()->get(),
			NULL
		);
	}

	nvgRestore(ctx);
}

void Window::onKeyDown(const SDL_Event& event)
{
	if (event.key.keysym.sym == SDLK_c && this->getState("hovered")) {
		this->setState("visible", this->getState("visible") == false);
	}
}

void Window::onMouseMove(const SDL_Event& event)
{
	if (this->getState("dragged"))
	{
		m_dragEnd = m_mouse;
		m_dragDelta = m_dragEnd - m_dragStart;
	}

	m_mouse = glm::vec2((float)event.motion.x, (float)event.motion.y);
	this->setState("hovered", this->intersects(m_mouse));

	if (this->getState("closable"))
	{
		glm::vec2 position = this->getRelativePosition();
		glm::vec2 pos = glm::vec2(position.x + m_header.rect->getSize().x - m_header.rect->getSize().y * 1.0f, position.y);
		glm::vec2 size = glm::vec2(m_header.rect->getSize().y, m_header.rect->getSize().y);
		Rect rect(pos, size);

		this->getIcon()->setState("hovered", rect.intersects(m_mouse));
	}

	LayerManager* layerManager = this->getLayout()->getGuiManager()->getLayerManager();
	if (this->getState("hovered"))
		layerManager->addWidget(0, this);
	else
		layerManager->removeWidget(0, this);
}

void Window::onClosed(CallbackData data)
{
	data.sender->getLayout()->removeWidget(data.sender);
}

void Window::onMouseDown(const SDL_Event& event)
{
	this->setState("hovered", this->intersects(m_mouse));


	if (this->getState("draggable") && event.button.button == SDL_BUTTON_LEFT && !this->getState("dragged"))
	{
		if (m_header.rect->intersects(m_mouse)) 
		{
			m_dragStart = m_mouse;

			if(this->getState("closable"))
				if (this->getIcon()->getState("hovered"))
					this->setState("dragged", false);
			else
				this->setState("dragged", true);
		}
	}
}

void Window::onMouseUp(const SDL_Event& event)
{
	m_dragStart = glm::vec2();
	m_dragEnd = m_mouse;
	this->setState("dragged", false);

	if (this->getIcon()->getState("hovered")) {

		if (event.button.button == SDL_BUTTON_LEFT) {
			this->getIcon()->handleEventListener("onClosed", { this });
		}
	}	

	this->setState("hovered", this->intersects(m_mouse));
}

void Window::onTextInput(const SDL_Event & event)
{

}

void Window::onKeyUp(const SDL_Event& event)
{

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
