
#include "table.h"
#include "eventListener.h"
#include "scrollbar.h"

 Table::Table(const glm::vec2 & position, const glm::vec2 & size, const std::string & font) {

	m_margin = glm::vec4(
		30.0f, // Top
		0.0f, // Right
		0.0f, // Bottom
		0.0f  // Left
	);

	m_font = font;
	m_fontSize = 18.0f;
	m_blur = 0.0f;
	m_align = NVG_ALIGN_LEFT;
	m_color = nvgRGBA(255, 255, 255, 100);
	m_background = nvgRGB(40, 40, 40);
	m_stripLines = nvgRGB(35, 35, 35);
	m_borderColor = nvgRGB(70, 70, 70);

	m_scrollbar = new Scrollbar(glm::vec2(0.0f), glm::vec2(13.0f, 100.0f));
	m_scrollbar->setExpandModeX(Widget::ExpandMode::FIXED);
	m_scrollbar->setExpandModeY(Widget::ExpandMode::PARENT);
	m_scrollbar->setPositionModeX(Widget::ExpandMode::LAYOUT);
	m_scrollbar->setPositionModeY(Widget::ExpandMode::LAYOUT);
	m_scrollbar->setAlignment(Widget::Alignment::TOP_RIGHT);
	m_scrollbar->addEventListener("onMouseMove", &Table::onScrollbarDragged);

	this->addChild(m_scrollbar);
}

 Table::~Table() {


}

void Table::update(double delta) {


}

void Table::draw(NVGcontext & ctx, double delta) {

	nvgSave(ctx);

	glm::vec2 pos = this->getRelativePosition();
	glm::vec2 size = this->getRelativeSize();

	pos.x += m_margin.w;
	pos.y += m_margin.x;

	nvgScissor(ctx, pos.x, pos.y, size.x, size.y);

	pos.y -= m_offsetScroll;

	nvgBeginPath(ctx);
	nvgRect(ctx,
		pos.x,
		pos.y,
		size.x,
		size.y
	);

	nvgFillColor(ctx, m_background);
	nvgFill(ctx);


	int i = 0, j = 0;
	float lh = 25.0f;
	float cw = 0;
	for (unsigned int r = 0; r < m_rows.size(); r++)
	{
		i++;
		unsigned int cs = m_rows[r]->m_columns.size();
		float y = pos.y + (lh * i);
		cw = ceil(size.x / cs);

		if (i % 2 == 0) {
			nvgBeginPath(ctx);
			nvgRect(ctx,
				pos.x,
				y - lh,
				size.x,
				lh
			);

			nvgFillColor(ctx, m_stripLines);
			nvgFill(ctx);
		}

		for (unsigned int c = 0; c < cs; c++)
		{
			float x = pos.x + (cw * j);

			if (j > 0) 
			{
				nvgBeginPath(ctx);
				nvgRect(ctx,
					x,
					y - lh,
					1.0f,
					lh
				);

				nvgFillColor(ctx, m_borderColor);
				nvgFill(ctx);
			}

			nvgFontSize(ctx, m_fontSize);
			nvgFontFace(ctx, m_font.c_str());
			nvgTextAlign(ctx, m_align);
			nvgFontBlur(ctx, m_blur);
			nvgFillColor(ctx, m_color);

			NVGtextRow rows[1];
			const char* text = m_rows[r]->m_columns[c]->m_data.c_str();
			const char* start;
			const char* end;

			start = text;
			end = text + strlen(text);

			int nrows = nvgTextBreakLines(ctx, start, end, cw - 10, rows, 1);
			NVGtextRow* row = &rows[0];

			nvgText(ctx,
				x + 10,
				y - 7,
				row->start,
				row->end
			);

			j++;
		}

		j = 0;
	}

	nvgResetScissor(ctx);
	nvgRestore(ctx);
}

void Table::onScrollbarDragged(const CallbackData & data)
{

	Scrollbar* sender = (Scrollbar*)data.sender;
	Table* parent = (Table*)data.sender->getParent();

	parent->setOffsetScroll(sender->getHandleDragOffset());
}

void Table::onMouseWheel(const SDL_Event & event) {

	if (this->getState("hovered"))
	{
		glm::vec2 position = this->getRelativePosition();
		glm::vec2 size = this->getRelativeSize();
		float hy = position.y + 30.0f;
		float drag = m_scrollbar->getHandleDragOffset();
		float handleHeight = m_scrollbar->getHandleHeight();
		drag += event.wheel.y * -3.0f;

		if (hy + drag < hy)
			drag = 0;

		if (hy + drag + handleHeight > hy + (size.y - 30.0f))
			drag = (size.y - 30.0f) - handleHeight;

		m_scrollbar->setHandleDragOffset(drag);
		this->setOffsetScroll(drag);
	}
}

void Table::onMouseMove(const SDL_Event & event) {

	m_mouse = glm::vec2(event.motion.x, event.motion.y);
	this->setState("hovered", this->intersects(m_mouse));
}

void Table::onMouseUp(const SDL_Event & event) {

}

void Table::onMouseDown(const SDL_Event & event) {

}

