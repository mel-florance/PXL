#pragma once

#include <vector>

#include <glm\glm.hpp>
#include <GL\glew.h>

#include "rawModel.h"

class Loader
{
public:
	Loader();
	~Loader();

	RawModel loadToVAO(
		std::vector<glm::vec3> vertices,
		std::vector<int> indices,
		std::vector<glm::vec2> uvs,
		std::vector<glm::vec3> normals
	);

	inline void unbindVAO() { glBindVertexArray(0); }

private:
	void storeDataInAttributeList(GLuint location, int size, void* data, int dataSize);
	void bindIndicesBuffer(int* indices, int& count);
	GLuint createVAO();

	std::vector<GLuint> m_vaos;
	std::vector<GLuint> m_vbos;
};

