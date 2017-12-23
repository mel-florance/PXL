#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include "obj_loader.h"


class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0.0f, 0.0f, 0.0f)) {
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	inline glm::vec3* getPos() { return &pos; }
	inline glm::vec2* getTexCoord() { return &texCoord; }
	inline glm::vec3* getNormal() { return &normal; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};


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

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;

	void initMesh(const IndexedModel& model);

public:
	Mesh(Vertex* vertices, unsigned int vertexCount, unsigned int* indices, unsigned int indicesCount);
	Mesh(const std::string& filename);
	virtual ~Mesh();

	void draw();
};
