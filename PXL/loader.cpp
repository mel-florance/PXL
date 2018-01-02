#include "loader.h"

Loader::Loader()
{
	m_vaos.clear();
	m_vbos.clear();
}

Mesh* Loader::loadToVAO(
	const std::string& name,
	std::vector<glm::vec3> vertices,
	std::vector<int> indices,
	std::vector<glm::vec2> uvs,
	std::vector<glm::vec3> normals,
	std::vector<glm::vec3> tangents
)
{
	GLuint vao = this->createVAO();
	GLuint indicesSize = indices.size();
	
	this->bindIndicesBuffer(indices.data(), indicesSize);
	this->storeDataInAttributeList(0, 3, &vertices[0], vertices.size() * sizeof(glm::vec3));
	this->storeDataInAttributeList(1, 2, &uvs[0], uvs.size() * sizeof(glm::vec2));
	this->storeDataInAttributeList(2, 3, &normals[0], vertices.size() * sizeof(glm::vec3));
	this->storeDataInAttributeList(3, 3, &tangents[0], tangents.size() * sizeof(glm::vec3));
	this->unbindVAO();

	return new Mesh(name, vao, indicesSize);
}

void Loader::storeDataInAttributeList(GLuint location, int size, void* data, int dataSize)
{
	GLuint vbo;

	glGenBuffers(1, &vbo);
	m_vbos.push_back(vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Loader::bindIndicesBuffer(int* indices, GLuint& count)
{
	GLuint vbo;

	glGenBuffers(1, &vbo);
	m_vbos.push_back(vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * count, indices, GL_STATIC_DRAW);
}

GLuint Loader::createVAO()
{
	GLuint vao;

	glGenVertexArrays(1, &vao);
	m_vaos.push_back(vao);
	glBindVertexArray(vao);

	return vao;
}

Loader::~Loader()
{
	while (m_vbos.size() > 0)
	{
		glDeleteBuffers(1, &m_vbos.back());
		m_vbos.pop_back();
	}

	while (m_vaos.size() > 0)
	{
		glDeleteVertexArrays(1, &m_vaos.back());
		m_vaos.pop_back();
	}
}

