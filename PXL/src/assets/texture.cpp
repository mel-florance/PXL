
#include "texture.h"

 Texture::Texture(const std::string & filename) {

	m_filename = filename;
	m_generateMipmaps = false;
	m_lodBias = 0.0f;
	this->load();
}

 Texture::Texture(const std::string & filename, bool generateMipmaps) {

	m_filename = filename;
	m_generateMipmaps = generateMipmaps;
	this->load();
}

 Texture::~Texture() {

	glDeleteTextures(1, &m_texture);
}

Texture Texture::load() {
}

void Texture::bind(unsigned int unit) {

	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::unbind() {

	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
}

