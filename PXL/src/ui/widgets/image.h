#pragma once

#include <string>

#include "../nanovg/nanovg.h"
#include "../core/widget.h"

class Image : public Widget
{
public:
	Image(NVGcontext* ctx, const std::string& name, glm::vec2& position, glm::vec2& size);
	~Image();

	inline std::string& getName() { return m_name; }
	inline void setName(const std::string& name) { m_name = name; }

	void draw(NVGcontext* ctx, double delta);
private:
	std::string m_name;
	NVGcontext* m_ctx;
	int m_image;
};

