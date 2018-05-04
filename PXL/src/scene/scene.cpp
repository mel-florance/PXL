#include "scene.h"
#include "../ui/core/widget.h"

Scene::Scene(const std::string& name)
{
	m_name = name;
	m_clearColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_fogColor = glm::vec3(0.65f, 0.65f, 0.65f);
	m_fogGradient = 0.015f;
	m_fogDensity = 0.0f;
}

// Meshes
Mesh* Scene::getMeshByName(const std::string name)
{
	for (unsigned int i = 0; i < m_meshes.size(); i++)
		if (m_meshes[i]->getName() == name)
			return m_meshes[i];

	return nullptr;
}

Mesh* Scene::addMesh(Mesh* mesh)
{
	m_meshes.push_back(mesh);
	return mesh;
}

void Scene::removeMesh(Mesh* mesh)
{
	m_meshes.erase(std::remove(m_meshes.begin(), m_meshes.end(), mesh), m_meshes.end());
}

// Materials
Material* Scene::addMaterial(Material* material)
{
	m_materials.emplace_back(material);
	return material;
}

void Scene::removeMaterial(Material* material)
{
	m_materials.erase(std::remove(m_materials.begin(), m_materials.end(), material), m_materials.end());
}

// Ui widgets
void Scene::addWidget(Widget* widget, Layout* layout)
{
	layout->addWidget(widget);
}

void Scene::removeWidget(Widget* widget, Layout* layout)
{
	layout->removeWidget(widget);
}

// Cameras
void Scene::addCamera(Camera* camera)
{
	m_cameras.emplace_back(camera);
	m_activeCamera = m_cameras.size() - 1;
}

void Scene::removeCamera(Camera* camera) 
{
	m_cameras.erase(std::remove(m_cameras.begin(), m_cameras.end(), camera), m_cameras.end());
}


// Lights
void Scene::addLight(Light* light)
{
	m_lights.emplace_back(light);
}

void Scene::removeLight(Light* light) 
{
	m_lights.erase(std::remove(m_lights.begin(), m_lights.end(), light), m_lights.end());
}

Scene::~Scene()
{

}
