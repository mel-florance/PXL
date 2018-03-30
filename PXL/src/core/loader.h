#pragma once

#include <vector>
#include <string>

#include <glm\glm.hpp>
#include <GL\glew.h>

#include "../mesh/mesh.h"

class Loader
{
public:
	Loader();
	~Loader();

	Mesh* loadToVAO(const std::string& name, std::vector<glm::vec3> vertices);
	Mesh* loadToVAO(const std::string& name, std::vector<glm::vec2> vertices);

	Mesh* loadToVAO(
		const std::string& name,
		std::vector<glm::vec3> vertices,
		std::vector<int> indices,
		std::vector<glm::vec2> uvs,
		std::vector<glm::vec3> normals,
		std::vector<glm::vec3> tangents
	);

	Uint32 loadCubeMap(std::vector<std::string> textures);

	inline void unbindVAO() { glBindVertexArray(0); }

private:
	void storeDataInAttributeList(GLuint location, int size, void* data, int dataSize);
	void bindIndicesBuffer(int* indices, GLuint& count);
	GLuint createVAO();

	std::vector<GLuint> m_vaos;
	std::vector<GLuint> m_vbos;
};
