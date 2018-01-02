#pragma once

#include <SDL2/SDL.h>

class Clock
{
public:
	Clock();
	~Clock();

	void update();

	Uint32 m_lastFrame;
	float m_deltaTime;
};
