#pragma once

#include <vector>
#include <algorithm>
#include <string>

#include <glm\glm.hpp>

#include "mesh.h"
#include "material.h"
#include "Light.h"
#include "camera.h"


class Scene
{
public:
	Scene(const std::string& name);
	~Scene();

	void addMesh(Mesh* mesh);
	void removeMesh(Mesh* mesh);
	Mesh* getMeshByName(std::string name);

	void addCamera(Camera* camera);
	void addLight(Light* light);

	inline std::string& getName() { return m_name; }
	inline void setName(std::string name) { m_name = name; }

	inline glm::vec4& getClearColor() { return m_clearColor; }
	inline void setClearColor(glm::vec4 color) { m_clearColor = color; }

	inline std::vector<class Mesh*> getMeshes() { return m_meshes; }
	inline std::vector<class Material*> getMaterials() { return m_materials; }
	inline std::vector<class Camera*> getCameras() { return m_cameras; }
	inline std::vector<class Light*> getLights() { return m_lights; }

	void setActiveCamera(unsigned int index) { m_activeCamera = index; }
	inline Camera* getActiveCamera() { return m_cameras[m_activeCamera]; }

private:
	std::string m_name;
	glm::vec4 m_clearColor;
	unsigned int m_activeCamera;

	std::vector<class Mesh*> m_meshes;
	std::vector<class Material*> m_materials;
	std::vector<class Camera*> m_cameras;
	std::vector<class Light*> m_lights;
};
