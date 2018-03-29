#pragma once

#include <string>
#include <vector>

#include <GL\glew.h>

#include "material.h"
#include "transform.h"

class Mesh
{
public:
	Mesh(const std::string& name, GLuint& vao, GLuint& vertexCount);
	~Mesh();

	inline GLuint& getVao() { return m_vao; }
	inline GLuint& getVertexCount() { return m_vertexCount; }

	inline const std::string& getName() { return m_name; }
	inline void setName(std::string& name) { m_name = name; }

	inline Transform* getTransform() { return m_transform; }
	inline void setTransform(Transform* transform) { m_transform = transform; }

	inline Material* getMaterial() { return m_material; }
	inline void setMaterial(Material* material) { m_material = material; }

	void draw();
	void toggleAttributes(bool state);

	void addChild(Mesh* child);

	std::vector<class Mesh*> getInstances() { return m_instances; }

	Mesh* createInstance(const std::string& name);

private:
	std::string m_name;
	GLuint m_vao;
	GLuint m_vertexCount;

	std::vector<class Mesh*> m_children;
	std::vector<class Mesh*> m_instances;

	Material* m_material;
	Transform* m_transform;
};

