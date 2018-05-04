
#include "splitter.h"

 Splitter::Splitter(const glm::vec2 & position, const glm::vec2 & size) {

	m_background = nvgRGB(0, 0, 0);
	m_offset = glm::vec2(0.0f);
}

void Splitter::update(double delta) {

	if (this->getState("hovered")) 
	{
		m_background = nvgRGB(47, 124, 202);

		if (this->getLayout()->getWindow() != nullptr)
		{
			std::string cursor = this->getLayout()->getDirection() == StackDirection::HORIZONTAL ? "SIZEWE" : "SIZENS";
			SDL_SetCursor(this->getLayout()->getWindow()->getMCursor(cursor));
		}
	}
	else 
	{
		m_background = nvgRGB(0, 0, 0);
	}

	if (this->getState("dragged"))
	{
		glm::vec2 pos = this->getPosition();

		if (this->getLayout()->getDirection() == StackDirection::HORIZONTAL) 
		{
			this->setPosition(glm::vec2(pos.x + (m_mouse.x - pos.x), pos.y));
		}
		else {
			this->setPosition(glm::vec2(pos.x, pos.y + (m_mouse.y - pos.y)));
		}
	}
}

void Splitter::draw(NVGcontext & ctx, double delta) {

	nvgSave(ctx);

	glm::vec2 position = this->getPosition();
	glm::vec2 size = this->getSize();

	nvgBeginPath(ctx);
	nvgRect(ctx,
		position.x,
		position.y,
		size.x,
		size.y);

	nvgFillColor(ctx, m_background);
	nvgFill(ctx);

	nvgRestore(ctx);
}

void Splitter::onMouseMove(const SDL_Event & event) {

	m_mouse = glm::vec2(event.motion.x, event.motion.y);
	glm::vec2 position = this->getPosition();
	glm::vec2 size = this->getSize();

	float threshold = 5.0f;

	Rect rect(glm::vec2(position.x - threshold, position.y - threshold), glm::vec2(size.x + threshold * 2.0f, size.y + threshold * 2.0f));

	this->setState("hovered", rect.intersects(m_mouse));

	if (!this->getState("hovered")) 
		SDL_SetCursor(this->getLayout()->getWindow()->getMCursor("ARROW"));
	else
	{
		if (this->getLayout()->getWindow() != nullptr)
		{
			std::string cursor = this->getLayout()->getDirection() == StackDirection::HORIZONTAL ? "SIZEWE" : "SIZENS";
			SDL_SetCursor(this->getLayout()->getWindow()->getMCursor(cursor));
		}
	}
}

void Splitter::onMouseDown(const SDL_Event & event) {

	if (this->getState("hovered") && event.button.button == SDL_BUTTON_LEFT)
	{
		this->setState("dragged", true);
	}
}

void Splitter::onMouseUp(const SDL_Event & event) {

	this->setState("dragged", false);
}

void Splitter::onWindowResized(const SDL_Event & event) {


}

void Splitter::onWindowSizeChanged(const SDL_Event & event) {


}

 Splitter::~Splitter() {


}

