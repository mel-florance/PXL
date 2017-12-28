#pragma once

class Clock
{
public:
	Clock();
	~Clock();

	void update();

	int m_lastFrame;
	int m_deltaTime;
};
