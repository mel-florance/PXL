#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include <SDL2/SDL.h>

#include "clock.h"
#include "display.h"
#include "sceneManager.h"
#include "shaderManager.h"
#include "assetManager.h"
#include "fontManager.h"
#include "renderer.h"


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

private:
	Display* m_window;
	Clock* m_clock;
	Game* m_game;

	SceneManager* m_sceneManager;
	ShaderManager* m_shaderManager;
	AssetManager* m_assetManager;
	FontManager* m_fontManager;

	Renderer* m_renderer;
	Loader* m_loader;

	bool m_running;
	double m_deltaTime;
	double m_frameStart;
	double m_frameEnd;
};

