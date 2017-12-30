#include "scene.h"
#include <algorithm>

Scene::Scene(const std::string& name)
{
	m_name = name;
}

void Scene::addMesh(Mesh* mesh)
{
	m_meshes.emplace_back(mesh);
}

void Scene::removeMesh(Mesh* mesh) {
	m_meshes.erase(std::remove(m_meshes.begin(), m_meshes.end(), mesh), m_meshes.end());
}

Mesh* Scene::getMeshByName(const std::string name)
{
	for (unsigned int i = 0; i < m_meshes.size(); i++) {
		if (m_meshes[i]->getName() == name)
			return m_meshes[i];
	}

	return nullptr;
}

Scene::~Scene()
{

}