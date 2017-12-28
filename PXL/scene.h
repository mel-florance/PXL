#pragma once

#include <vector>
#include <algorithm>
#include <string>

#include "mesh.h"
#include "material.h"
#include "Light.h"
#include "camera.h"


class Scene
{
public:
	Scene(std::string name);
	~Scene();

	void addMesh(Mesh* mesh);
	void removeMesh(Mesh* mesh);
	Mesh* getMeshByName(std::string name);

private:
	std::string m_name;

	std::vector<class Mesh*> m_meshes;
	std::vector<class Material*> m_materials;
	std::vector<class Camera*> m_cameras;
	std::vector<class Light*> m_lights;
};
