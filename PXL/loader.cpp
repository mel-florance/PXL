#include "loader.h"
#include "stb_image.h"

Loader::Loader()
{
	m_vaos.clear();
	m_vbos.clear();
}

Mesh* Loader::loadToVAO(const std::string& name, std::vector<glm::vec2> vertices)
{
	GLuint vao = this->createVAO();
	GLuint vc = vertices.size();

	this->storeDataInAttributeList(0, 2, &vertices[0], vc * sizeof(glm::vec2));
	this->unbindVAO();

	return new Mesh(name, vao, vc);
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
	
	if(indicesSize > 0)
		this->bindIndicesBuffer(indices.data(), indicesSize);
	if(vertices.size() > 0)
		this->storeDataInAttributeList(0, 3, &vertices[0], vertices.size() * sizeof(glm::vec3));
	if(uvs.size() > 0)
		this->storeDataInAttributeList(1, 2, &uvs[0], uvs.size() * sizeof(glm::vec2));
	if(normals.size() > 0)
		this->storeDataInAttributeList(2, 3, &normals[0], vertices.size() * sizeof(glm::vec3));
	if(tangents.size() > 0)
		this->storeDataInAttributeList(3, 3, &tangents[0], tangents.size() * sizeof(glm::vec3));

	this->unbindVAO();

	return new Mesh(name, vao, indicesSize);
}

Uint32 Loader::loadCubeMap(std::vector<std::string> textures)
{
	Uint32 id;
	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);

	for (Uint32 i = 0; i < textures.size(); i++)
	{
		int width, height, numComponents;
		unsigned char* imageData = stbi_load(textures[i].c_str(), &width, &height, &numComponents, STBI_rgb_alpha);

		if (imageData == NULL) {
			std::cerr << "Cube map texture loading failed for: " << textures[i].c_str() << std::endl;
			return 0;
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		stbi_image_free(imageData);
	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return id;
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
