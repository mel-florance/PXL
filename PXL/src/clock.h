#pragma once

#include <chrono>
#include <iostream>
#include <SDL2/SDL.h>

class Clock
{
public:
	Clock();
	~Clock();

	double getTime();

private:
	std::chrono::steady_clock::time_point m_epoch;
};
