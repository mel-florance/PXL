#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include "profiler.h"
#include "clock.h"
#include "display.h"
#include "gameLoop.h"
#include "inputManager.h"

#include "../scene/sceneManager.h"
#include "../shaders/shaderManager.h"
#include "../assets/assetManager.h"
#include "../ui/core/guiManager.h"
#include "../audio/soundManager.h"

#include "../rendering/renderer.h"

class Editor;

class Engine
{
public:
	Engine(glm::vec2& windowSize);
	~Engine();

	void start();
	static void update(GameLoop* loop, Engine* self);
	static void render(GameLoop* loop, Engine* self);
	void stop();

	inline Display* getWindow() { return m_window; }
	inline Renderer* getRenderer() { return m_renderer; }
	inline Loader* getLoader() { return m_loader; }
	inline GameLoop* getLoop() { return m_gameLoop; }

	inline SceneManager* getSceneManager() { return m_sceneManager; }
	inline ShaderManager* getShaderManager() { return m_shaderManager; }
	inline AssetManager* getAssetManager() { return m_assetManager; }
	inline GuiManager* getGuiManager() { return m_guiManager; }
	inline FontManager* getFontManager() { return m_fontManager; }
	inline InputManager* getInputManager() { return m_inputManager; }
	inline SoundManager* getSoundManager() { return m_soundManager; }




private:
	GameLoop* m_gameLoop;
	Loader* m_loader;

	Display* m_window;
	Renderer* m_renderer;
	Editor* m_editor;
	InputManager* m_inputManager;
	SceneManager* m_sceneManager;

	ShaderManager* m_shaderManager;
	AssetManager* m_assetManager;
	GuiManager* m_guiManager;

	FontManager* m_fontManager;
	SoundManager* m_soundManager;

	glm::vec2 m_windowSize;
};

