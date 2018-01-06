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

	inline void setDiffuseTexture(Texture* texture) { m_diffuseTexture = texture; }
	inline Texture* getDiffuseTexture() { return m_diffuseTexture; }

	inline void setKa(glm::vec3& value) { m_Ka = value; }
	inline glm::vec3& getKa() { return m_Ka; }

	inline void setKd(glm::vec3& value) { m_Kd = value; }
	inline glm::vec3& getKd() { return m_Kd; }

	inline void setKs(glm::vec3& value) { m_Ks = value; }
	inline glm::vec3& getKs() { return m_Ks; }

	inline void setBackFaceCulling(bool value) { m_backFaceCulling = value; }
	inline bool& getBackFaceCulling() { return m_backFaceCulling; }

	inline void setTiling(glm::vec2& tiling) { m_tiling = tiling; }
	inline glm::vec2& getTiling() { return m_tiling; }

	virtual void bindAttributes();

private:
	float m_shininess;

	glm::vec3 m_Ka;
	glm::vec3 m_Kd;
	glm::vec3 m_Ks;

	Texture* m_diffuseTexture;

	glm::vec2 m_tiling;
	bool m_backFaceCulling;
};


