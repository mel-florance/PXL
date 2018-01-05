#pragma once

#include "texture.h"
#include "material.h"

class BasicMaterial : public Material
{
public:
	BasicMaterial(const std::string& name, Shader* shader);
	~BasicMaterial();

	inline float getShininess() { return m_shininess; }
	inline float getReflectivity() { return m_reflectivity; }
	inline Texture* getDiffuseTexture() { return m_diffuseTexture; }

	inline void setShininess(float value) { m_shininess = value; }
	inline void setReflectivity(float value) { m_reflectivity = value; }
	inline void setDiffuseTexture(Texture* texture) { m_diffuseTexture = texture; }

	virtual void preUpdate(Transform* transform, Camera* camera, std::vector<Light*> lights);
	virtual void postUpdate();

	virtual void bindAttributes();

private:
	glm::vec3 m_color;
	glm::vec2 m_tiling = glm::vec2(1.0f, 1.0f);

	Texture* m_diffuseTexture;

	float m_shininess = 50.0f;
	float m_reflectivity = 0.5f;
};

