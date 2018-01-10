#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include "clock.h"
#include "display.h"
#include "sceneManager.h"
#include "shaderManager.h"
#include "assetManager.h"
#include "fontManager.h"
#include "inputManager.h"
#include "renderer.h"
#include "profiler.h"

class Game;
class Engine
{
public:
	Engine();
	~Engine();

	void start();
	void stop();

	inline Display* getWindow() { return m_window; }
	inline Clock* getClock() { return m_clock; }
	inline SceneManager* getSceneManager() { return m_sceneManager; }
	inline ShaderManager* getShaderManager() { return m_shaderManager; }
	inline Renderer* getRenderer() { return m_renderer; }
	inline AssetManager* getAssetManager() { return m_assetManager; }
	inline Loader* getLoader() { return m_loader; }
	inline FontManager* getFontManager() { return m_fontManager; }
	inline InputManager* getInputManager() { return m_inputManager; }
	inline Profiler* getProfiler() { return m_profiler; }

	inline double getFps() { return m_fps; }

private:
	Display* m_window;
	Clock* m_clock;
	Game* m_game;

	SceneManager* m_sceneManager;
	ShaderManager* m_shaderManager;
	AssetManager* m_assetManager;
	FontManager* m_fontManager;
	InputManager* m_inputManager;

	Renderer* m_renderer;
	Loader* m_loader;
	Profiler* m_profiler;

	bool m_running;
	double m_fps;
	double m_frameTime;
	double m_passedTime;
};

