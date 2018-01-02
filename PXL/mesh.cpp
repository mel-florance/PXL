#include "mesh.h"

Mesh::Mesh(const std::string& name, GLuint& vao, GLuint& vertexCount)
{
	m_name = name;
	m_vao = vao;
	m_vertexCount = vertexCount;
	m_transform = new Transform();
}

Mesh::~Mesh()
{
	delete m_transform;
}
