#include "scene.h"
#include "../ui/widget.h"

Scene::Scene(const std::string& name)
{
	m_name = name;
	m_clearColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_fogColor = glm::vec3(0.65f, 0.65f, 0.65f);
	m_fogGradient = 1.5f;
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

void Scene::addMesh(Mesh* mesh)
{
	m_meshes.emplace_back(mesh);
}

void Scene::removeMesh(Mesh* mesh)
{
	m_meshes.erase(std::remove(m_meshes.begin(), m_meshes.end(), mesh), m_meshes.end());
}

// Ui widgets

void Scene::addWidget(Widget* widget)
{
	m_widgets.emplace_back(widget);
}

void Scene::removeWidget(Widget* widget)
{
	m_widgets.erase(std::remove(m_widgets.begin(), m_widgets.end(), widget), m_widgets.end());
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

// Materials

void Scene::addMaterial(Material* material)
{
	m_materials.emplace_back(material);
}

void Scene::removeMaterial(Material* material)
{
	m_materials.erase(std::remove(m_materials.begin(), m_materials.end(), material), m_materials.end());
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
