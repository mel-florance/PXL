#pragma once

#include "Light.h"

class PointLight : public Light
{
public:
	PointLight();
	virtual ~PointLight();

private:
	glm::vec3 m_attenuation;
};

