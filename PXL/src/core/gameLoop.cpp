
#include "gameLoop.h"
#include "engine.h"
#include "profiler.h"
#include "clock.h"

 GameLoop::GameLoop(Engine & engine) {

	m_engine = engine;
	m_clock = new Clock();
	m_profiler = new Profiler(m_clock);

	m_profiler->addTimer("frame");
	m_profiler->addTimer("update");
	m_profiler->addTimer("render");
	m_profiler->addTimer("sleep");

	m_updateCallback = nullptr;
	m_renderCallback = nullptr;

	m_running = false;
	m_render = false;
	m_sleepTime = 1;
	m_fps = 0.0f;
	m_lastTime = 0.0;
	m_startTime = 0.0;
	m_frameTime = 1.0 / 60.0;
	m_frameCounter = 0.0;
	m_unprocessedTime = 0;
	m_frames = 0;
	m_passedTime = 0.0;
	m_fpsIndex = 0;
	m_fpsSum = 0.0f;
}

void GameLoop::start() {

	if (m_running)
		return;

	m_running = true;
	m_lastTime = m_clock->getTime();
	m_frameCounter = 0;
	m_unprocessedTime = 0;
	m_frames = 0;

	while (m_running)
	{
		m_render = false;
		m_startTime = m_clock->getTime();

		m_passedTime = m_startTime - m_lastTime;
		m_lastTime = m_startTime;

		m_unprocessedTime += m_passedTime;
		m_frameCounter += m_passedTime;

		if (m_frameCounter >= 0.1f)
		{
			m_fps = this->computeAverageFps((1.0f / (float)m_passedTime));
			m_frames = 0;
			m_frameCounter = 0;
		}

		m_profiler->startTimer("frame");

		while (m_unprocessedTime > m_frameTime)
		{
			m_profiler->startTimer("update");
			if (m_updateCallback != nullptr)
				m_updateCallback(this, m_engine);
			m_profiler->stopTimer("update");

			m_render = true;
			m_unprocessedTime -= m_frameTime;
		}

		if (m_render)
		{
			m_profiler->startTimer("render");
			if (m_renderCallback != nullptr)
				m_renderCallback(this, m_engine);
			m_profiler->stopTimer("render");

			m_frames++;
		}
		else
		{
			m_profiler->startTimer("sleep");
			Sleep(m_sleepTime);
			m_profiler->stopTimer("sleep");
		}

		m_profiler->stopTimer("frame");
	}
}

void GameLoop::stop() {

	m_running = false;
}

float GameLoop::computeAverageFps(float fps) {

	m_fpsSum -= m_fpsList[m_fpsIndex];
	m_fpsSum += fps;
	m_fpsList[m_fpsIndex] = fps;

	if (++m_fpsIndex == MAX_SAMPLES)
		m_fpsIndex = 0;

	return m_fpsSum / MAX_SAMPLES;
}

 GameLoop::~GameLoop() {

	delete m_clock;
	delete m_profiler;
}

