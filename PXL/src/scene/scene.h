#pragma once

#include <vector>
#include <algorithm>
#include <string>

#include <glm\glm.hpp>


#include "../mesh/mesh.h"
#include "../core/util.h"
#include "../materials/material.h"

#include "../lighting/light.h"
#include "../cameras/camera.h"
#include "../ui/core/guiManager.h"

#include "../ui/widgets/text.h"
#include "../ui/widgets/layout.h"

class Widget;

class Scene
{
public:
	Scene(const std::string& name);
	~Scene();

	inline std::string& getName() { return m_name; }
	inline void setName(std::string& name) { m_name = name; }

	inline std::vector<class Mesh*> getMeshes() { return m_meshes; }
	Mesh* getMeshByName(const std::string name);
	Mesh* addMesh(Mesh* mesh);
	void removeMesh(Mesh* mesh);

	inline std::vector<class Material*> getMaterials() { return m_materials; }
	Material* addMaterial(Material* material);
	void removeMaterial(Material* material);

	inline std::vector<class Camera*> getCameras() { return m_cameras; }
	void addCamera(Camera* camera);
	void removeCamera(Camera* camera);

	inline std::vector<class Light*> getLights() { return m_lights; }
	void addLight(Light* light);
	void removeLight(Light* light);

	void addWidget(Widget* widget, Layout* layout);
	void removeWidget(Widget* widget, Layout* layout);

	void setActiveCamera(unsigned int index) { m_activeCamera = index; }
	inline Camera* getActiveCamera() { return m_cameras[m_activeCamera]; }

	inline glm::vec4& getClearColor() { return m_clearColor; }
	inline void setClearColor(glm::vec4& color) { m_clearColor = color; }

	inline glm::vec3& getFogColor() { return m_fogColor; }
	inline void setFogColor(glm::vec3& color) { m_fogColor = color; }

	inline float& getFogGradient() { return m_fogGradient; }
	inline void setFogGradient(float& value) { m_fogGradient = value; }

	inline float& getFogDensity() { return m_fogDensity; }
	inline void setFogDensity(float& value) { m_fogDensity = value; }

private:
	std::string m_name;
	unsigned int m_activeCamera;

	std::vector<class Camera*> m_cameras;
	std::vector<class Light*> m_lights;
	std::vector<class Mesh*> m_meshes;
	std::vector<class Material*> m_materials;

	glm::vec4 m_clearColor;
	glm::vec3 m_fogColor;
	float m_fogGradient;
	float m_fogDensity;
};
