#include "sceneManager.h"

SceneManager::SceneManager()
{

}

void SceneManager::addScene(std::string name)
{
	Scene* scene = new Scene(name);
	m_scenes.push_back(scene);
	m_currentScene = m_scenes.size() - 1;
}

Scene* SceneManager::getCurrentScene()
{
	return m_scenes[m_currentScene];
}

SceneManager::~SceneManager()
{

}
