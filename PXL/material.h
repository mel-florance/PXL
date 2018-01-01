#pragma once
#include <string>

#include <glm/glm.hpp>

#include "texture.h"

class Material
{
public:
	Material(const std::string& name, const std::string& shaderId);
	~Material();

	inline float getShininess() { return m_shininess; }
	inline float getReflectivity() { return m_reflectivity; }
	inline Texture* getDiffuseTexture() { return m_diffuseTexture; }

	inline void setShininess(float value) { m_shininess = value; }
	inline void setReflectivity(float value) { m_reflectivity = value; }
	inline void setDiffuseTexture(Texture* texture) { m_diffuseTexture = texture; }

private:
	std::string m_name;
	std::string m_shaderId;

	glm::vec3 m_color;
	glm::vec2 m_tiling = glm::vec2(1.0f, 1.0f);

	Texture* m_diffuseTexture;

	float m_shininess = 50.0f;
	float m_reflectivity = 0.5f;
};
