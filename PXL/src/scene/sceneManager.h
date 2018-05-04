#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "scene.h"
#include "../core/manager.h"

class GuiManager;

class SceneManager : public Manager
{
public:
	SceneManager();
	~SceneManager();

	inline std::vector<class Scene*> getScenes() { return m_scenes; }
	inline void setCurrentScene(unsigned int index) { m_currentScene = index; }

	Scene* addScene(const std::string& name);
	void deleteScene(const std::string& name);
	void listScenes();

	Scene* getSceneByName(const std::string& name);
	Scene* getCurrentScene() { return m_scenes[m_currentScene]; }

	void setGuiManager(GuiManager* guiManager) { m_guiManager = guiManager; }
	GuiManager* getGuiManager() { return m_guiManager; }

private:
	GuiManager* m_guiManager;
	unsigned int m_sceneCount;
	unsigned int m_currentScene;
	std::vector<Scene*> m_scenes;
};
