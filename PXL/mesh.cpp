#include "mesh.h"

Mesh::Mesh(const std::string& name, const std::string& filename)
{
	this->m_name = name;
	this->m_transform = new Transform();

	IndexedModel model = OBJModel(filename).ToIndexedModel();
	std::cout << "Loaded mesh: " << filename << ". Vertices: " << model.positions.size() << std::endl;
	initMesh(model);
}

void Mesh::initMesh(const IndexedModel & model)
{
	m_drawCount = model.indices.size();

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

Mesh::Mesh(const std::string& name, Vertex* vertices, unsigned int vertexCount, unsigned int* indices, unsigned int indicesCount)
{
	this->m_name = name;
	IndexedModel model;

	for (unsigned int i = 0; i < vertexCount; i++) {
		model.positions.emplace_back(*vertices[i].getPos());
		model.texCoords.emplace_back(*vertices[i].getTexCoord());
		model.normals.emplace_back(*vertices[i].getNormal());
	}

	for (unsigned int i = 0; i < indicesCount; i++)
		model.indices.emplace_back(indices[i]);

	initMesh(model);
}

void Mesh::draw()
{
	glBindVertexArray(m_vertexArrayObject);
	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
	delete m_transform;
}
