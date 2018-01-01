#pragma once

#include <GL\glew.h>

class RawModel
{
public:
	RawModel(GLuint& vao, int& vertexCount);
	~RawModel();

	inline GLuint getVao() { return m_vao; }
	inline int getVertexCount() { return m_vertexCount; }

private:
	GLuint m_vao;
	int m_vertexCount;
};

