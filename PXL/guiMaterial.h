#pragma once

#include "texture.h"
#include "material.h"
#include "scene.h"

class GuiMaterial : Material
{
public:
	GuiMaterial(const std::string& name, Shader* shader);
	~GuiMaterial();

	virtual void preUpdate(Scene* scene);
	virtual void updateTransform(Transform* transform);
	virtual void postUpdate();

	inline void setAlpha(float value) { m_alpha = value; }
	inline float& getAlpha() { return m_alpha; }

	inline void setDiffuseColor(const glm::vec3& color) { m_diffuseColor = color; }
	inline glm::vec3& getDiffuseColor() { return m_diffuseColor; }

	inline void setDiffuseTexture(Texture* texture) { m_diffuseTexture = texture; }
	inline Texture* getDiffuseTexture() { return m_diffuseTexture; }

	inline void setTiling(glm::vec2& tiling) { m_tiling = tiling; }
	inline glm::vec2& getTiling() { return m_tiling; }

	inline unsigned int hasDiffuseTexture() { return m_diffuseTexture != nullptr ? 1 : 0; }

	virtual void bindAttributes();

private:
	float m_alpha;
	Texture* m_diffuseTexture;
	glm::vec2 m_tiling;
	glm::vec3 m_diffuseColor;
};


