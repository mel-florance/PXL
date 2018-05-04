#pragma once

#include <map>
#include <string>
#include <algorithm>
#include <vector>

#include "../core/widget.h"

class Tabs : public Widget
{
public:
	Tabs(const glm::vec2& position, const glm::vec2& size);

	enum TabDirection { HORIZONTAL, VERTICAL};

	struct TabHeader 
	{
		TabHeader(const std::string& name) : m_name(name) {}
		~TabHeader() {}

		std::string m_name;
		std::string m_shortcut;
		Icon* m_icon;
		float m_width;
		bool m_hovered = false;
	};

	struct TabContent 
	{
		TabContent(const std::string& name, Widget* widget = nullptr) : m_name(name), m_widget(widget) {}
		~TabContent() {}

		std::string m_name;
		Widget* m_widget;
	};

	struct Tab
	{
		Tab(const std::string& name, TabHeader* header, TabContent* content) : m_name(name), m_header(header), m_content(content) {}

		inline std::string& getName() { return m_name; }
		inline void setName(const std::string& name) { m_name = name; }

		std::string m_name;
		TabHeader* m_header;
		TabContent* m_content;
	};

	void update(double delta);
	void draw(NVGcontext* ctx, double delta);

	void onMouseMove(const SDL_Event& event);
	void onMouseDown(const SDL_Event& event);
	void onMouseUp(const SDL_Event& event);
	void onWindowResized(const SDL_Event& event);
	void onWindowSizeChanged(const SDL_Event& event);

	Tabs::Tab* addTab(const std::string& name);

	inline bool removeTab(const std::string& name) 
	{
		for (auto tab : m_tabs)
		{
			if (tab->getName() == name)
				m_tabs.erase(std::remove(m_tabs.begin(), m_tabs.end(), tab), m_tabs.end());
		}
	}

	~Tabs();

private:
	TabDirection m_direction = HORIZONTAL;
	NVGalign m_align;
	std::string m_font;
	float m_fontSize;
	float m_blur;
	NVGcolor m_color;
	NVGcolor m_background;
	glm::vec4 m_margin;

	unsigned int m_activeTab;
	std::vector<Tab*> m_tabs;
};