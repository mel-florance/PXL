
#include "scrollbar.h"
#include "icon.h"
#include "rect.h"

 Scrollbar::Scrollbar(const glm::vec2 & position, const glm::vec2 & size) {

	m_background = nvgRGB(20, 20, 20);
	m_handleHeight = size.y;
	m_handleBackground = nvgRGB(60, 60, 60);
	m_margin = glm::vec4(
		30.0f, // Top
		0.0f, // Right
		0.0f, // Bottom
		0.0f  // Left
	);

	m_firstIcon = new Icon("TOP_DIR", glm::vec2(0.0f), glm::vec2(10.0f, 10.0f));
	m_secondIcon = new Icon("DOWN_DIR", glm::vec2(0.0f), glm::vec2(10.0f, 10.0f));
	m_handle = new Rect(glm::vec2(0.0f), glm::vec2(10.0f, 10.0f));
	m_handleDragged = false;
	m_handleDragOffset = 0.0f;
	m_handleMargin = glm::vec4(
		15.0f,
		2.0f,
		15.0f,
		2.0f
	);
}

void Scrollbar::update(double delta) {


}

void Scrollbar::draw(NVGcontext & ctx, double delta) {

	glm::vec2 position = this->getRelativePosition();
	glm::vec2 size = this->getRelativeSize();

	position.x += m_margin.w;
	position.y += m_margin.x;

	size.x -= (m_margin.w + m_margin.y);
	size.y -= (m_margin.x + m_margin.z);

	nvgSave(ctx);

	// Background
	nvgBeginPath(ctx);
	nvgRect(ctx,
		position.x + size.x,
		position.y,
		13.0f,
		size.y 
	);
	nvgFillColor(ctx, m_background);
	nvgFill(ctx);


	// Handle
	nvgBeginPath(ctx);
	nvgRect(ctx,
		position.x + size.x + m_handleMargin.w,
		position.y + m_handleDragOffset + m_handleMargin.x,
		13.0f - (m_handleMargin.w + m_handleMargin.y),
		m_handleHeight - (m_handleMargin.x + m_handleMargin.z)
	);

	nvgFillColor(ctx, m_handleBackground);
	nvgFill(ctx);

	// Icons
	if (m_firstIcon != nullptr && m_secondIcon != nullptr)
	{
		nvgFontSize(ctx, 40.0f);
		nvgFontFace(ctx, "entypo");
		nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

		nvgText(ctx,
			position.x + size.x + 7.0f,
			position.y + 7.0f,
			m_firstIcon->get(),
			NULL
		);

		nvgText(ctx,
			position.x + size.x + 7.0f,
			position.y - 7.0f + size.y,
			m_secondIcon->get(),
			NULL
		);
	}

	nvgRestore(ctx);
}

void Scrollbar::onKeyDown(const SDL_Event & event) {


}

void Scrollbar::onTextInput(const SDL_Event & event) {


}

void Scrollbar::onKeyUp(const SDL_Event & event) {


}

void Scrollbar::onMouseMove(const SDL_Event & event) {

	m_mouse = glm::vec2(event.motion.x, event.motion.y);

	glm::vec2 position = this->getRelativePosition();
	glm::vec2 size = this->getRelativeSize();

	position.x += m_margin.w;
	position.y += m_margin.x;

	size.x -= (m_margin.w + m_margin.y);
	size.y -= (m_margin.x);

	Rect rect(
		glm::vec2(position.x + size.x, position.y + m_handleDragOffset),
		glm::vec2(10.0f, m_handleHeight)
	);

	this->setState("hovered", rect.intersects(m_mouse));

	float hx = position.x + size.x;
	float hy = position.y;

	if (m_handleDragged)
	{
		float offset = m_mouse.y - hy;
		float drag = -m_margin.x + offset - m_dragDelta.y;

		if (hy + drag < hy)
			drag = 0.0f;

		if (hy + drag + m_handleHeight > hy + size.y)
			drag = size.y - m_handleHeight;

		m_handleDragOffset = drag;
		this->handleEventListener("onMouseMove", { this });
	}
}

void Scrollbar::onMouseWheel(const SDL_Event & event) {

	if (this->getState("hovered")) 
	{
		glm::vec2 position = this->getRelativePosition();
		glm::vec2 size = this->getRelativeSize();

		position.x += m_margin.w;
		position.y += m_margin.x;

		size.x -= (m_margin.w + m_margin.y);
		size.y -= (m_margin.x);

		float hy = position.y;
		m_handleDragOffset += event.wheel.y * -3.0f;

		if (hy + m_handleDragOffset < hy)
			m_handleDragOffset = 0;

		if (hy + m_handleDragOffset + m_handleHeight > hy + size.y)
			m_handleDragOffset = size.y - m_handleHeight;

		this->handleEventListener("onMouseMove", { this });
	}
}

void Scrollbar::onMouseDown(const SDL_Event & event) {

	if (this->getState("hovered") && event.button.button == SDL_BUTTON_LEFT)
	{
		glm::vec2 position = this->getRelativePosition();
		float hy = position.y + m_margin.x + m_handleDragOffset;

		m_handleDragged = true;
		m_dragDelta.y = m_mouse.y - hy;
	}
}

void Scrollbar::onMouseUp(const SDL_Event & event) {

	if(event.button.button == SDL_BUTTON_LEFT)
		m_handleDragged = false;
}

void Scrollbar::onWindowResized(const SDL_Event & event) {


}

void Scrollbar::onWindowSizeChanged(const SDL_Event & event) {


}

void Scrollbar::computeHandleHeight(float parentHeight, float scrollMax) {

	float handleHeight = (scrollMax / parentHeight) * 100.0f;
	handleHeight = handleHeight > 100.0f ? 100.0f : handleHeight;

	m_handleHeight = (handleHeight * scrollMax) / 100.0f;
}

 Scrollbar::~Scrollbar() {

	delete m_firstIcon;
	delete m_secondIcon;
	delete m_handle;
}

