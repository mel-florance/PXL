#pragma once

#include <chrono>

using namespace std::chrono;

#include <SDL2/SDL.h>

class Clock
{
public:
	Clock();
	~Clock();

	void update();

	float getDelta();

	Uint32 m_lastFrame;
	float m_deltaTime;
};
