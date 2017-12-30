#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	virtual ~DirectionalLight();

private:
	glm::vec3 m_direction;
};

