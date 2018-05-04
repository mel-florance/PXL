
#include "clock.h"

 Clock::Clock() {


}

 Clock::~Clock() {


}

double Clock::getTime() {

	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_epoch).count() / 1000000000.0;
}

