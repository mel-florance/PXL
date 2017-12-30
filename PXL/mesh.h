#pragma once

#include <string>
#include <iostream>

#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>

#include "obj_loader.h"
#include "transform.h"
#include "Vertex.h"

class Mesh
{
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

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;

	void initMesh(const IndexedModel& model);

public:
	Mesh(const std::string& name, Vertex* vertices, unsigned int vertexCount, unsigned int* indices, unsigned int indicesCount);
	Mesh(const std::string& name, const std::string& filename);
	virtual ~Mesh();

	inline std::string& getName() { return m_name; }
	inline Transform* getTransform() { return m_transform; }

	void draw();
};
