#pragma once

#include <string>
#include <iostream>

#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>

#include "obj_loader.h"
#include "transform.h"
#include "vertex.h"
#include "material.h"

class Mesh
{
public:
	Mesh(const std::string& name, Vertex* vertices, unsigned int vertexCount, unsigned int* indices, unsigned int indicesCount);
	Mesh(const std::string& name, const std::string& filename);
	virtual ~Mesh();

	inline std::string& getName() { return m_name; }
	inline void setName(const std::string& name) { m_name = name; }

	inline Transform* getTransform() { return m_transform; }
	inline void setTransform(Transform* transform) { m_transform = transform; }

	inline void setMaterial(Material* material) { m_material = material; }
	inline Material* getMaterial() { return m_material; }

	void draw();

private:
	enum {
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS = 4
	};

	std::string m_name;
	Transform* m_transform;
	Material* m_material;

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;

	void initMesh(const IndexedModel& model);
	void calcNormals(IndexedModel& model);
};
