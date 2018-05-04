
#include "accordion.h"
#include "icon.h"

 Accordion::Accordion(const glm::vec2 & position, const glm::vec2 & size) {

	m_margin = glm::vec4(
		0.0f, // Top
		0.0f, // Right
		0.0f, // Bottom
		0.0f  // Left
	);
}

void Accordion::update(double delta) {


}

void Accordion::draw(NVGcontext & ctx, double delta) {

	glm::vec2 position = this->getRelativePosition();
	glm::vec2 size = this->getRelativeSize();

	position.x += m_margin.w;
	position.y += m_margin.x;

	size.x -= m_margin.w + m_margin.y;
	size.y -= m_margin.x + m_margin.z;

	nvgSave(ctx);

	float lh = 30.0f;
	unsigned int i = 0;
	float stackedHeights = 0.0f;

	for (auto section : m_sections)
	{
		float y = position.y + (lh * i);

		y += i * (lh * 0.25f) + stackedHeights;

		nvgBeginPath(ctx);
		nvgRect(ctx,
			position.x + 10.0f,
			y + 60.0f,
			size.x - 20.0f,
			lh
		);

		if (section.second->m_hovered)
			nvgFillColor(ctx, nvgRGB(60, 60, 60));
		else
			nvgFillColor(ctx, nvgRGB(50, 50, 50));

		nvgFill(ctx);

		nvgFillColor(ctx, nvgRGB(150, 150, 150));
		nvgFontSize(ctx, 18.0f);
		nvgFontFace(ctx, "segoeui");
		nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

		nvgText(ctx,
			position.x + 48.0f,
			y + 75.0f,
			section.second->m_title.c_str(),
			NULL
		);

		nvgFontSize(ctx, 42.0f);
		nvgFontFace(ctx, "entypo");
		nvgFillColor(ctx, nvgRGBA(255, 255, 255, 128));
		nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

		nvgText(ctx,
			position.x + 25.0f,
			y + 75.0f,
			section.second->m_icon->get(),
			NULL
		);

		if (section.second->m_opened) 
		{
			stackedHeights += 150.0f;

			for (auto widget : section.second->m_widgets) 
				this->drawSectionWidget(ctx, delta, widget);
		}

		i++;
	}
	
	nvgRestore(ctx);
}

void Accordion::drawSectionWidget(NVGcontext & ctx, double delta, Widget & widget) {

	widget->update(delta);
	widget->draw(ctx, delta);

	for (auto child : widget->getChildren())
		this->drawSectionWidget(ctx, delta, child);
}

void Accordion::onMouseMove(const SDL_Event & event) {

	glm::vec2 position = this->getRelativePosition();
	glm::vec2 size = this->getRelativeSize();

	position.x += m_margin.w;
	position.y += m_margin.x;

	size.x -= m_margin.w + m_margin.y;
	size.y -= m_margin.x + m_margin.z;

	m_mouse = glm::vec2(event.motion.x, event.motion.y);

	this->setState("hovered", this->intersects(m_mouse));

	float lh = 30.0f;
	unsigned int i = 0;
	float stackedHeights = 0.0f;

	for (auto section : m_sections)
	{
		float y = position.y + (lh * i) + stackedHeights;

		y += i * (lh * 0.25f);

		Rect rect(
			glm::vec2(position.x + 10.0f, y + 60.0f),
			glm::vec2(size.x - 20.0f, lh + stackedHeights)
		);

		section.second->m_hovered = rect.intersects(m_mouse);

		if (section.second->m_opened)
		{
			stackedHeights += 150.0f;
		}

		i++;
	}
}

void Accordion::onMouseDown(const SDL_Event & event) {

	/*glm::vec2 position = this->getRelativePosition();
	glm::vec2 size = this->getRelativeSize();

	position.x += m_margin.w;
	position.y += m_margin.x;

	size.x -= m_margin.w + m_margin.y;
	size.y -= m_margin.x + m_margin.z;

	m_mouse = glm::vec2(event.motion.x, event.motion.y);

	this->setState("hovered", this->intersects(m_mouse));

	if (this->getState("hovered"))
	{
		float lh = 30.0f;
		unsigned int i = 0;
		float stackedHeights = 0.0f;

		for (auto& section : m_sections)
		{
			float y = position.y + (lh * i) + stackedHeights;

			y += i * (lh * 0.25f);

			Rect rect(glm::vec2(position.x + 10.0f, y + 60.0f), glm::vec2(size.x - 20.0f, lh));

			if (rect.intersects(m_mouse) && event.button.button == SDL_BUTTON_LEFT)
			{
				section.second->m_opened = section.second->m_opened != true;

				if (section.second->m_opened)
				{
					stackedHeights += 150.0f;
				}

				section.second->m_icon->setSymbol(section.second->m_opened ? "DOWN_DIR" : "RIGHT_DIR");
			}

			i++;
		}
	}*/
}

void Accordion::onMouseUp(const SDL_Event & event) {

	glm::vec2 position = this->getRelativePosition();
	glm::vec2 size = this->getRelativeSize();

	position.x += m_margin.w;
	position.y += m_margin.x;

	size.x -= m_margin.w + m_margin.y;
	size.y -= m_margin.x + m_margin.z;

	m_mouse = glm::vec2(event.motion.x, event.motion.y);

	this->setState("hovered", this->intersects(m_mouse));

	if (this->getState("hovered"))
	{
		float lh = 30.0f;
		unsigned int i = 0;
		float stackedHeights = 0.0f;

		for (auto& section : m_sections)
		{
			float y = position.y + (lh * i) + stackedHeights;

			y += i * (lh * 0.25f);

			Rect rect(glm::vec2(position.x + 10.0f, y + 60.0f), glm::vec2(size.x - 20.0f, lh));

			section.second->m_hovered = rect.intersects(m_mouse);

			if (section.second->m_hovered == true && event.button.button == SDL_BUTTON_LEFT)
			{
				section.second->m_opened = section.second->m_opened;

				if (section.second->m_opened == true)
				{
					stackedHeights += 150.0f;
				}

				section.second->m_icon->setSymbol(section.second->m_opened ? "DOWN_DIR" : "RIGHT_DIR");
			}

			i++;
		}
	}
}

void Accordion::onWindowResized(const SDL_Event & event) {


}

void Accordion::onWindowSizeChanged(const SDL_Event & event) {


}

 Accordion::~Accordion() {


}

