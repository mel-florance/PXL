#pragma once

#include <vector>
#include <string>
#include <algorithm>

#include "../core/widget.h"
#include "icon.h"

class Accordion : public Widget
{
public:
	Accordion(const glm::vec2& position, const glm::vec2& size);

	void update(double delta);
	void draw(NVGcontext* ctx, double delta);

	struct Section 
	{
		Section(const std::string& title) : m_title(title), m_opened(true) 
		{
			m_icon = new Icon("RIGHT_DIR", glm::vec2(0.0f), glm::vec2(0.0f));
		}

		~Section() 
		{
			delete m_icon;
		}
	
		enum StackDirection { HORIZONTAL, VERTICAL };
		
		inline void addWidget(Widget* widget) { m_widgets.emplace_back(widget); }
		inline bool removeWidget(Widget* widget) 
		{
			auto exists = std::find(m_widgets.begin(), m_widgets.end(), widget);

			if (exists != m_widgets.end())
				m_widgets.erase(exists);
		}

		bool m_opened;
		std::string m_title;
		Icon* m_icon;
		StackDirection m_direction;
		std::vector<Widget*> m_widgets;
	};

	inline void addSection(const std::string& title)
	{
		Accordion::Section* section = new Section(title);
		m_sections[title] = section;
	}

	inline bool removeSection(const std::string& name)
	{
		auto exists = m_sections.find(name);

		if (exists != m_sections.end())
			m_sections.erase(exists);
	}

	~Accordion();

private:
	std::map<std::string, Section*> m_sections;
};

