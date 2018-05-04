
#include "window.h"
#include "eventListener.h"
#include "rect.h"

 Window::Window(const std::string & text, const glm::vec2 & position, const glm::vec2 & size, const std::string & font) {

	m_margin = glm::vec4(
		0.0f, // Top
		0.0f, // Right
		0.0f, // Bottom
		0.0f  // Left
	);

	m_header.text = text;
	m_header.font = font;
	m_header.fontSize = 18.0f;
	m_header.blur = 0.0f;
	m_header.align = NVG_ALIGN_LEFT;
	m_header.color = nvgRGBA(255, 255, 255, 128);
	m_header.rect = new Rect(glm::vec2(position.x + 1, position.y + 1), glm::vec2(size.x - 2, 30));
	m_header.isFixedBottom = false;

	m_drawingShadow = true;
	m_opacity = 1.0f;
	m_background = nvgRGB(40, 40, 40);
	m_borderRadius = 0.0f;
	m_windowDragOffset = glm::vec2(0.0f);

	const glm::vec2 iconPosition = glm::vec2(
		position.x + m_header.rect->getSize().x - m_header.rect->getSize().y * 0.55f,
		position.y + m_header.rect->getSize().y * 0.55f
	);
	const glm::vec2 iconSize = glm::vec2(m_header.rect->getSize().x * 0.15f, m_header.rect->getSize().x * 0.15f);
	Icon* icon = new Icon("CANCEL_SQUARED", iconPosition, iconSize);
	icon->addEventListener("onClosed", &Window::onClosed);
	this->setIcon(icon);

	this->addEventListener("onClosed", &Window::onClosed);
}

 Window::~Window() {

	delete m_header.rect;
}

void Window::onKeyDown(const SDL_Event & event) {


}

void Window::onTextInput(const SDL_Event & event) {


}

void Window::onKeyUp(const SDL_Event & event) {


}

void Window::onMouseMove(const SDL_Event & event) {

	m_mouse = glm::vec2((float)event.motion.x, (float)event.motion.y);
	this->setState("hovered", this->intersects(m_mouse));
	glm::vec2 position = this->getRelativePosition();

	if (this->getState("dragged"))
	{
		glm::vec2 offset = m_mouse - position;
		m_windowDragOffset = offset - m_dragDelta;

		position += m_windowDragOffset;
		this->setPosition(position);
	}

	if (this->getState("closable"))
	{
		glm::vec2 pos = glm::vec2(position.x + m_header.rect->getSize().x - m_header.rect->getSize().y * 1.0f, position.y);
		glm::vec2 size = glm::vec2(m_header.rect->getSize().y, m_header.rect->getSize().y);
		Rect rect(pos, size);

		this->getIcon()->setState("hovered", rect.intersects(m_mouse));
	}


}

void Window::onMouseDown(const SDL_Event & event) {

	if (this->getState("hovered"))
	{
		if (this->getState("draggable") && event.button.button == SDL_BUTTON_LEFT)
		{
			LayerManager* layerManager = this->getLayout()->getGuiManager()->getLayerManager();
			layerManager->addWidget(0, this);

			glm::vec2 position = this->getRelativePosition();
			glm::vec2 size = this->getRelativeSize();
			position += m_windowDragOffset;

			position.x += m_margin.w;
			position.y += m_margin.x;


			size.x -= m_margin.w + m_margin.y;
			size.y -= m_margin.x + m_margin.z;

			m_header.rect->setPosition(glm::vec2(position.x + 1, position.y + 1));
			m_header.rect->setSize(glm::vec2(size.x - 2, 30));

			if (m_header.rect->intersects(m_mouse))
			{
				if (this->getState("closable"))
				{
					if (this->getIcon()->getState("hovered"))
						this->setState("dragged", false);
					else {

						this->setState("dragged", true);
						glm::vec2 pos = position + m_windowDragOffset;
						m_dragDelta = m_mouse - pos;
					}
				}
				else
				{
					this->setState("dragged", true);
					glm::vec2 pos = position + m_windowDragOffset;
					m_dragDelta = m_mouse - pos;
				}
			}
		}
	}
}

void Window::onMouseUp(const SDL_Event & event) {

	if (this->getIcon()->getState("hovered"))
	{
		if (event.button.button == SDL_BUTTON_LEFT) 
		{
			if (this->hasListener("onClosed")) 
			{
				LayerManager* layerManager = this->getLayout()->getGuiManager()->getLayerManager();
				layerManager->removeWidget(0, this);

				this->getLayout()->removeWidget(this);
			}
		}
	}

	m_windowDragOffset = glm::vec2(0.0f);
	this->setState("dragged", false);

	//if (this->getState("hovered") == false && this->getState("draggable") && event.button.button == SDL_BUTTON_LEFT)
	//{
	//	LayerManager* layerManager = this->getLayout()->getGuiManager()->getLayerManager();
	//	layerManager->removeWidget(0, this);
	//}

}

void Window::onWindowResized(const SDL_Event & event) {


}

void Window::onWindowSizeChanged(const SDL_Event & event) {


}

void Window::onClosed(const CallbackData & data)
{

	data.sender->getLayout()->removeWidget(data.sender);
}

void Window::drawBackground(NVGcontext & ctx, glm::vec2 & position) {
}

void Window::drawShadow(NVGcontext & ctx, glm::vec2 & position) {
}

void Window::drawHeader(NVGcontext & ctx, glm::vec2 & position) {
}

void Window::drawHeaderText(NVGcontext & ctx, glm::vec2 & position) {
}

void Window::drawIcon(NVGcontext & ctx, glm::vec2 & position) {
}

void Window::draw(NVGcontext & ctx, double delta) {

	nvgSave(ctx);

	glm::vec2 position = this->getRelativePosition();
	glm::vec2 size = this->getRelativeSize();

	position.x += m_margin.w;
	position.y += m_margin.x;

	size.x -= m_margin.w + m_margin.y;
	size.y -= m_margin.x + m_margin.z;



	nvgBeginPath(ctx);
	nvgRoundedRect(ctx,
		position.x,
		position.y,
		size.x,
		size.y,
		m_borderRadius
	);

	nvgFillColor(ctx, nvgRGBAf(m_background.r, m_background.g, m_background.b, m_opacity));
	nvgFill(ctx);

	if (m_drawingShadow == true)
	{
		// Shadow
		m_shadowPaint = nvgBoxGradient(
			ctx,
			position.x,
			position.y + 2,
			size.x,
			size.y,
			m_borderRadius * 2,
			8.0f,
			nvgRGBA(0, 0, 0, 255),
			nvgRGBA(0, 0, 0, 0)
		);

		nvgBeginPath(ctx);
		nvgRect(ctx,
			position.x - 10,
			position.y - 10,
			size.x + 20,
			size.y + 30
		);

		nvgRoundedRect(ctx,
			position.x,
			position.y,
			size.x,
			size.y,
			m_borderRadius
		);

		nvgPathWinding(ctx, NVG_HOLE);
		nvgFillPaint(ctx, m_shadowPaint);
		nvgFill(ctx);
	}

	glm::vec2 pos;
	if (m_header.isFixedBottom == false)
		pos = glm::vec2(position.x, position.y);
	else
		pos = glm::vec2(position.x, position.y + (this->getLayout()->getComputedSize().y - m_header.rect->getSize().y));

	m_header.rect->setPosition(pos);
	m_header.rect->setSize(glm::vec2(size.x, 30));

	// Header
	m_headerPaint = nvgLinearGradient(ctx,
		pos.x,
		pos.y,
		pos.x,
		pos.y,
		nvgRGBA(60, 60, 60, 255),
		nvgRGBA(20, 20, 20, 255)
	);

	nvgBeginPath(ctx);
	nvgRoundedRect(ctx,
		pos.x,
		pos.y,
		size.x,
		m_header.rect->getSize().y,
		m_borderRadius - 1
	);
	nvgFillPaint(ctx, m_headerPaint);
	nvgFill(ctx);
	nvgBeginPath(ctx);
	nvgMoveTo(ctx,
		pos.x + 0.5f,
		pos.y + 0.5f 
	);
	nvgLineTo(ctx,
		pos.x + 0.5f + size.x - 1,
		pos.y + 0.5f 
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
		pos.x + 10.0f,
		pos.y + m_header.rect->getSize().y * 0.66f,
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

void Window::update(double delta) {

	//if (this->getState("dragged"))
	//{
	//	glm::vec2 pos = this->getRelativePosition();
	//	this->setComputedPosition(pos + (m_mouse - pos));
	//}	
}

