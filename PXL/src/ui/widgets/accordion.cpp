#include "accordion.h"

Accordion::Accordion(const glm::vec2& position, const glm::vec2& size) : Widget(position, size)
{

}

void Accordion::update(double delta)
{

}

void Accordion::draw(NVGcontext* ctx, double delta)
{
	glm::vec2 position = this->getRelativePosition();
	glm::vec2 size = this->getRelativeSize();

	nvgSave(ctx);

	float lh = 30.0f;
	unsigned int i = 0;

	for (auto section : m_sections)
	{
		float y = position.y + (lh * i);

		y += i * (lh * 0.25f);

		nvgBeginPath(ctx);
		nvgRect(ctx,
			position.x + 10.0f,
			y + 60.0f,
			size.x - 20.0f,
			lh
		);

		nvgFillColor(ctx, nvgRGB(50, 50, 50));
		nvgFill(ctx);

		nvgFillColor(ctx, nvgRGB(150, 150, 150));
		nvgFontSize(ctx, 18.0f);
		nvgFontFace(ctx, "segoeui");
		nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

		nvgText(ctx,
			position.x + 45.0f,
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

		i++;
	}
	
	nvgRestore(ctx);
}

Accordion::~Accordion()
{

}