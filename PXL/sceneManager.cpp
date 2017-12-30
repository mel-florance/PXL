#include "sceneManager.h"

SceneManager::SceneManager()
{

}

Scene* SceneManager::addScene(const std::string& name)
{
	Scene* scene = new Scene(name);
	m_scenes.emplace_back(scene);
	m_currentScene = m_scenes.size() - 1;
	return scene;
}

Scene* SceneManager::getSceneByName(const std::string& name) 
{
	for (unsigned int i = 0; i < m_scenes.size(); i++) {
		if (m_scenes[i]->getName() == name)
			return m_scenes[i];
	}

	return nullptr;
}

void SceneManager::deleteScene(const std::string& name)
{
	Scene* scene = getSceneByName(name);

	if (scene != nullptr) {
		m_scenes.erase(std::remove(m_scenes.begin(), m_scenes.end(), scene), m_scenes.end());
		std::cout << "Deleted scene: " << scene->getName() << std::endl;
		delete scene;
	}
}

void SceneManager::listScenes()
{
	std::cout << "Listing scenes: " << std::endl;

	for (unsigned int i = 0; i < m_scenes.size(); i++)
		std::cout << m_scenes[i]->getName() << std::endl;
}

SceneManager::~SceneManager()
{

}