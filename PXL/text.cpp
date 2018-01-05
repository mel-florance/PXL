#include "text.h"

Text::Text(const char* text, int x, int y, int size) : m_text(text), m_x(x), m_y(y), m_size(size)
{
	glGenBuffers(1, &m_vbo_vertices);
	glGenBuffers(1, &m_vbo_uvs);
}

void Text::draw()
{
	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> uvs;

	unsigned int len = strlen(m_text);

	for (unsigned int i = 0; i < len; i++) 
	{
		glm::vec2 v_up_left = glm::vec2(m_x + i * m_size, m_y + m_size);
		glm::vec2 v_up_right = glm::vec2(m_x + i * m_size + m_size, m_y + m_size);
		glm::vec2 v_down_right = glm::vec2(m_x + i * m_size + m_size, m_y);
		glm::vec2 v_down_left = glm::vec2(m_x + i * m_size, m_y);

		vertices.push_back(v_up_left);
		vertices.push_back(v_down_left);
		vertices.push_back(v_up_right);

		vertices.push_back(v_down_right);
		vertices.push_back(v_up_right);
		vertices.push_back(v_down_left);

		char character = m_text[i];

		float uv_x = (character % 16) / 16.0f;
		float uv_y = (character / 16) / 16.0f;

		glm::vec2 u_up_left = glm::vec2(uv_x, uv_y);
		glm::vec2 u_up_right = glm::vec2(uv_x + 1.0f / 16.0f,uv_y);
		glm::vec2 u_down_right = glm::vec2(uv_x + 1.0f / 16.0f,(uv_y + 1.0f / 16.0f));
		glm::vec2 u_down_left = glm::vec2(uv_x, (uv_y + 1.0f / 16.0f));

		uvs.push_back(u_up_left);
		uvs.push_back(u_down_left);
		uvs.push_back(u_up_right);

		uvs.push_back(u_down_right);
		uvs.push_back(u_up_right);
		uvs.push_back(u_down_left);
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_uvs);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	this->getMaterial()->getShader()->bind();
	this->getMaterial()->bindAttributes();
	this->getMaterial()->getDiffuseTexture()->bind(0);
	this->getMaterial()->getShader()->setUniform1i("diffuseTexture", 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertices);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_uvs);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glDisable(GL_BLEND);


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	this->getMaterial()->getShader()->unbind();
	this->getMaterial()->getDiffuseTexture()->unbind();
}

Text::~Text()
{
	glDeleteBuffers(1, &m_vbo_vertices);
	glDeleteBuffers(1, &m_vbo_uvs);
}
