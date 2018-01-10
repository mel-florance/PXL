#pragma once

#include <vector>
#include <algorithm>
#include <string>

#include <glm\glm.hpp>

#include "mesh.h"
#include "material.h"
#include "Light.h"
#include "camera.h"
#include "text.h"

class Widget;

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
	void addText(Text* text);
	void addWidget(Widget* widget);

	inline std::string& getName() { return m_name; }
	inline void setName(std::string& name) { m_name = name; }

	inline std::vector<class Text*> getTexts() { return m_texts; }
	inline std::vector<class Mesh*> getMeshes() { return m_meshes; }
	inline std::vector<class Material*> getMaterials() { return m_materials; }
	inline std::vector<class Camera*> getCameras() { return m_cameras; }
	inline std::vector<class Light*> getLights() { return m_lights; }
	inline std::vector<class Widget*> getWidgets() { return m_widgets; }

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

	std::vector<class Text*> m_texts;
	std::vector<class Mesh*> m_meshes;
	std::vector<class Material*> m_materials;
	std::vector<class Camera*> m_cameras;
	std::vector<class Light*> m_lights;
	std::vector<class Widget*> m_widgets;

	glm::vec4 m_clearColor;
	glm::vec3 m_fogColor;
	float m_fogGradient;
	float m_fogDensity;
};
