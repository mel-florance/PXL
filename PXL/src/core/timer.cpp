
#include "timer.h"
#include "clock.h"

 Timer::Timer(Clock & clock) {

	m_clock = clock;
}

 Timer::~Timer() {


}

void Timer::start() {

	m_startTime = m_clock->getTime();
}

void Timer::stop() {

	m_calls++;
	m_totalTime += (m_clock->getTime() - m_startTime);
	m_startTime = 0;
}

double Timer::report(double divisor) {

	divisor = (divisor == 0) ? m_calls : divisor;
	double result = (m_totalTime == 0 && divisor == 0.0) ? 0.0 : (1000.0 * m_totalTime) / ((double)divisor);

	m_totalTime = 0.0;
	m_calls = 0;

	return result;
}

