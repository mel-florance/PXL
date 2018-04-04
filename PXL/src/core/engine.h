#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include "profiler.h"
#include "clock.h"
#include "display.h"
#include "inputManager.h"

#include "../scene/sceneManager.h"
#include "../shaders/shaderManager.h"
#include "../assets/assetManager.h"
#include "../ui/core/guiManager.h"

#include "../rendering/renderer.h"


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
	inline Renderer* getRenderer() { return m_renderer; }
	inline Loader* getLoader() { return m_loader; }
	inline Profiler* getProfiler() { return m_profiler; }


	inline SceneManager* getSceneManager() { return m_sceneManager; }
	inline ShaderManager* getShaderManager() { return m_shaderManager; }
	inline AssetManager* getAssetManager() { return m_assetManager; }
	inline GuiManager* getGuiManager() { return m_guiManager; }
	inline FontManager* getFontManager() { return m_fontManager; }
	inline InputManager* getInputManager() { return m_inputManager; }

	inline double getFps() { return m_fps; }

private:
	Display* m_window;
	Clock* m_clock;
	Game* m_game;
	Renderer* m_renderer;
	Loader* m_loader;
	Profiler* m_profiler;


	SceneManager* m_sceneManager;
	ShaderManager* m_shaderManager;
	AssetManager* m_assetManager;
	GuiManager* m_guiManager;
	InputManager* m_inputManager;
	FontManager* m_fontManager;

	bool m_running;
	double m_fps;
	double m_frameTime;
	double m_passedTime;
};

