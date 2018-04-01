#pragma once

#include <string>

#include "layout.h"

class BoxLayout : public Layout
{
public:
	BoxLayout(const std::string& name, const glm::vec2& position, const glm::vec2& size);
	~BoxLayout();

private:

};

