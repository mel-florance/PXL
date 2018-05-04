
#include "checkbox.h"

 Checkbox::Checkbox(const glm::vec2 & position, const glm::vec2 & size) {

	m_background = nvgRGB(40, 40, 40);
	m_borderRadius = 3.0f;

	Icon* icon = new Icon("CHECK", glm::vec2(position.x, position.y), glm::vec2(this->getSize().x, this->getSize().x));
	this->setIcon(icon);
}

void Checkbox::onMouseMove(const SDL_Event & event) {

	m_mouse = glm::vec2((float)event.motion.x, (float)event.motion.y);
	this->setState("hovered", this->intersects(m_mouse));
}

void Checkbox::onMouseDown(const SDL_Event & event) {

	this->setState("hovered", this->intersects(m_mouse));

	if (this->getState("checkable") && event.button.button == SDL_BUTTON_LEFT && this->getState("hovered"))
		this->setState("checked", this->getState("checked") == false);
}

void Checkbox::onMouseUp(const SDL_Event & event) {


}

void Checkbox::update(double delta) {

	if (this->getState("hovered"))
		m_background = nvgRGB(45, 45, 45);
	else
		m_background = nvgRGB(40, 40, 40);
}

void Checkbox::draw(NVGcontext & ctx, double delta) {

	nvgSave(ctx);

	glm::vec2 position = this->getRelativePosition();

	//Background
	NVGpaint bg;
	bg = nvgBoxGradient(ctx,
		position.x + 1,
		position.y + 1 + 1.5f,
		this->getSize().x - 2,
		this->getSize().y - 2, 3, 2,
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

	// Icon
	if (this->hasIcon() && this->getState("checked"))
	{
		nvgFontSize(ctx, 31.0f);
		nvgFontFace(ctx, "entypo");
		nvgFillColor(ctx, nvgRGBA(255, 255, 255, 128));
		nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

		nvgText(ctx,
			position.x + (this->getSize().x * 0.5f),
			position.y + (this->getSize().y * 0.5f),
			this->getIcon()->get(),
			NULL
		);
	}

	nvgRestore(ctx);
}

 Checkbox::~Checkbox() {


}

