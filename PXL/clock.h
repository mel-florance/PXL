#pragma once

class Clock
{
public:
	Clock();
	virtual ~Clock();

	int m_lastFrame;
	int m_deltaTime;
};

