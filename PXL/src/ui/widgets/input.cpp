
#include "input.h"

 Input::Input(glm::vec2 & position, glm::vec2 & size, const std::string & font) {

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

 Input::~Input() {

	delete m_caret;
}

void Input::update(double delta) {

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

void Input::draw(NVGcontext & ctx, double delta) {

	nvgSave(ctx);

	glm::vec2 position = this->getRelativePosition();
	glm::vec2 size = this->getRelativeSize();

	this->drawBackground(ctx, position, size);
	this->drawText(ctx, position, size);
	this->drawCaret(ctx, position, size);
	this->drawIcon(ctx, position, size);

	nvgRestore(ctx);
}

void Input::drawBackground(NVGcontext & ctx, glm::vec2 & position, glm::vec2 & size) {

	NVGpaint bg;

	bg = nvgBoxGradient(ctx,
		position.x + 1,
		position.y + 1 + 1.5f,
		size.x - 2,
		size.y - 2, 3, 4,
		m_background,
		nvgRGBA(0, 0, 0, 50)
	);

	nvgBeginPath(ctx);

	nvgRoundedRect(ctx,
		position.x + 1,
		position.y + 1,
		size.x - 2,
		size.y - 2,
		4 - 1
	);

	nvgFillPaint(ctx, bg);
	nvgFill(ctx);
	nvgBeginPath(ctx);

	nvgRoundedRect(ctx,
		position.x + 0.5f,
		position.y + 0.5f,
		size.x - 1,
		size.y - 1,
		4 - 0.5f
	);

	nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 48));
	nvgStroke(ctx);
}

void Input::drawText(NVGcontext & ctx, glm::vec2 & position, glm::vec2 & size) {

	nvgFontSize(ctx, m_text.fontSize);
	nvgFontFace(ctx, m_text.font.c_str());
	nvgTextAlign(ctx, m_text.align);
	nvgFontBlur(ctx, m_text.blur);
	nvgFillColor(ctx, m_text.color);

	std::string text = m_text.text;

	if (m_text.drawPlaceholder && m_text.placeholder.size() > 0)
		text = m_text.placeholder;

	m_text.width = nvgTextBounds(ctx, 0, 0, text.c_str(), NULL, 0);

	float diff = size.x - m_text.width;
	float textX = m_text.width + m_margin.w > size.x
		? position.x + diff - m_margin.w
		: position.x + 5;

	nvgScissor(ctx, position.x, position.y, size.x, size.y - m_margin.x);

	nvgText(ctx,
		textX,
		position.y + (size.y * 0.5f) + 5,
		text.c_str(),
		NULL
	);
}

void Input::drawCaret(NVGcontext & ctx, glm::vec2 & position, glm::vec2 & size) {

	if (this->getState("focused"))
	{
		float caretX = m_text.width + m_margin.w > size.x
			? position.x + size.x - m_margin.w
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

void Input::drawIcon(NVGcontext & ctx, glm::vec2 & position, glm::vec2 & size) {

	if (this->hasIcon() && m_text.text.size() > 0)
	{
		nvgResetScissor(ctx);

		if (this->getIcon()->getState("hovered"))
			nvgFillColor(ctx, nvgRGBA(255, 255, 255, 128));
		else
			nvgFillColor(ctx, nvgRGBA(255, 255, 255, 50));

		nvgFontSize(ctx, 32.0f);
		nvgFontFace(ctx, "entypo");
		nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

		nvgText(ctx,
			position.x + size.x - size.y * 0.48f,
			position.y + size.y * 0.55f,
			this->getIcon()->get(),
			NULL
		);
	}
}

void Input::onKeyDown(const SDL_Event & event) {

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

void Input::onTextInput(const SDL_Event & event) {

	if (this->getState("focused"))
		m_text.text.append(event.text.text);
}

void Input::onKeyUp(const SDL_Event & event) {

	if (this->getState("focused")) {
		m_caret->blinking = true;
		m_caret->blinkStart = SDL_GetTicks();
	}
}

void Input::onMouseMove(const SDL_Event & event) {

	m_mouse = glm::vec2((float)event.motion.x, (float)event.motion.y);
	this->setState("hovered", this->intersects(m_mouse));

	glm::vec2 position = this->getRelativePosition();
	glm::vec2 size = this->getRelativeSize();

	if (this->getState("hovered")) 
	{
		Rect rect(
			glm::vec2(position.x + size.x - size.y  * 1.0f, position.y),
			glm::vec2(size.y, size.y)
		);

		bool iconIntersect = rect.intersects(m_mouse);
		this->getIcon()->setState("hovered", iconIntersect);

		SDL_SetCursor(this->getWindow()->getMCursor(this->getText().size() > 0 && iconIntersect ? "HAND" : "IBEAM"));
	}
	else {
		SDL_SetCursor(SDL_GetDefaultCursor());
		this->getIcon()->setState("hovered", false);
	}
}

void Input::onMouseDown(const SDL_Event & event) {

	bool intersect = this->intersects(m_mouse);
	this->setState("hovered", intersect);
	this->setState("focused", intersect);

	if (this->getState("focused"))
	{
		// TODO: Place caret at mouse position.f
		m_caret->blinking = true;
		m_caret->blinkStart = SDL_GetTicks();
		m_text.drawPlaceholder = false;
	}
}

void Input::onMouseUp(const SDL_Event & event) {

	bool intersect = this->intersects(m_mouse);
	this->setState("hovered", intersect);

	glm::vec2 position = this->getRelativePosition();
	glm::vec2 size = this->getRelativeSize();

	Rect rect(
		glm::vec2(position.x + size.x - size.y  * 1.0f, position.y),
		glm::vec2(size.y, size.y)
	);

	if (rect.intersects(m_mouse) && event.button.button == SDL_BUTTON_LEFT)
		this->clearText();

	if (!this->getState("focused"))
	{
		m_caret->blinkStart = SDL_GetTicks();
		m_text.drawPlaceholder = m_text.text.size() == 0;
	}
}

void Input::onWindowResized(const SDL_Event & event) {

	this->setScreen(glm::vec2(event.window.data1, event.window.data2));
}

void Input::onWindowSizeChanged(const SDL_Event & event) {

	this->setScreen(glm::vec2(event.window.data1, event.window.data2));
}

