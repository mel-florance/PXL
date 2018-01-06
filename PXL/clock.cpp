#include "clock.h"

auto timePrev = high_resolution_clock::now();

Clock::Clock()
{

}

float Clock::getDelta()
{
	auto timeCurrent = high_resolution_clock::now();
	auto timeDiff = duration_cast< nanoseconds >(timeCurrent - timePrev);
	double delta = timeDiff.count();
	delta /= 1000000000;
	timePrev = timeCurrent;

	return delta;
}

void Clock::update()
{
	m_deltaTime = getDelta();

}

Clock::~Clock()
{

}