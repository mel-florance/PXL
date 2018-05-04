
#include "mesh.h"
#include "transform.h"
#include "material.h"

 Mesh::Mesh(const std::string & name, GLuint & vao, GLuint & vertexCount) {

	m_name = name;
	m_vao = vao;
	m_vertexCount = vertexCount;
	m_transform = new Transform();
	m_visible = true;
}

 Mesh::~Mesh() {

	delete m_transform;

	for (unsigned int i = 0; i < m_instances.size(); i++)
		delete m_instances[i];
}

void Mesh::draw() {

	glDrawElements(GL_TRIANGLES, this->getVertexCount(), GL_UNSIGNED_INT, 0);
}

void Mesh::toggleAttributes(bool state) {

	for (unsigned int i = 0; i < 4; i++)
		state == true 
		? glEnableVertexAttribArray(i) 
		: glDisableVertexAttribArray(i);
}

void Mesh::addChild(Mesh & child) {

	m_children.push_back(child);
	child->getTransform()->setParent(m_transform);
}

Mesh Mesh::createInstance(const std::string & name) {

	Mesh* mesh = new Mesh(name, m_vao, m_vertexCount);
	m_instances.push_back(mesh);
	return mesh;
}

