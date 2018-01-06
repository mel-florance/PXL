#pragma once

#include "texture.h"
#include "material.h"
#include "scene.h"

class BasicMaterial : public Material
{
public:
	BasicMaterial(const std::string& name, Shader* shader);
	~BasicMaterial();

	virtual void preUpdate(Scene* scene);
	virtual void updateTransform(Transform* transform);
	virtual void postUpdate();

	inline void setShininess(float value) { m_shininess = value; }
	inline float& getShininess() { return m_shininess; }

	inline void setDiffuse(glm::vec3& diffuse) { m_diffuse = diffuse; }
	inline glm::vec3& getDiffuse() { return m_diffuse; }

	inline void setAmbient(glm::vec3& ambient) { m_ambient = ambient; }
	inline glm::vec3& getAmbient() { return m_ambient; }

	inline void setSpecular(glm::vec3& specular) { m_specular = specular; }
	inline glm::vec3& getSpecular() { return m_specular; }

	inline void setDiffuseTexture(Texture* texture) { m_diffuseTexture = texture; }
	inline Texture* getDiffuseTexture() { return m_diffuseTexture; }

	inline void setKa(float value) { m_Ka = value; }
	inline float& getKa() { return m_Ka; }

	inline void setKd(float value) { m_Kd = value; }
	inline float& getKd() { return m_Kd; }

	inline void setKs(float value) { m_Ks = value; }
	inline float& getKs() { return m_Ks; }

	inline void setBackFaceCulling(bool value) { m_backFaceCulling = value; }
	inline bool& getBackFaceCulling() { return m_backFaceCulling; }

	virtual void bindAttributes();

private:
	float m_shininess;

	glm::vec3 m_diffuse;
	glm::vec3 m_ambient;
	glm::vec3 m_specular;

	float m_Ka;
	float m_Kd;
	float m_Ks;

	Texture* m_diffuseTexture;

	glm::vec2 m_tiling;
	bool m_backFaceCulling;
};


