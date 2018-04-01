#include "input.h"
#include <iostream>

Input::Input(glm::vec2& position, glm::vec2& size, const std::string& font) : Widget(position, size)
{
	m_background = glm::vec4(38.0f, 38.0f, 38.0f, 100.0f);

	m_margin = glm::vec4(
		8.0f, // Top
		5.0f, // Right
		8.0f, // Bottom
		5.0f  // Left
	);

	m_text.font = font;
	m_text.fontSize = 20.0f;
	m_text.blur = 0.0f;
	m_text.align = NVG_ALIGN_LEFT;
	m_text.color = glm::vec4(255.0f, 255.0f, 255.0f, 255.0f);

	m_caret.size = glm::vec2(1.0f, size.y - m_margin.z);
	m_caret.background = glm::vec4(255.0f, 255.0f, 255.0f, 255.0f);
	m_caret.blinkStart = SDL_GetTicks();
	m_caret.blinkSpeed = 1000;
}

void Input::update(double delta)
{
	if (m_focused)
		m_background = glm::vec4(58.0f, 58.0f, 58.0f, 100.0f);
	else if (m_hovered) 
		m_background = glm::vec4(48.0f, 48.0f, 48.0f, 100.0f);
	else
		m_background = glm::vec4(38.0f, 38.0f, 38.0f, 100.0f);

	if (m_focused)
	{
		if (SDL_GetTicks() - m_caret.blinkStart > m_caret.blinkSpeed)
		{
			m_caret.blinkStart = SDL_GetTicks();
			m_caret.background.a -= 255;
		}

		if (m_caret.background.a < 0)
			m_caret.background.a = 255;

		if (m_caret.background.a > 255)
			m_caret.background.a = 0;
	}
}

void Input::draw(NVGcontext* ctx, double delta)
{
	nvgSave(ctx);

	glm::vec2 position = this->getRelativePosition();

	this->drawBackground(ctx, position);
	this->drawText(ctx, position);
	this->drawCaret(ctx, position);

	nvgRestore(ctx);
}

void Input::drawBackground(NVGcontext* ctx, glm::vec2& position)
{
	NVGpaint bg;

	bg = nvgBoxGradient(ctx,
		position.x + 1,
		position.y + 1 + 1.5f,
		this->getSize().x - 2,
		this->getSize().y - 2, 3, 4,
		nvgRGBA(
		(unsigned char)m_background.r,
			(unsigned char)m_background.g,
			(unsigned char)m_background.b,
			(unsigned char)m_background.a
		),
		nvgRGBA(0, 0, 0, 50)
	);

	nvgBeginPath(ctx);

	nvgRoundedRect(ctx,
		position.x + 1,
		position.y + 1,
		this->getSize().x - 2,
		this->getSize().y - 2,
		4 - 1
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

void Input::drawText(NVGcontext* ctx, glm::vec2& position)
{
	m_text.width = nvgTextBounds(ctx, position.x, position.y, m_text.text.c_str(), NULL, 0);

	float diff = this->getSize().x - m_text.width;
	float textX = m_text.width + m_margin.w > this->getSize().x
		? position.x + diff - m_margin.w
		: position.x + 5;

	nvgFontSize(ctx, m_text.fontSize);
	nvgFontFace(ctx, m_text.font.c_str());
	nvgTextAlign(ctx, m_text.align);
	nvgFontBlur(ctx, m_text.blur);
	nvgFillColor(ctx, nvgRGBA(
		(unsigned char)m_text.color.r,
		(unsigned char)m_text.color.g,
		(unsigned char)m_text.color.b,
		(unsigned char)m_text.color.a)
	);

	nvgScissor(ctx, position.x, position.y, this->getSize().x, this->getSize().y - m_margin.x);

	nvgText(ctx,
		textX,
		position.y + (this->getSize().y * 0.5f) + 5,
		m_text.text.c_str(),
		NULL
	);
}

void Input::drawCaret(NVGcontext* ctx, glm::vec2& position)
{
	if (m_focused)
	{
		float caretX = m_text.width + m_margin.w > this->getSize().x
			? position.x + this->getSize().x - m_margin.w
			: position.x + m_text.width + m_margin.w;

		nvgBeginPath(ctx);

		nvgRect(ctx,
			caretX,
			position.y + m_margin.x,
			m_caret.size.x,
			m_caret.size.y - m_margin.z
		);

		nvgFillColor(ctx, nvgRGBA(
			(unsigned char)m_caret.background.r,
			(unsigned char)m_caret.background.g,
			(unsigned char)m_caret.background.b,
			(unsigned char)m_caret.background.a)
		);

		nvgFill(ctx);
	}
}

void Input::onTextInput(const SDL_Event& event)
{
	if (m_focused)
		m_text.text.append(event.text.text);
}

void Input::onKeyDown(const SDL_Event& event)
{
	if (event.key.keysym.sym == SDLK_BACKSPACE && m_text.text.size() > 0)
		m_text.text.pop_back();

	if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER)
		m_focused = false;
}

void Input::onKeyUp(const SDL_Event& event)
{

}

void Input::onMouseMove(const SDL_Event& event)
{
	m_mouse = glm::vec2((float)event.motion.x, (float)event.motion.y);
	m_mouseRel = glm::vec2((float)event.motion.xrel, (float)event.motion.yrel);
	m_hovered = this->intersects(m_mouse);

	Display* window = this->getWindow();

	if(window != nullptr)
		window->setCurrentCursor(m_hovered ? window->getCursor("IBEAM") : window->getCursor("ARROW"));
}

void Input::onMouseDown(const SDL_Event& event)
{
	this->setFocused(this->intersects(m_mouse));
}

void Input::onMouseUp(const SDL_Event& event)
{
	this->setFocused(this->intersects(m_mouse));
}

void Input::onWindowResized(const SDL_Event& event)
{
	this->setScreen(glm::vec2(event.window.data1, event.window.data2));
}

void Input::onWindowSizeChanged(const SDL_Event& event)
{
	this->setScreen(glm::vec2(event.window.data1, event.window.data2));
}


Input::~Input()
{

}
