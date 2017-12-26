#pragma once

#include "clock.h"

class Engine
{
public:
	Engine();
	~Engine();

	const Clock* m_clock;
};

