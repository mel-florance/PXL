#pragma once

#include <vector>
#include <algorithm>
#include <string>

#include "../core/widget.h"

class List : public Widget
{
public:
	List(const glm::vec2& position, const glm::vec2& size);
	~List();

	void update(double delta);
	void draw(NVGcontext* ctx);

	inline void addItem(const std::string& item) { m_list.emplace_back(item); }
	inline void removeItem(const std::string& item) { 
		m_list.erase(std::remove(m_list.begin(), m_list.end(), item), m_list.end());
	}

private:
	std::vector<std::string> m_list;
};