#include "splitter.h"
#include "layout.h"

Splitter::Splitter(const glm::vec2& position, const glm::vec2& size) : Widget(position, size)
{
	m_background = nvgRGB(0, 0, 0);
}

void Splitter::update(double delta)
{

}

void Splitter::draw(NVGcontext* ctx, double delta)
{
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

void Splitter::onMouseMove(const SDL_Event& event)
{
	m_mouse = glm::vec2(event.motion.x, event.motion.y);
	this->setState("hovered", this->intersects(m_mouse));

	if (this->getState("hovered") && event.button.button != SDL_BUTTON_RIGHT)
	{
		m_background = nvgRGB(255, 0, 0);
		if (this->getLayout()->getWindow() != nullptr)
		{
			SDL_SetCursor(this->getLayout()->getWindow()->getMCursor(this->getLayout()->getDirection() == StackDirection::HORIZONTAL ? "SIZEWE" : "SIZENS"));
		}
	}
	else {
		m_background = nvgRGB(0, 0, 0);
		//SDL_SetCursor(SDL_GetDefaultCursor());
	}
}

void Splitter::onMouseDown(const SDL_Event& event)
{

}

void Splitter::onMouseUp(const SDL_Event& event)
{

}

void Splitter::onWindowResized(const SDL_Event& event)
{

}

void Splitter::onWindowSizeChanged(const SDL_Event& event)
{

}

Splitter::~Splitter()
{

}
