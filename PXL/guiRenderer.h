#pragma once

#include "mesh.h"
#include "meshFactory.h"
#include "loader.h"

class GuiRenderer
{
public:
	GuiRenderer(Loader* loader);
	~GuiRenderer();

private:
	Mesh* m_quad;
	Loader* m_loader;
};