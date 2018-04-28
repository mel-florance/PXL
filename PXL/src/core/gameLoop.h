#pragma once


#include "profiler.h"
#include "clock.h"

#define MAX_SAMPLES 60

class Engine;
class GameLoop
{
public:
	GameLoop(Engine* engine);

	typedef void (*GameLoopCallback)(GameLoop* loop, Engine* engine);

	void start();
	void stop();

	inline bool isRunning() { return m_running; }
	inline Profiler* getProfiler() { return m_profiler; }
	inline Clock* getClock() { return m_clock; }

	inline void setUpdateCallback(GameLoopCallback callback) { m_updateCallback = callback; }
	inline void setRenderCallback(GameLoopCallback callback) { m_renderCallback = callback; }

	inline double getFrameTime() { return m_frameTime; }
	inline double getPassedTime() { return m_passedTime; }
	inline float getFps() { return m_fps; }

	float computeAverageFps(float fps);

	~GameLoop();
	Clock* m_clock;

private:

	Profiler* m_profiler;
	Engine* m_engine;
	GameLoopCallback m_updateCallback;
	GameLoopCallback m_renderCallback;

	bool m_running;
	bool m_render;
	int m_sleepTime;
	float m_fps;
	double m_lastTime;
	double m_startTime;
	double m_frameTime;
	double m_frameCounter;
	double m_unprocessedTime = 0;
	int m_frames = 0;
	double m_passedTime;

	int m_fpsIndex;
	float m_fpsSum;
	float m_fpsList[MAX_SAMPLES];
};

