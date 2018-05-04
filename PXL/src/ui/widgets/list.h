#pragma once

#include <vector>
#include <algorithm>
#include <string>

#include "../core/widget.h"

class List : public Widget
{
public:
	List(const glm::vec2& position, const glm::vec2& size, const std::string& font);
	~List();

	void update(double delta);
	void draw(NVGcontext* ctx, double delta);

	void addItem(const std::string& item);

	inline void removeItem(const std::string& item) { 
		m_list.erase(std::remove(m_list.begin(), m_list.end(), item), m_list.end());
	}

private:
	std::vector<std::string> m_list;

	glm::vec4 m_margin;
	NVGalign m_align;
	std::string m_font;
	float m_fontSize;
	float m_blur;
	glm::vec4 m_color;
	NVGcolor m_background;
};