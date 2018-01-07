#include "texture.h"

#include "stb_image.h"

#include "util.h"

Texture::Texture(const std::string& filename)
{
	m_filename = filename;
	m_generateMipmaps = false;
	this->load();
}

Texture::Texture(const std::string& filename, bool generateMipmaps)
{
	m_filename = filename;
	m_generateMipmaps = generateMipmaps;
	this->load();
}

Texture* Texture::Texture::load() 
{
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(m_filename.c_str(), &width, &height, &numComponents, STBI_rgb_alpha);

	if (imageData == NULL) {
		std::cerr << "Texture loading failed for texture: " << m_filename << std::endl;
		return nullptr;
	}

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (m_generateMipmaps) {
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexEnvf(GL_TEXTURE_FILTER_CONTROL, GL_TEXTURE_LOD_BIAS, m_lodBias);
	}
	else
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	std::cout.precision(3);
	std::cout << "Loaded texture: " << m_filename << ": " << getFileSize(m_filename) << "Mb" << std::endl;

	stbi_image_free(imageData);

	return this;
}

void Texture::bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::unbind() 
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}
