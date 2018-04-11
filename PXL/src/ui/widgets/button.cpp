#include "button.h"
#include "layout.h"

Button::Button(glm::vec2& position, glm::vec2& size, const std::string& font) : Widget(position, size)
{
	m_background = nvgRGBA(30, 30, 30, 255);
	m_hightlight = nvgRGBA(100, 100, 100, 255);
	m_borderRadius = 4.0f;

	m_margin = glm::vec4(
		8.0f, // Top
		5.0f, // Right
		8.0f, // Bottom
		5.0f  // Left
	);

	m_text.font = font;
	m_text.fontSize = 18.0f;
	m_text.blur = 0.0f;
	m_text.align = NVG_ALIGN_MIDDLE;
	m_text.color = nvgRGBA(200, 200, 200, 255);
	m_text.shadow = nvgRGBA(0, 0, 0, 0);
}

void Button::update(double delta)
{
	if (this->getState("active"))
	{
		m_background = nvgRGBA(120, 120, 120, 64);
		m_text.color = nvgRGBA(160, 160, 160, 255);
		m_hightlight = nvgRGBA(30, 30, 30, 255);
	}
	else if (this->getState("hovered"))
	{
		m_background = nvgRGBA(50, 50, 50, 255);
		m_text.color = nvgRGBA(220, 220, 220, 255);
		m_hightlight = nvgRGBA(120, 120, 120, 255);
	}
	else
	{
		m_background = nvgRGBA(30, 30, 30, 255);
		m_text.color = nvgRGBA(200, 200, 200, 255);
		m_hightlight = nvgRGBA(100, 100, 100, 255);
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

	m_text.width = nvgTextBounds(ctx, position.x, position.y, m_text.text.c_str(), NULL, 0);

	bg = nvgLinearGradient(ctx,
		position.x,
		position.y,
		position.x,
		position.y + this->getSize().y,
		m_hightlight,
		m_background
	);

	nvgBeginPath(ctx);
	nvgRoundedRect(ctx, 
		position.x + 1, 
		position.y + 1, 
		this->getSize().x - 1,
		this->getSize().y - 1,
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
	nvgFontSize(ctx, m_text.fontSize);
	nvgFontFace(ctx, m_text.font.c_str());
	nvgTextAlign(ctx, m_text.align);
	nvgFontBlur(ctx, m_text.blur);
	nvgFillColor(ctx, m_text.shadow);

	nvgScissor(ctx, 
		position.x,
		position.y, 
		this->getSize().x, 
		this->getSize().y
	);

	nvgText(ctx,
		position.x + (this->getSize().x - m_text.width) * 0.5f + 2.5f,
		position.y + (this->getSize().y * 0.5f) - 1,
		m_text.text.c_str(),
		NULL
	);

	nvgFillColor(ctx, m_text.color);

	nvgText(ctx,
		position.x + (this->getSize().x - m_text.width) * 0.5f + 2.5f,
		position.y + (this->getSize().y * 0.5f),
		m_text.text.c_str(),
		NULL
	);
}

void Button::onTextInput(const SDL_Event& event) {}
void Button::onKeyDown(const SDL_Event& event) {}
void Button::onKeyUp(const SDL_Event& event) {}

void Button::onMouseMove(const SDL_Event& event)
{
	m_mouse = glm::vec2((float)event.motion.x, (float)event.motion.y);
	m_mouseRel = glm::vec2((float)event.motion.xrel, (float)event.motion.yrel);

	this->setState("hovered", this->intersects(m_mouse));
}

void Button::onMouseDown(const SDL_Event& event)
{
	if(event.button.button == SDL_BUTTON_LEFT && this->getState("hovered"))
		this->setState("active", true);
}

void Button::onMouseUp(const SDL_Event& event)
{
	this->setState("active", false);

	if (event.button.button == SDL_BUTTON_LEFT )
	{
		if (this->getState("hovered")) {
			if (this->hasListener("onClosed"))
				this->handleEventListener("onClosed", { this });

			if (this->getState("hovered"))
				this->handleEventListener("mouseUp", { this });
		}
	}
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
