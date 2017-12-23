#pragma once

#include <string>
#include <GL/glew.h>

class Texture
{
public:
	Texture(const std::string& filename);
	virtual ~Texture();

	GLuint m_texture;

	void bind(unsigned int unit);
};

