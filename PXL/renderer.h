#pragma once

#include "scene.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void render(Scene* scene);
};

