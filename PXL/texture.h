#pragma once

#include <string>
#include <GL/glew.h>

class Texture
{
public:
	Texture(const std::string& filename);
	Texture(const std::string& filename, bool generateMipmaps);
	virtual ~Texture();

	GLuint m_texture;

	void load();
	void bind(unsigned int unit);
	void unbind();
	
	std::string m_filename;
	bool m_generateMipmaps = false;
};
