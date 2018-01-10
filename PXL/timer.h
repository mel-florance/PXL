#pragma once

#include "clock.h"

class Timer
{
public:
	Timer(Clock* clock);
	~Timer();

	void start();
	void stop();
	double report(double divisor);

private:
	int m_calls;
	Clock* m_clock;	
	double m_startTime;
	double m_totalTime;
};

