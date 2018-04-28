#include "tabs.h"
#include "../core/guiManager.h"

Tabs::Tabs(const glm::vec2& position, const glm::vec2& size) : Widget(position, size)
{
	m_background = nvgRGBA(255, 255, 255, 0);
	m_margin = glm::vec4(
		17.0f, // Top
		0.0f, // Right
		0.0f, // Bottom
		0.0f  // Left
	);

	m_font = "segoeui";
	m_fontSize = 18.0f;
	m_blur = 0.0f;
	m_align = NVG_ALIGN_MIDDLE;
	m_color = nvgRGB(150, 150, 150);
	m_activeTab = 0;
}

void Tabs::update(double delta)
{

}

void Tabs::draw(NVGcontext* ctx, double delta)
{
	nvgSave(ctx);

	glm::vec2 position = this->getRelativePosition();
	glm::vec2 size = this->getRelativeSize();

	position.x += m_margin.w;
	position.y += m_margin.x;

	//size.x -= (m_margin.w + m_margin.y);
	//size.y -= (m_margin.x + m_margin.z);

	// Tabs background
	nvgBeginPath(ctx);
	nvgRect(ctx,
		position.x,
		position.y,
		size.x,
		size.y
	);

	nvgFillColor(ctx, m_background);
	nvgFill(ctx);

	float fontSize = 18.0f;
	
	nvgFontSize(ctx, fontSize);
	nvgFontFace(ctx, m_font.c_str());
	nvgTextAlign(ctx, m_align);
	nvgFontBlur(ctx, m_blur);

	// Draw tabs
	float stackedWidth = 0.0f;
	float itemWidth = ceil(size.x / m_tabs.size());

	unsigned int i = 0;
	for (auto tab : m_tabs)
	{
		tab->m_header->m_width = itemWidth;
		stackedWidth += tab->m_header->m_width;
		float textWidth = nvgTextBounds(ctx, 0, 0, tab->m_name.c_str(), NULL, 0);
		float x = position.x + stackedWidth - tab->m_header->m_width;

		// Draw tab item vertical separator
		nvgBeginPath(ctx);
		nvgRect(ctx,
			x - 0.5f,
			position.y + 13.0f,
			1.0f,
			size.y - 8.0f
		);

		nvgFillColor(ctx, nvgRGB(10, 10, 10));
		nvgFill(ctx);

		// Draw tab item background
		nvgBeginPath(ctx);
		nvgRect(ctx,
			x,
			position.y + 13.0f,
			tab->m_header->m_width + 15.0f,
			size.y - 8.0f
		);

		// Draw tab item background
		if (i == m_activeTab) 
			nvgFillColor(ctx, nvgRGB(40, 40, 40));
		else if (tab->m_header->m_hovered)
			nvgFillColor(ctx, nvgRGB(35, 35, 35));
		else
			nvgFillColor(ctx, nvgRGB(30, 30, 30));

		nvgFill(ctx);

		if(i == m_activeTab)
			nvgFillColor(ctx, nvgRGB(47, 124, 202));
		else if(tab->m_header->m_hovered)
			nvgFillColor(ctx, nvgRGB(130, 130, 130));
		else
			nvgFillColor(ctx, nvgRGB(100, 100, 100));

		// Draw tab item text
		nvgText(ctx,
			x + (itemWidth * 0.5f) - (textWidth * 0.5f),
			position.y + 8.0f + (size.y * 0.5f),
			tab->m_name.c_str(),
			NULL
		);

		if (i == m_activeTab && tab->m_content != nullptr) 
		{
			if (tab->m_content->m_widget != nullptr)
			{		
				tab->m_content->m_widget->draw(ctx, delta);
			}
		}

		i++;
	}

	nvgRestore(ctx);
}

void Tabs::onMouseMove(const SDL_Event& event)
{
	m_mouse = glm::vec2(event.motion.x, event.motion.y);
	this->setState("hovered", this->intersects(m_mouse));
	glm::vec2 position = this->getRelativePosition();
	glm::vec2 size = this->getRelativeSize();

	position.x += m_margin.w;
	position.y += m_margin.x;

	float stackedWidth = 0.0f;
	float itemWidth = ceil(size.x / m_tabs.size());

	for (auto tab : m_tabs)
	{
		tab->m_header->m_width = itemWidth;
		stackedWidth += tab->m_header->m_width;
		float x = position.x + stackedWidth - tab->m_header->m_width;

		Rect rect(
			glm::vec2(x, position.y + 13.0f),
			glm::vec2(tab->m_header->m_width, size.y - 8.0f)
		);

		tab->m_header->m_hovered = rect.intersects(m_mouse);
	}
}

void Tabs::onMouseDown(const SDL_Event& event)
{

}

void Tabs::onMouseUp(const SDL_Event& event)
{
	for (unsigned int i = 0; i < m_tabs.size(); i++)
		if (m_tabs[i]->m_header->m_hovered && i != m_activeTab)
			m_activeTab = i;
}

void Tabs::onWindowResized(const SDL_Event& event)
{

}

void Tabs::onWindowSizeChanged(const SDL_Event& event)
{

}

Tabs::Tab* Tabs::addTab(const std::string & name)
{
	TabHeader* header = new TabHeader(name);
	TabContent* content = new TabContent(name);
	Tab* tab = new Tab(name, header, content);

	m_tabs.emplace_back(tab);
	return tab;
}


Tabs::~Tabs()
{

}
