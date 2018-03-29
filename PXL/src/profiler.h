#pragma once

#include <map>
#include <string>

#include "timer.h"

class Profiler
{
public:
	Profiler(Clock* clock);
	~Profiler();

	Timer* getTimer(const std::string& name);
	void addTimer(const std::string& name);
	void stopTimer(const std::string& name);
	void startTimer(const std::string& name);
	double getReport(const std::string& name);

private:
	Clock* m_clock;
	std::map<std::string, Timer*> m_timers;
};

