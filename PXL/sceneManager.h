#pragma once

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

	void addScene(std::string& name);
	Scene* getCurrentScene();

private:
	unsigned int m_currentScene;
	std::vector<class Scene*> m_scenes;
};
