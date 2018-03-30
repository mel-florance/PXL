#pragma once

#include <sstream>
#include <string>

#include "material.h"
#include "../texturing/texture.h"
#include "../scene/scene.h"

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

	inline void setExponent(float value) { m_exponent = value; }
	inline float& getExponent() { return m_exponent; }

	inline void setReflectivity(float value) { m_reflectivity = value; }
	inline float& getReflectivity() { return m_reflectivity; }

	inline void setAlpha(float value) { m_alpha = value; }
	inline float& getAlpha() { return m_alpha; }

	inline void setDiffuseTexture(Texture* texture) { m_diffuseTexture = texture; }
	inline Texture* getDiffuseTexture() { return m_diffuseTexture; }
	
	inline void setSpecularTexture(Texture* texture) { m_specularTexture = texture; }
	inline Texture* getSpecularTexture() { return m_specularTexture; }

	inline void setNormalTexture(Texture* texture) { m_normalTexture = texture; }
	inline Texture* getNormalTexture() { return m_normalTexture; }

	inline void setKa(glm::vec3& value) { m_Ka = value; }
	inline glm::vec3& getKa() { return m_Ka; }

	inline void setKd(glm::vec3& value) { m_Kd = value; }
	inline glm::vec3& getKd() { return m_Kd; }

	inline void setKs(glm::vec3& value) { m_Ks = value; }
	inline glm::vec3& getKs() { return m_Ks; }

	inline void setKe(glm::vec3& value) { m_Ke = value; }
	inline glm::vec3& getKe() { return m_Ke; }

	inline void setBackFaceCulling(bool value) { m_backFaceCulling = value; }
	inline bool& getBackFaceCulling() { return m_backFaceCulling; }

	inline void setTiling(glm::vec2& tiling) { m_tiling = tiling; }
	inline glm::vec2& getTiling() { return m_tiling; }

	inline unsigned int hasDiffuseTexture() { return m_diffuseTexture != nullptr ? 1 : 0; }
	inline unsigned int hasSpecularTexture() { return m_specularTexture != nullptr ? 1 : 0; }
	inline unsigned int hasNormalTexture() { return m_normalTexture != nullptr ? 1 : 0; }

	virtual void bindAttributes();

private:
	float m_shininess;
	float m_exponent;
	float m_alpha;
	float m_reflectivity;

	glm::vec3 m_Ka; // Ambient
	glm::vec3 m_Kd; // Diffuse
	glm::vec3 m_Ks; // Specular
	glm::vec3 m_Ke; // Emission

	Texture* m_diffuseTexture;
	Texture* m_specularTexture;
	Texture* m_normalTexture;

	glm::vec2 m_tiling;
	bool m_backFaceCulling;
};
