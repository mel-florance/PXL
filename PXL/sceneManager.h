#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "Scene.h"


class SceneManager
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

private:
	unsigned int m_currentScene;
	std::vector<class Scene*> m_scenes;
};
