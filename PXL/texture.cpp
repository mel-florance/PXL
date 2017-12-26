#include "texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>
#include <ostream>
#include "util.h"

Texture::Texture(const std::string& filename)
{
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(filename.c_str(), &width, &height, &numComponents, STBI_rgb_alpha);

	if (imageData == NULL)
		std::cerr << "Texture loading failed for texture: " << filename << std::endl;

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	std::cout.precision(3);
	std::cout << "Loaded texture: " << filename << ": " << getFileSize(filename) << "Mb" << std::endl;

	stbi_image_free(imageData);
}

void Texture::bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}
