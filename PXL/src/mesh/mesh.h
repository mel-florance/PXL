#pragma once

#include <string>
#include <vector>

#include <GL\glew.h>

#include "../materials/material.h"
#include "../core/transform.h"

class Mesh
{
public:
	Mesh(const std::string& name, GLuint& vao, GLuint& vertexCount);
	~Mesh();

	inline const unsigned long getId() { return (unsigned long)this; }

	inline GLuint getVao() { return m_vao; }
	inline GLuint getVertexCount() { return m_vertexCount; }

	inline std::string& getName() { return m_name; }
	inline void setName(const std::string& name) { m_name = name; }

	inline Transform* getTransform() { return m_transform; }
	inline void setTransform(Transform* transform) { m_transform = transform; }

	inline Material* getMaterial() { return m_material; }
	inline void setMaterial(Material* material) { m_material = material; }

	inline bool isVisible() { return m_visible; }
	inline void setVisible(bool state) { m_visible = state; }

	void draw();
	void toggleAttributes(bool state);

	void addChild(Mesh* child);

	inline std::vector<class Mesh*>& getInstances() { return m_instances; }

	Mesh* createInstance(const std::string& name);

private:
	std::string m_name;
	std::string m_id;
	GLuint m_vao;
	GLuint m_vertexCount;
	bool m_visible;

	std::vector<class Mesh*> m_children;
	std::vector<class Mesh*> m_instances;

	Material* m_material;
	Transform* m_transform;
};

