#pragma once

#include "../core/widget.h"

class Form : public Widget
{
public:
	Form(const glm::vec2& position, const glm::vec2& size);
	~Form();
};

