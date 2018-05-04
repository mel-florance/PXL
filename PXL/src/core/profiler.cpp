
#include "profiler.h"
#include "clock.h"
#include "timer.h"

 Profiler::Profiler(Clock & clock) {

	m_clock = clock;
}

 Profiler::~Profiler() {

	for (const auto &timer : m_timers)
		delete timer.second;
}

Timer Profiler::getTimer(const std::string & name) {

	for (auto &timer : m_timers)
		if (timer.first == name)
			return timer.second;

	return nullptr;
}

void Profiler::addTimer(const std::string & name) {

	m_timers[name] = new Timer(m_clock);
}

void Profiler::stopTimer(const std::string & name) {

	m_timers[name]->stop();
}

void Profiler::startTimer(const std::string & name) {

	m_timers[name]->start();
}

double Profiler::getReport(const std::string & name) {

	return m_timers[name]->report(0);
}

