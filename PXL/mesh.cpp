#include "mesh.h"

Mesh::Mesh(const std::string& name, GLuint& vao, GLuint& vertexCount)
{
	m_name = name;
	m_vao = vao;
	m_vertexCount = vertexCount;
	m_transform = new Transform();
}

void Mesh::draw(Camera* camera, std::vector<Light*> lights)
{
	this->getMaterial()->getShader()->bind();
	this->getMaterial()->bindAttributes();
	this->getMaterial()->preUpdate(this->getTransform(), camera, lights);

	glBindVertexArray(this->getVao());
	this->toggleAttributes(true);

	glDrawElements(GL_TRIANGLES, this->getVertexCount(), GL_UNSIGNED_INT, 0);

	this->toggleAttributes(false);
	this->getMaterial()->postUpdate();

	glBindVertexArray(0);
}

void Mesh::toggleAttributes(bool state)
{
	for (unsigned int i = 0; i < 4; i++)
		state == true 
		? glEnableVertexAttribArray(i) 
		: glDisableVertexAttribArray(i);
}

Mesh::~Mesh()
{
	delete m_transform;
}
