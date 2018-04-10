#include "input.h"
#include "icon.h"
#include <iostream>

Input::Input(glm::vec2& position, glm::vec2& size, const std::string& font) : Widget(position, size)
{
	m_background = nvgRGB(40, 40, 40);

	m_margin = glm::vec4(
		8.0f, // Top
		5.0f, // Right
		8.0f, // Bottom
		5.0f  // Left
	);

	m_text.text = "";
	m_text.font = font;
	m_text.fontSize = 20.0f;
	m_text.blur = 0.0f;
	m_text.align = NVG_ALIGN_LEFT;
	m_text.color = nvgRGBA(255, 255, 255, 128);
	m_text.placeholder = "";
	m_text.drawPlaceholder = true;

	m_caret = new InputCaret();
	m_caret->size = glm::vec2(1.0f, size.y - m_margin.z);
	m_caret->background = nvgRGBA(255, 255, 255, 255);
	m_caret->blinkStart = SDL_GetTicks();
	m_caret->blinkSpeed = 1000;
	m_caret->blinking = false;

	Icon* icon = new Icon("CIRCLED_CROSS", glm::vec2(), glm::vec2(20, 20));
	this->setIcon(icon);
}


void Input::update(double delta)
{
	if (this->getState("focused")) 
	{
		m_background = nvgRGB(50, 50, 50);
		m_text.color = nvgRGB(255, 255, 255);

		if (m_caret->blinking)
		{
			if (SDL_GetTicks() - m_caret->blinkStart > m_caret->blinkSpeed)
			{
				m_caret->blinkStart = SDL_GetTicks();
				m_caret->background.a -= 255;
			}

			if (m_caret->background.a < 0)
				m_caret->background.a = 255;

			if (m_caret->background.a > 255)
				m_caret->background.a = 0;
		}
		else
			m_caret->background.a = 255;
	}
	else if (this->getState("hovered"))
	{
		m_text.color = nvgRGB(255, 255, 255);
		m_background = nvgRGB(45, 45, 45);
	}
	else {
		m_text.color = nvgRGBA(255, 255, 255, 128);
		m_background = nvgRGB(40, 40, 40);
	}
}

void Input::draw(NVGcontext* ctx, double delta)
{
	nvgSave(ctx);

	glm::vec2 position = this->getRelativePosition();

	this->drawBackground(ctx, position);
	this->drawText(ctx, position);
	this->drawCaret(ctx, position);
	this->drawIcon(ctx, position);

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
		m_background,
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
	std::string text = m_text.text;

	if (m_text.drawPlaceholder && m_text.placeholder.size() > 0)
		text = m_text.placeholder;

	m_text.width = nvgTextBounds(ctx, position.x, position.y, text.c_str(), NULL, 0);

	float diff = this->getSize().x - m_text.width;
	float textX = m_text.width + m_margin.w > this->getSize().x
		? position.x + diff - m_margin.w
		: position.x + 5;

	nvgFontSize(ctx, m_text.fontSize);
	nvgFontFace(ctx, m_text.font.c_str());
	nvgTextAlign(ctx, m_text.align);
	nvgFontBlur(ctx, m_text.blur);
	nvgFillColor(ctx, m_text.color);

	nvgScissor(ctx, position.x, position.y, this->getSize().x, this->getSize().y - m_margin.x);

	nvgText(ctx,
		textX,
		position.y + (this->getSize().y * 0.5f) + 5,
		text.c_str(),
		NULL
	);
}

void Input::drawCaret(NVGcontext* ctx, glm::vec2& position)
{
	if (this->getState("focused"))
	{
		float caretX = m_text.width + m_margin.w > this->getSize().x
			? position.x + this->getSize().x - m_margin.w
			: position.x + m_text.width + m_margin.w;

		nvgBeginPath(ctx);

		nvgRect(ctx,
			caretX,
			position.y + m_margin.x,
			m_caret->size.x,
			m_caret->size.y - m_margin.z
		);

		nvgFillColor(ctx, m_caret->background);

		nvgFill(ctx);
	}
}

void Input::drawIcon(NVGcontext* ctx, glm::vec2 & position)
{
	if (this->hasIcon() && m_text.text.size() > 0)
	{
		nvgFontSize(ctx, 32.0f);
		nvgFontFace(ctx, "entypo");
		nvgFillColor(ctx, nvgRGBA(255, 255, 255, 128));
		nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

		nvgText(ctx,
			position.x + this->getSize().x -this->getSize().y * 0.48f,
			position.y + this->getSize().y * 0.55f,
			this->getIcon()->get(),
			NULL
		);
	}
}

void Input::onTextInput(const SDL_Event& event)
{
	if (this->getState("focused"))
		m_text.text.append(event.text.text);
}

void Input::onKeyDown(const SDL_Event& event)
{
	if (this->getState("focused")) {

		if (event.key.keysym.sym == SDLK_BACKSPACE && m_text.text.size() > 0)
			m_text.text.resize(m_text.text.size() - 1);

		if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
			this->setState("focused", false);
			m_text.drawPlaceholder = m_text.text.size() == 0;
		}

		m_caret->blinking = false;
		m_caret->background.a = 255;
	}
}

void Input::onKeyUp(const SDL_Event& event)
{
	if (this->getState("focused")) {
		m_caret->blinking = true;
		m_caret->blinkStart = SDL_GetTicks();
	}
}

void Input::onMouseMove(const SDL_Event& event)
{
	m_mouse = glm::vec2((float)event.motion.x, (float)event.motion.y);
	this->setState("hovered", this->intersects(m_mouse));


	if (this->getState("hovered")) {
		SDL_SetCursor(this->getWindow()->getCursor("IBEAM"));
	}
	else {
		SDL_SetCursor(SDL_GetDefaultCursor());
	}
}

void Input::onMouseDown(const SDL_Event& event)
{
	bool intersect = this->intersects(m_mouse);
	this->setState("hovered", intersect);
	this->setState("focused", intersect);

	if (this->getState("focused"))
	{
		// TODO: Place caret at mouse position.
		m_caret->blinking = true;
		m_caret->blinkStart = SDL_GetTicks();
		m_text.drawPlaceholder = false;
	}
}

void Input::onMouseUp(const SDL_Event& event)
{
	bool intersect = this->intersects(m_mouse);
	this->setState("hovered", intersect);

	if (!this->getState("focused"))
	{
		m_caret->blinkStart = SDL_GetTicks();
		m_text.drawPlaceholder = m_text.text.size() == 0;
	}
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
	delete m_caret;
}
